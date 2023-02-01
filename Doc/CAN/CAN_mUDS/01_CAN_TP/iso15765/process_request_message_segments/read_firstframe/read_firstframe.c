#include "read_firstframe_private.h"

boolean read_firstframe(struct iso15765_tp_s* instance)
{
	instance->sequence_number_counter = 0;
	instance->pdu.iso15765_service_data.buffer_idx = 0;
	instance->pdu.iso15765_protocol_data.length = determine_uds_segmented_frame_length(instance->can_frame.data.byte);
	instance->number_of_unprocessed_bytes = instance->pdu.iso15765_protocol_data.length;
	instance->handled_message_counter = server_parameter[0].block_size;

	if ((instance->pdu.iso15765_protocol_data.length < FIRST_FRAME_MIN_LENGTH)||
			(instance->pdu.iso15765_protocol_data.target_address_type == functional_address_type)) {
		/*ignore message*/
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
		return FALSE;
	} else if (instance->pdu.iso15765_protocol_data.length > CAN_TP_BUFFER_SIZE) {
		/*ignore message*/
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_BUFFER_OVFLW;
		return FALSE;
	} else {
		add_data_to_buffer(
				first_frame_type,
				instance->can_frame.data.byte,
				instance->pdu.iso15765_service_data.data,
				FIRST_FRAME_LENGTH,
				0
				);
		instance->number_of_unprocessed_bytes -= FIRST_FRAME_LENGTH;
		instance->pdu.iso15765_service_data.buffer_idx += FIRST_FRAME_LENGTH;
		set_next_rx_signal(instance, fc_write_cts_signal);
		instance->sequence_number_counter = 1;
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication_ff;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
		return TRUE;
	}
}

static uint16 determine_uds_segmented_frame_length(uint8* first_two_bytes_in_frame)
{
	return (((uint16)first_two_bytes_in_frame[0]<<8)&0x0F00)+((uint16)first_two_bytes_in_frame[1]);
}
