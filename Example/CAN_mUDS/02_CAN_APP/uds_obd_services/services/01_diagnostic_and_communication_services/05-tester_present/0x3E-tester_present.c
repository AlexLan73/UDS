#include "tester_present.h"
#include "uds_timers.h"
#include "Platform_Types.h"

uint8 tester_present(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	uint8 sub_function = request_message->pdu.iso15765_service_data.data[1] & 0x7F;
	switch (sub_function) {
	case 0x00:
	case 0x80:
		start_uds_s_3_server_time_measurement();

		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = TPPR;
		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
		response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;

		return NRC_PR;
	default:
		return NRC_SFNS;
	}
}

