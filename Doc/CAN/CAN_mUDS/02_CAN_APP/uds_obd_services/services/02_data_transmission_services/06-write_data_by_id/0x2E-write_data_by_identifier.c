#include "write_data_by_id_private.h"

void write_data_by_id(struct iso15765_tp_s*  response_message, struct iso15765_tp_s* request_message)
{
	if ((request_message->pdu.iso15765_protocol_data.length) >= WR_BY_ID_MIN_MESSAGE_LENGTH) {
		uint16 data_id = (((uint16)request_message->pdu.iso15765_service_data.data[2]<<8) + request_message->pdu.iso15765_service_data.data[3]);
		if (total_length_is_correct(data_id, request_message)) {
			if (support_by_active_session(data_id)) {
				if (security_access_granted(data_id)) {
					if (check_conditions()) { // TODO
						if (data_is_valid(request_message)) {
							if (write_data_by_id_complete(data_id, request_message)) {
								response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = WDBIPR;
								response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = request_message->pdu.iso15765_service_data.data[1];
								response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = request_message->pdu.iso15765_service_data.data[2];
								response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
								response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
							} else {
								response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_GPF;
							}
						} else {
							response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
						}
					} else {
						response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_CNC;
					}
				} else {
					response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SAD;
				}
			} else {
				response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SNSIAS;
			}
		} else {
			response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
		}
	} else {
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
	}

	if (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER]) {
		response_message->pdu.iso15765_service_data.buffer_idx = 0;
		// prepare negative response
		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0x7F;
		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = WDBI;
		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER];
		response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
	}

	uint8 suppress_pos_rsp_msg_indication_bit = (request_message->pdu.iso15765_service_data.data[1] & 0x80);

	if ((suppress_pos_rsp_msg_indication_bit) && (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_PR)) {// && (“not yet a NRC NRC_RCRRP 0x78  response sent”))
		suppress_uds_response = 1;
	} else {
		suppress_uds_response = 0;
	}
}

static uint8 total_length_is_correct(uint16 data_id, struct iso15765_tp_s* request_message)
{
	return 1;
}

static uint8 support_by_active_session(uint16 data_id)
{
	return 1;
}


static uint8 security_access_granted(uint16 data_id)
{
	return 1;
}

static uint8 check_conditions(void)
{
	return 1;
}

static uint8 data_is_valid(struct iso15765_tp_s* request_message)
{
	//TODO Data record is valid? how to check?
	return 1;
}

static uint8 write_data_by_id_complete(uint16 data_id, struct iso15765_tp_s* request_message)
{
	return 1;
}
