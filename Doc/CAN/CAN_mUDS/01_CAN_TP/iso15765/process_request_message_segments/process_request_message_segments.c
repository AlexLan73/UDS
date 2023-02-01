#include "can_initialization.h"
#include "process_request_message_segments.h"

#include "rx_fsm.h"
#include "tx_fsm.h"
#include "tp_timers.h"

#include "read_singleframe.h"
#include "read_firstframe.h"
#include "read_consecutiveframe.h"
#include "write_flowcontrol.h"
#include "reset_network_layer.h"
#include "can_frame_status.h"
#include "can_frame_structure.h"
#include "can_read_frame.h"
#include "can_chck_status.h"

#pragma GCC optimize "O0"

extern void read_request_message(struct iso15765_tp_s* request_message);
extern void function_to_get_first_frame(struct iso15765_tp_s* message);
//--------------------------------------------------------------------------------
//DECLARATION FUNC
//--------------------------------------------------------------------------------

//STATIC

/*!
\brief short description

full description

\param[in]
*/
static void copy_can_msg(uint32 can_id, struct can_message_s rx_msg, struct iso15765_tp_s* can_tp_instance_p);

/*!
\brief short description

full description

\param[in] rm - request message -
*/
static void set_data_layer_primitive(enum iso15765_message_type mt, struct iso15765_tp_s* instance_p);

/*!
\brief short description

full description

\param[in] rm - request message -
*/
static void process_received_message_segment(struct iso15765_tp_s* instance);

/*!
\brief short description

full description

*/
static void check_rx_signal_change(struct iso15765_tp_s* instance);

/*!
\brief short description

full description

*/
static enum iso_15765_frame_type determine_segment_type(uint8 first_byte_in_frame);

/*!
\brief short description

full description

*/
static boolean received_first_frame_segment(struct iso15765_tp_s* instance);

/*!
\brief short description

full description

*/
static boolean request_message_complete(struct iso15765_tp_s* instance);

/*!
\brief short description

full description

*/
static boolean handle_received_segment(struct iso15765_tp_s* instance);

/*!
\brief short description

full description

\param[in] cm can message -
\param[in] req_m request message -
\return
 */
static void can_tp_iso15765_receive_message_segment(uint32 can_id);



//-------------------------------------------------------------------------------------------------------------------------------
// GLOBAL FUNC
//-------------------------------------------------------------------------------------------------------------------------------

void can_tp_read_segment(uint32 can_id)
{
	can_tp_iso15765_receive_message_segment(can_id);
}

struct iso15765_tp_s* get_iso15765_tp_request_instance(uint32 can_id)
{
	// maybe can_tp_instance was reserved for received ID
	uint8 i = 0;
	for (i = 0; i < ISO15765_MAX_NUM; i++) {
		if (can_tp_iso15765_request_instance[i].can_tp.pdu.iso15765_protocol_data.target_address == can_id &&
				can_tp_iso15765_request_instance[i].is_free == 0 &&
				can_tp_iso15765_request_instance[i].can_tp.pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] == idle) {
			return &can_tp_iso15765_request_instance[i].can_tp;
		}
	}

	//if instance wasn't reserved
	//search empty instance for save
	for (i = 0; i < ISO15765_MAX_NUM; i++) {
		if (can_tp_iso15765_request_instance[i].is_free) {
			can_tp_iso15765_request_instance[i].is_free = FALSE;
			return &can_tp_iso15765_request_instance[i].can_tp;
		}
	}

	return NULL_PTR;
}

boolean release_iso15765_tp_request_instance(struct iso15765_tp_s* can_tp_request_instance_p)
{
	uint8 i = 0;

	for (i = 0; i < ISO15765_MAX_NUM; i++) {
		if (can_tp_iso15765_request_instance[i].is_free == FALSE) {
			if (
					(can_tp_request_instance_p->pdu.iso15765_protocol_data.target_address == can_tp_iso15765_request_instance[i].can_tp.pdu.iso15765_protocol_data.target_address) &&
					(can_tp_request_instance_p->pdu.iso15765_protocol_data.source_address == can_tp_iso15765_request_instance[i].can_tp.pdu.iso15765_protocol_data.source_address)
					) {
				can_tp_iso15765_request_instance[i].is_free = TRUE;
				return TRUE;
			}
		}
	}

	return FALSE;
}






