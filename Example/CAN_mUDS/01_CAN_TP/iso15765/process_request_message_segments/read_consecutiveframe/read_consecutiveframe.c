#include "read_consecutiveframe_private.h"

void read_consecutiveframe(struct iso15765_tp_s* instance)
{
	uint8 current_sequence_number = ( (instance->can_frame.data.byte[0])&0x0F );

	if (instance->sequence_number_counter == current_sequence_number) {
		if( instance->number_of_unprocessed_bytes > CONSECUTIVE_FRAME_MAX_LENGTH) {
			add_data_to_buffer(
					consecutive_frame_type,
					instance->can_frame.data.byte,
					instance->pdu.iso15765_service_data.data,
					CONSECUTIVE_FRAME_MAX_LENGTH,
					instance->pdu.iso15765_service_data.buffer_idx
					);
			instance->number_of_unprocessed_bytes -= CONSECUTIVE_FRAME_MAX_LENGTH;
			instance->pdu.iso15765_service_data.buffer_idx += CONSECUTIVE_FRAME_MAX_LENGTH;
		} else if (instance->number_of_unprocessed_bytes <= CONSECUTIVE_FRAME_MAX_LENGTH) {
			add_data_to_buffer(
					consecutive_frame_type,
					instance->can_frame.data.byte,
					instance->pdu.iso15765_service_data.data,
					instance->number_of_unprocessed_bytes,
					instance->pdu.iso15765_service_data.buffer_idx
					);
			instance->number_of_unprocessed_bytes = 0;
		}

		if (instance->number_of_unprocessed_bytes) {
			if (current_sequence_number == MAX_SEQUENCE_NUMBER) {
				instance->sequence_number_counter = 0;
			} else {
				instance->sequence_number_counter++;
			}
			instance->handled_message_counter--;
			if ((instance->handled_message_counter <= server_parameter[0].block_size) &&
					(instance->handled_message_counter > 0)) {
				reset_tp_timer(instance);
				set_next_rx_signal(instance, cf_wait_ind_signal);
			} else {
				instance->handled_message_counter = server_parameter[0].block_size;
				change_tp_timer_to(instance, BR_TIMER);
				set_next_rx_signal(instance, fc_write_cts_signal);
			}
		} else {
			//TODO check this condition
//			if (can_tp_iso15765_server_parameter.need_send_fc_after_last_cf) {
//				set_next_rx_signal(instance, fc_write_cts_signal);
//			} else {
				set_next_rx_signal(instance, rx_success_signal);
//			}
		}
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
	} else {
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_WRONG_SN;
		set_next_rx_signal(instance, rx_error_signal);
	}
}
