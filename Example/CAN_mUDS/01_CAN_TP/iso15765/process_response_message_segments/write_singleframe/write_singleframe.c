#include "write_singleframe_private.h"

void write_singleframe(struct iso15765_tp_s* instance)
{
	add_sf_pdu(instance);
	extract_data_from_buffer(
			single_frame_type,
			instance->pdu.iso15765_service_data.data,
			instance->can_frame.data.byte ,
			instance->pdu.iso15765_protocol_data.length, 0);
	instance->can_frame.id = instance->pdu.iso15765_protocol_data.target_address;
	instance->can_frame.length = 8;

	can_write_frame(instance->can_frame);
}

static void add_sf_pdu(struct iso15765_tp_s* instance)
{
	instance->can_frame.data.byte[0] = (0x00 << 4) | ( (uint8)(instance->pdu.iso15765_protocol_data.length & 0xF) );
}
