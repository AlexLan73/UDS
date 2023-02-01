#include "write_firstframe_private.h"

void write_firstframe(struct iso15765_tp_s* instance)
{
	if ((instance->pdu.iso15765_protocol_data.length < FIRST_FRAME_MIN_LENGTH) ||
			(instance->pdu.iso15765_protocol_data.length > CAN_TP_BUFFER_SIZE)) {
		//ignore first_frame
		set_next_tx_signal(instance, tx_default_signal); //TODO RESET_UDS();
		stop_rx_timer_segmented(instance);
	} else {
		instance->sequence_number_counter = 0;
		instance->handled_message_counter = 0;
		instance->pdu.iso15765_service_data.buffer_idx = 0;

		add_ff_pdu(instance);
		/*instance->remain_data_counter = */extract_data_from_buffer(
				first_frame_type,
				instance->pdu.iso15765_service_data.data,
				instance->can_frame.data.byte,
				FIRST_FRAME_LENGTH,
				0
				);
		instance->pdu.iso15765_service_data.buffer_idx += FIRST_FRAME_LENGTH;
		instance->number_of_unprocessed_bytes -= FIRST_FRAME_LENGTH;

		instance->can_frame.id = instance->pdu.iso15765_protocol_data.target_address;
		instance->can_frame.length = 8;

		can_write_frame(instance->can_frame);

		set_next_tx_signal(instance, ff_wait_confirm__signal);
	}
}

static void add_ff_pdu(struct iso15765_tp_s* instance)
{
	instance->can_frame.data.byte[0] = (0x01 << 4) | ( (uint8)( (instance->pdu.iso15765_protocol_data.length>>8) & 0xF) ); // frame type				 // buffer_for_transmission_size
	instance->can_frame.data.byte[1] = (uint8)(instance->pdu.iso15765_protocol_data.length & 0xFF );
}
