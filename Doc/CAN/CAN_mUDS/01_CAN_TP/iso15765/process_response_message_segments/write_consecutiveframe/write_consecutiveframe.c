#include "write_consecutiveframe_private.h"

void write_consecutiveframe(struct iso15765_tp_s* instance)
{
	if (instance->sequence_number_counter < MAX_SEQUENCE_NUMBER) {
		instance->sequence_number_counter++;
	} else {
		instance->sequence_number_counter = 0;
	}

	add_cf_pdu(instance);

	if (instance->number_of_unprocessed_bytes >= CONSECUTIVE_FRAME_MAX_LENGTH) {
		/*instance->remain_data_counter = */extract_data_from_buffer(
				consecutive_frame_type,
				instance->pdu.iso15765_service_data.data,
				instance->can_frame.data.byte ,
				CONSECUTIVE_FRAME_MAX_LENGTH,
				instance->pdu.iso15765_service_data.buffer_idx);
		instance->pdu.iso15765_service_data.buffer_idx += CONSECUTIVE_FRAME_MAX_LENGTH;
		instance->number_of_unprocessed_bytes -= CONSECUTIVE_FRAME_MAX_LENGTH;
	} else if ((instance->number_of_unprocessed_bytes < CONSECUTIVE_FRAME_MAX_LENGTH)) {
		/*instance->remain_data_counter = */extract_data_from_buffer(
				consecutive_frame_type,
				instance->pdu.iso15765_service_data.data,
				instance->can_frame.data.byte ,
				instance->number_of_unprocessed_bytes,
				instance->pdu.iso15765_service_data.buffer_idx);
		instance->pdu.iso15765_service_data.buffer_idx += instance->number_of_unprocessed_bytes;
		instance->number_of_unprocessed_bytes = 0;
	}

	instance->can_frame.id = instance->pdu.iso15765_protocol_data.target_address;
	instance->can_frame.length = 8;

	can_write_frame(instance->can_frame);
}

static void add_cf_pdu(struct iso15765_tp_s* instance)
{
	instance->can_frame.data.byte[0] = ((0x02 << 4) | ( (uint8)(instance->sequence_number_counter & 0xF) )); /*frame type and sequence number*/
}
