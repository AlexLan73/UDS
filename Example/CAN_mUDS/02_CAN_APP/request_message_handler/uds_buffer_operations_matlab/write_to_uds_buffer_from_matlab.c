#include "write_to_uds_buffer_from_matlab.h"
#include "write_to_uds_buffer_from_c.h"
#include "can_tp_iso15765_parameters.h"
#include "uds_parameters.h"
#include "Platform_types.h"

//extern void write_to_uds_buffer_from_c(unsigned char data_byte, unsigned char* to, unsigned short size, unsigned short current_position);

void write_1byte_to_uds_buffer_from_matlab(unsigned char data)
{
	write_1byte_to_uds_buffer_from_c(
			data,
			can_tp_iso15765_response_instance[0].can_tp.pdu.iso15765_service_data.data,
			1,
			&can_tp_iso15765_response_instance[0].can_tp.pdu.iso15765_service_data.buffer_idx
			);//TODO resp instance buffer
	can_tp_iso15765_response_instance[0].can_tp.pdu.iso15765_protocol_data.length = can_tp_iso15765_response_instance[0].can_tp.pdu.iso15765_service_data.buffer_idx;
}


