#include "can_initialization.h"
#include "process_response_segment.h"
#include "tx_fsm.h"
#include "tp_timers.h"
#include "write_singleframe.h"
#include "write_firstframe.h"
#include "read_flowcontrolframe.h"
#include "write_consecutiveframe.h"
#include "reset_network_layer.h"
#include "process_request_message_segments.h"
#include "can_frame_status.h"
#include "can_chck_status.h"

static boolean transmit_segment(struct iso15765_tp_s* instance);
static void check_tx_signal_change(struct iso15765_tp_s* instance);

//TODO add protocol_name parameter into function signature
void can_tp_write(struct iso15765_tp_s* responce_instance)
{
	//TODO need to check all conditions!
	if (responce_instance->pdu.iso15765_protocol_data.source_address == NULL_PTR) { /*todo need to release*/ return; }
	if (responce_instance->pdu.iso15765_protocol_data.target_address == NULL_PTR) { /*todo need to release*/ return; }
	if (responce_instance->pdu.iso15765_protocol_data.length == 0) { /*todo need to release*/ return; }

	if (responce_instance->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] == request_transmission) {
		responce_instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = request_transmission;
		responce_instance->number_of_unprocessed_bytes = responce_instance->pdu.iso15765_protocol_data.length;

		if (responce_instance->pdu.iso15765_protocol_data.length <= SINGLE_FRAME_MAX_LENGTH) {
			set_next_tx_signal(responce_instance, sf_request_signal);
		} else if (responce_instance->pdu.iso15765_protocol_data.length <= CAN_TP_BUFFER_SIZE) {
			set_next_tx_signal(responce_instance, ff_request_signal);
		}
		can_tp_iso15765_send_message_segments();
	}
}

