#include "read_singleframe_private.h"

boolean read_singleframe(struct iso15765_tp_s* instance)
{
	instance->pdu.iso15765_protocol_data.length = determine_uds_unsegmented_frame_length(instance->can_frame.data.byte[0]);

	if ((instance->pdu.iso15765_protocol_data.length == 0) ||
			(instance->pdu.iso15765_protocol_data.length > SINGLE_FRAME_MAX_LENGTH)) {
		//ignore message
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
		return FALSE;
	} else {
		add_data_to_buffer(
				single_frame_type,
				instance->can_frame.data.byte,
				instance->pdu.iso15765_service_data.data,
				instance->pdu.iso15765_protocol_data.length, 0 );
		instance->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = indication;
		instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
		set_next_rx_signal(instance, rx_success_signal);
		return TRUE;
	}
}


static uint8 determine_uds_unsegmented_frame_length(uint8 first_byte_in_frame)
{
	return first_byte_in_frame & 0x0F;
}