//--------------------------------------------------------------------------------
// STATIC FUNC
//--------------------------------------------------------------------------------

static void can_tp_iso15765_receive_message_segment(uint32 can_id)
{
	struct can_message_s can_msg;
	enum can_status_e status;
	struct iso15765_tp_s* iso15765_instance = NULL_PTR;



	status = can_read_frame(can_id, &can_msg);

	if (status == new_data) {
		enum iso_15765_frame_type segment_type = determine_segment_type(can_msg.data.byte[0]&0xFF);

		iso15765_instance = get_iso15765_tp_request_instance(can_id);

		if (iso15765_instance == NULL_PTR) { return; }
		copy_can_msg(can_id, can_msg, iso15765_instance);

		switch (segment_type) {
		case single_frame_type:
			set_next_rx_signal(iso15765_instance, sf_ind_signal);
			break;
		case first_frame_type:
			if (can_id == server_parameter[0].broadcast_address) { return; }
			set_next_rx_signal(iso15765_instance, ff_ind_signal);
			break;
		case consecutive_frame_type:
			if (can_id == server_parameter[0].broadcast_address) { return; }
			set_next_rx_signal(iso15765_instance, cf_ind_signal);
			break;
		case flow_control_frame_type:
			///!!!!!!! WARNING !!!!!!! this case use TX_FSM
			///!!!!!!! WARNING !!!!!!! this case use RESPONSE instanse
			if (can_id == server_parameter[0].broadcast_address) { return; }

			uint8 idx = 0;
			for (idx = 0; idx < ISO15765_MAX_NUM; idx++) {
				if (!can_tp_iso15765_response_instance[idx].is_free &&
					can_tp_iso15765_response_instance[idx].can_tp.pdu.iso15765_protocol_data.source_address == can_id) {
					copy_can_msg(can_id, can_msg, &can_tp_iso15765_response_instance[idx].can_tp);
					set_next_tx_signal(&can_tp_iso15765_response_instance[idx].can_tp, fc_indication_signal);
				}
			}
			release_iso15765_tp_request_instance(iso15765_instance);
			return;
		case unknown_type:
		default:
			return;
		}

		if (can_id == server_parameter[0].server_address) {
			iso15765_instance->pdu.iso15765_protocol_data.target_address_type = physical_address_type;
			iso15765_instance->pdu.iso15765_protocol_data.source_address = server_parameter[0].client_address;
			iso15765_instance->pdu.iso15765_protocol_data.target_address = server_parameter[0].server_address;
			iso15765_instance->pdu.iso15765_protocol_data.id_type = ID_CAN_11BIT;
			iso15765_instance->pdu.iso15765_protocol_data.format_type = normal_addressing_format;
			iso15765_instance->pdu.iso15765_protocol_data.result[DATA_LAYER] = N_OK;
		} else if (can_id == server_parameter[0].broadcast_address) {
			iso15765_instance->pdu.iso15765_protocol_data.target_address_type = functional_address_type;
			iso15765_instance->pdu.iso15765_protocol_data.source_address = server_parameter[0].broadcast_address;
			iso15765_instance->pdu.iso15765_protocol_data.target_address = server_parameter[0].server_address;
			iso15765_instance->pdu.iso15765_protocol_data.id_type = ID_CAN_11BIT;
			iso15765_instance->pdu.iso15765_protocol_data.format_type = normal_addressing_format;
			iso15765_instance->pdu.iso15765_protocol_data.result[DATA_LAYER] = N_OK;
		} else {
			return;
		}

		set_data_layer_primitive(indication, iso15765_instance);
	}

	iso15765_instance = NULL_PTR;

	// The loop is needed to process all received instances. (The first - reads, the second - counts the time until the next consecutive frame, the third....)
	uint8 idx;
	for (idx = 0; idx < ISO15765_MAX_NUM; idx++) {
		if (!can_tp_iso15765_request_instance[idx].is_free) {
			iso15765_instance = &can_tp_iso15765_request_instance[idx].can_tp;
			set_data_layer_primitive(unknown_message, iso15765_instance);
			process_received_message_segment(iso15765_instance); //TODO Function name is not correct.
			if (received_first_frame_segment(iso15765_instance)) {
				//todo something(run timer, in example)
				function_to_get_first_frame(iso15765_instance);
			}
			if (request_message_complete(iso15765_instance)) {
				read_request_message(iso15765_instance);
			}
			iso15765_instance = NULL_PTR;
		}
	}
}

