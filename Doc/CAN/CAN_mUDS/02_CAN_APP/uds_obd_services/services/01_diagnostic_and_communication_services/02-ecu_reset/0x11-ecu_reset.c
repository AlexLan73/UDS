#include "ecu_reset_private.h"

uint8 ecu_reset(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	if (request_message->pdu.iso15765_protocol_data.length == ER_LEN) {
		switch (request_message->pdu.iso15765_service_data.data[1] & 0x7F) {
		case HR:
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ERPR;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = HR;
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			return NRC_PR;
		default:
			suppress_uds_response = 1;
			return NRC_SNSIAS;
		}
	} else {
		return NRC_IMLOIF;
	}
}
