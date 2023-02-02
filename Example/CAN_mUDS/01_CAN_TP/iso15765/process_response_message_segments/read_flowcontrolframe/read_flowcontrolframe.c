#include "read_flowcontrolframe_private.h"

void read_flowcontrolframe(struct iso15765_tp_s* instance)
{
	uint8 flow_control_status = (instance->can_frame.data.byte[0]&0xF);
	client_parameter[0].block_size = instance->can_frame.data.byte[1];
	client_parameter[0].separation_time = instance->can_frame.data.byte[2];

	if (flow_control_status == continue_to_send) {
			if (instance->number_of_unprocessed_bytes) {
				if (client_parameter[0].block_size != 0) {
					set_next_tx_signal(instance, cf_req_with_fc_signal);
				} else if (client_parameter[0].block_size == 0) {
					set_next_tx_signal(instance, cf_req_without_fc_signal);
				}
				change_tp_timer_to(instance, CS_TIMER);
			} else {
				set_next_tx_signal(instance, tx_success_signal);/*success*/
			}
	} else if (flow_control_status == wait_fc) {
			reset_tp_timer(instance);
			instance->wait_frame_counter++;
			set_next_tx_signal(instance, fc_ind_wait_signal);
			if (instance->wait_frame_counter == MAX_WAIT_FRAME_TRANSMISSIONS) {
				set_next_tx_signal(instance, tx_error_signal);
				stop_rx_timer_segmented(instance);
			}
	} else if (flow_control_status == overflow) {
		set_next_tx_signal(instance, tx_error_signal);
	}
}