//-------------------------------------------------------------------------------------

static enum iso_15765_frame_type determine_segment_type(uint8 first_byte_in_frame)
{
	uint8 temp_type = ((first_byte_in_frame >> 4) & 0x0F);

	switch (temp_type) {
	case 0:
		return single_frame_type;
	case 1:
		return first_frame_type;
	case 2:
		return consecutive_frame_type;
	case 3:
		return flow_control_frame_type;
	default:
		return unknown_type;
	}
}

//------------------------------------------------------------------------------------------------------------------
static boolean received_first_frame_segment(struct iso15765_tp_s* instance)
{
	return (instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] == indication_ff)? TRUE:FALSE;
}

static boolean request_message_complete(struct iso15765_tp_s* instance)
{
	return (instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] == indication)?TRUE:FALSE;
}

static void copy_can_msg(uint32 can_id, struct can_message_s rx_msg, struct iso15765_tp_s* can_tp_instance_p)
{
	can_tp_instance_p->can_frame.id 			= can_id;
	can_tp_instance_p->can_frame.data.word[0]   = rx_msg.data.word[0];
	can_tp_instance_p->can_frame.data.word[1]   = rx_msg.data.word[1];
	can_tp_instance_p->can_frame.length 		= rx_msg.length;
}

static void set_data_layer_primitive(enum iso15765_message_type mt, struct iso15765_tp_s* instance_p)
{
	instance_p->pdu.iso15765_protocol_data.message_type[DATA_LAYER] = mt;
}

