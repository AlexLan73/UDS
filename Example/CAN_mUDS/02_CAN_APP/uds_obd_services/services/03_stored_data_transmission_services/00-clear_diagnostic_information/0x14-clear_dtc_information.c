#include "clear_dtc_information_private.h"

uint8 clear_dtc_information(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	if (request_message->pdu.iso15765_protocol_data.length == MESSAGE_LENGTH_CDTCI) {
		union id_of_group_of_dtc_u group_id;

		group_id.U = 0;
		group_id.B.high = request_message->pdu.iso15765_service_data.data[1];
		group_id.B.middle = request_message->pdu.iso15765_service_data.data[2];
		group_id.B.low = request_message->pdu.iso15765_service_data.data[3];

		delete_group_of_dtc(group_id);

		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = CDTCIPR;

		response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
		return NRC_PR;
	} else {
		return NRC_IMLOIF;
	}
}


static void delete_group_of_dtc(union id_of_group_of_dtc_u group_id)
{
//	f_0_clearDTC = 1;
}