void can_tp_iso15765_send_message_segments(void)
{
	struct iso15765_tp_s* instance_p = NULL_PTR;

	uint8 idx;
	for (idx = 0; idx < ISO15765_MAX_NUM; idx++) {
		if (!can_tp_iso15765_response_instance[idx].is_free) {
			instance_p = &can_tp_iso15765_response_instance[idx].can_tp;
			//TODO Link with individual received STmin timer
			if (transmit_segment(instance_p)) {
				if (instance_p->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] == confirmation) {
					instance_p->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = confirmation;
					if (instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] == N_OK) {
						instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
					} else {
						instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
					}
					release_iso15765_tp_response_instance(instance_p); //TODO Consider this action
				}
				instance_p = NULL_PTR;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------

static boolean transmit_segment(struct iso15765_tp_s* response_instance)
{
	check_tx_signal_change(response_instance);
	/*-------------------------------------------------------------------------------*/
	if (response_instance->tx_fsm.current_tx_state == SF_REQUEST_STATE) {
			start_tx_timer_unsegmented(response_instance);
			write_singleframe(response_instance);
			set_next_tx_signal(response_instance, sf_wait_conf_signal);//TODO
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == SF_WAIT_CONF_STATE) {
			enum can_status_e status = can_frame_chck_status(response_instance->pdu.iso15765_protocol_data.target_address);

			if (status == success) {
				change_tp_timer_to(response_instance, BS_TIMER);
				set_next_tx_signal(response_instance, tx_success_signal);
			} else {
				track_tp_time(response_instance);
			}
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == FF_REQUEST_STATE) {
			set_next_tx_signal(response_instance, ff_request_signal);/*TODO */
			start_tx_timer_segmented(response_instance);
			write_firstframe(response_instance);
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == FF_WAIT_CONFIRM__STATE) {
			enum can_status_e status = can_frame_chck_status(response_instance->pdu.iso15765_protocol_data.target_address);

			if (status == success) {
				change_tp_timer_to(response_instance, BS_TIMER);
				set_next_tx_signal(response_instance, ff_confirm_signal);
			} else {
				track_tp_time(response_instance);
			}
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == FC_WAIT_STATE) {
		/*FC_WAIT_STATE   rx_fsm*/
		track_tp_time(response_instance);
		can_tp_read_segment(response_instance->pdu.iso15765_protocol_data.source_address);
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == FC_INDICATION_STATE) {
		change_tp_timer_to(response_instance, CS_TIMER);
		read_flowcontrolframe(response_instance);
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == CF_REQUEST_WITH_FC_STATE ||
			response_instance->tx_fsm.current_tx_state == CF_REQUEST_WITHOUT_FC_STATE) {
		write_consecutiveframe(response_instance);
		change_tp_timer_to(response_instance, AS_TIMER);

		switch (response_instance->tx_fsm.current_tx_state) {
		case CF_REQUEST_WITH_FC_STATE:
			set_next_tx_signal(response_instance, cf_wait_conf_with_fc_signal);
			break;
		case CF_REQUEST_WITHOUT_FC_STATE:
			set_next_tx_signal(response_instance, cf_wait_conf_without_fc_signal);
			break;
		case TX_IGNORE:
		case TX_TIMEOUT:
		case TX_SUCCESS:
		case TX_ERROR_STATE:
		default:
			break;
		}
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == CF_WAIT_CONFIRM_WITH_FC_STATE ||
			response_instance->tx_fsm.current_tx_state == CF_WAIT_CONF_WITHOUT_FC_STATE) {
		enum can_status_e status = can_frame_chck_status(response_instance->pdu.iso15765_protocol_data.target_address);

		if (status == success) {
			response_instance->handled_message_counter++;

			switch(response_instance->tx_fsm.current_tx_state) {
			case CF_WAIT_CONFIRM_WITH_FC_STATE:
				if (response_instance->handled_message_counter < client_parameter[0].block_size) {
					if (response_instance->number_of_unprocessed_bytes) {
						set_next_tx_signal(response_instance, cf_req_with_fc_signal);
					} else {
						set_next_tx_signal(response_instance, fc_ind_wait_signal);
					}
					change_tp_timer_to(response_instance, CS_TIMER);
				} else if(response_instance->handled_message_counter == client_parameter[0].block_size) {
					change_tp_timer_to(response_instance, BS_TIMER);
					response_instance->handled_message_counter = 0;
					set_next_tx_signal(response_instance, fc_ind_wait_signal);
				}
				break;
			case CF_WAIT_CONF_WITHOUT_FC_STATE:
				if (response_instance->number_of_unprocessed_bytes) {
					change_tp_timer_to(response_instance,CS_TIMER);
					set_next_tx_signal(response_instance, cf_req_without_fc_signal);
				} else {
					set_next_tx_signal(response_instance, tx_success_signal);
				}
				break;
			default:
				break;
			}
		} else {
			track_tp_time(response_instance);
		}

	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == TX_ERROR_STATE) {
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == TX_IGNORE) {
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == TX_TIMEOUT) {
		stop_tx_timer_segmented(response_instance);
		response_instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = confirmation;
		response_instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
		set_can_tp_tx_default_network_layer(response_instance);
		return TRUE;
	}
	/*-------------------------------------------------------------------------------*/
	check_tx_signal_change(response_instance);
	if (response_instance->tx_fsm.current_tx_state == TX_SUCCESS) {
		response_instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = confirmation;
		response_instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;

		stop_tx_timer_segmented(response_instance);
		//set_next_tx_signal(tx_default_signal);
		set_can_tp_tx_default_network_layer(response_instance);
		return TRUE;
	}
	check_tx_signal_change(response_instance);
	/*-------------------------------------------------------------------------------*/
	return FALSE;
}


static void check_tx_signal_change(struct iso15765_tp_s* response_instance)
{
	if(response_instance->tx_fsm.new_tx_signal != response_instance->tx_fsm.current_tx_signal) {
		enum network_tx_state new_tx_state_temp = response_instance->tx_fsm.current_tx_state;
		response_instance->tx_fsm.current_tx_signal = response_instance->tx_fsm.new_tx_signal;
		response_instance->tx_fsm.current_tx_state = get_next_tx_step(response_instance);
		if(response_instance->tx_fsm.current_tx_state == TX_IGNORE) {
			response_instance->tx_fsm.current_tx_state = new_tx_state_temp;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------
struct iso15765_tp_s* get_iso15765_tp_response_instance_for(uint32 target_address)
{
	uint8 num_of_instance = ISO15765_MAX_NUM;
	// maybe can_tp_instance was previously reserved for target_address
	// (did not enough time to respond to the previous message)
	uint8 i = 0;
	for (i = 0; i < num_of_instance; i++) {
		if (can_tp_iso15765_response_instance[i].can_tp.pdu.iso15765_protocol_data.source_address == target_address &&
				can_tp_iso15765_response_instance[i].is_free == 0) {
			// already used!
			//return NULL_PTR;
			return &can_tp_iso15765_response_instance[i].can_tp;
		}
	}

	//if can_tp_instance was not previously reserved
	//we search empty instance to save
	for (i = 0; i < num_of_instance; i++) {
		if (can_tp_iso15765_response_instance[i].is_free) {
			can_tp_iso15765_response_instance[i].is_free = FALSE;
			return &can_tp_iso15765_response_instance[i].can_tp;
		}
	}

	return NULL_PTR;
}

boolean release_iso15765_tp_response_instance(struct iso15765_tp_s* can_tp_response_instance_p)
{
	uint8 num_of_instance = ISO15765_MAX_NUM;
	uint8 i = 0;
	for (i = 0; i<num_of_instance; i++) {
		if (!can_tp_iso15765_response_instance[i].is_free) {
			if (/*TODO check this condition*/
					can_tp_response_instance_p->pdu.iso15765_protocol_data.target_address == can_tp_iso15765_response_instance[i].can_tp.pdu.iso15765_protocol_data.target_address &&
					can_tp_response_instance_p->pdu.iso15765_protocol_data.source_address == can_tp_iso15765_response_instance[i].can_tp.pdu.iso15765_protocol_data.source_address
					) {
				can_tp_iso15765_response_instance[i].is_free = TRUE;
				return TRUE;
			}
		}
	}

	return FALSE;
}