static void process_received_message_segment(struct iso15765_tp_s* instance)
{
	/*-------------------------------------------------------------------------------*/
	//UNEXP
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == UNEXP_SF_IND_STATE) {
		stop_rx_timer_unsegmented(instance);
		if (!read_singleframe(instance)) {
			set_can_tp_rx_default_network_layer(instance); //TODO check this condition
			//set_next_rx_signal(instance, rx_error_signal); //TODO ERROR_STATE set indication for APP level !!!!fix
		}
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == UNEXP_FF_IND_STATE) {
		stop_rx_timer_segmented(instance);
		start_rx_timer_segmented(instance);

		if (read_firstframe(instance)) {
			instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication_ff;
		} else {
			set_can_tp_rx_default_network_layer(instance); //TODO check this condition
			return;
		}
	}
	/*-------------------------------------------------------------------------------*/


	/*-------------------------------------------------------------------------------*/
	//SINGLE
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == SF_IND_STATE) {
		if (!read_singleframe(instance)) {
			set_can_tp_rx_default_network_layer(instance);
		}
	}
	/*-------------------------------------------------------------------------------*/



	/*-------------------------------------------------------------------------------*/
	//MULTI
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == FF_IND_STATE) {
		start_rx_timer_segmented(instance);

		if (read_firstframe(instance)) {
			instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication_ff;
		} else {
			set_can_tp_rx_default_network_layer(instance);
			return;
		}
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == FC_WRITE_CTS_STATE) {
		write_flow_control_frame(instance, continue_to_send);
		set_next_rx_signal(instance, fc_wait_conf_signal);
		change_tp_timer_to(instance, AR_TIMER);
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == FC_WAIT_CONF_CTS_STATE) {
		enum can_status_e status = can_frame_chck_status(instance->pdu.iso15765_protocol_data.source_address);//todo check this condition

		if (status == success) {
			change_tp_timer_to(instance, CR_TIMER);
			instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
			if(instance->number_of_unprocessed_bytes) {
				set_next_rx_signal(instance, fc_conf_signal);
			} else {
				set_next_rx_signal(instance, rx_success_signal);
			}
		} else {
			track_tp_time(instance);
		}

	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == CF_WAIT_IND_STATE) {
		track_tp_time(instance);
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == CF_IND_STATE) {
		if (instance->timer.current_signal == AR_TIMER) {
			//if FC_WRITE_CTS_STATE didn't wait for confirmation. Need to change the timer.
			change_tp_timer_to(instance, CR_TIMER);
		}
		read_consecutiveframe(instance);
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == RX_SUCCESS_STATE) {
		// TODO reset flag req_m->is_empty = TRUE; inside application layer
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
		set_can_tp_rx_default_network_layer(instance);
		return;
	}
	/*-------------------------------------------------------------------------------*/



	/*-------------------------------------------------------------------------------*/
	/*-------------------ERROR, TIMEOUT, DEFAULT, OVERFLOW---------------------------*/
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == RX_TIMEOUT_STATE) {
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
		set_can_tp_rx_default_network_layer(instance);
		return;
	}
	/*-------------------------------------------------------------------------------*/
	// if consecutive frame is received the first, state will be default - ignore

	check_rx_signal_change(instance);
	if (instance->rx_fsm.current_rx_state == RX_DEFAULT_STATE) {
		release_iso15765_tp_request_instance(instance);
		return;
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == FC_WRITE_OVRFLW_STATE) {
		write_flow_control_frame(instance, overflow);
		change_tp_timer_to(instance, AR_TIMER);
		set_next_rx_signal(instance, fc_wait_conf_signal);
		return;
	}

	/*-------------------------------------------------------------------------------*/

	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == FC_WAIT_CONF_OVRFLW_STATE) {
		enum can_status_e status = can_frame_chck_status(instance->pdu.iso15765_protocol_data.source_address);//todo check this condition

		if (status == success) {
			change_tp_timer_to(instance, CR_TIMER);
			instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_BUFFER_OVFLW;
			set_next_rx_signal(instance, rx_error_signal);
		} else {
			track_tp_time(instance);
		}
	}
	/*-------------------------------------------------------------------------------*/
	check_rx_signal_change(instance);

	if (instance->rx_fsm.current_rx_state == RX_ERROR_STATE) {
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		set_can_tp_rx_default_network_layer(instance);
		return;
	}
}

static void check_rx_signal_change(struct iso15765_tp_s* instance)
{
	if (instance->rx_fsm.new_rx_signal != instance->rx_fsm.current_rx_signal) {
		enum network_rx_state new_rx_state_temp = instance->rx_fsm.current_rx_state;
		enum network_rx_signal new_rx_signal_temp = instance->rx_fsm.current_rx_signal;

		instance->rx_fsm.current_rx_signal = instance->rx_fsm.new_rx_signal;
		instance->rx_fsm.current_rx_state = get_next_rx_step(instance);
		if (instance->rx_fsm.current_rx_state == RX_IGNORE) {
			instance->rx_fsm.current_rx_state = new_rx_state_temp;
			instance->rx_fsm.current_rx_signal = instance->rx_fsm.new_rx_signal = new_rx_signal_temp;
		}
	}
}

//-------------------------------------------------------------------------------------

//boolean release_iso15765_tp_instance(struct iso15765_tp_s* can_tp_instance_p)
//{
//	uint8 i = 0;
//
//	for (i = 0; i<RESP_MSG_MAX_NUM; i++) {
//		if (!can_tp_iso15765_response_instances_array[i].is_free) {
//			if (/*TODO check this condition*/
//					can_tp_instance_p->pdu.iso15765_protocol_data.target_address ==
//					can_tp_iso15765_response_instances_array[i].can_tp.pdu.iso15765_protocol_data.target_address
//					) {
//				can_tp_iso15765_response_instances_array[i].is_free = TRUE;
//				return TRUE;
//			}
//		}
//	}
//
//	return FALSE;
//}
