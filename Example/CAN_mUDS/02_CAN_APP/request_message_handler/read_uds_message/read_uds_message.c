#include "read_uds_message.h"
#include "process_request_message_segments.h"
#include "process_response_segment.h"
#include "uds_timers.h"
#include "can_initialization.h"

static boolean with_subfunction(uint8 service);

void read_uds_message(struct iso15765_tp_s* request_message)
{
	//TODO if response_message == NULL_PTR, need to process the request. Make a request later.
	struct iso15765_tp_s* response_message = get_iso15765_tp_response_instance_for(request_message->pdu.iso15765_protocol_data.source_address);
	if (response_message != NULL_PTR) {
		//---------------------------------------------------------------------------------------------------------------------------------------
		// response_message header configuration
		//---------------------------------------------------------------------------------------------------------------------------------------
		if (request_message->pdu.iso15765_protocol_data.target_address == server_parameter[0].server_address ||
				request_message->pdu.iso15765_protocol_data.target_address == server_parameter[0].broadcast_address) {
			response_message->pdu.iso15765_protocol_data.target_address = server_parameter[0].client_address;
			response_message->pdu.iso15765_protocol_data.source_address = server_parameter[0].server_address;
		} else {
			release_iso15765_tp_response_instance(response_message);
			release_iso15765_tp_request_instance(request_message);
		}


//		switch (request_message->pdu.iso15765_protocol_data.target_address) {
//		case PHY_DIAG_REQ_CAN_ID:
//		case FUNC_DIAG_REQ_CAN_ID://todo mapping in transport layer
//			response_message->pdu.iso15765_protocol_data.target_address = PHY_DIAG_RESP_CAN_ID;
//			response_message->pdu.iso15765_protocol_data.source_address = PHY_DIAG_REQ_CAN_ID;
//			break;
//		default:
//			release_iso15765_tp_response_instance(response_message);
//			release_iso15765_tp_request_instance(request_message);
//			return;
//		}

		switch (request_message->pdu.iso15765_protocol_data.target_address_type) {
		case physical_address_type:
		case functional_address_type:
			response_message->pdu.iso15765_protocol_data.target_address_type = physical_address_type; //TODO
			break;
		default:
			release_iso15765_tp_response_instance(response_message);
			release_iso15765_tp_request_instance(request_message);
			return;
		}

		switch (request_message->pdu.iso15765_protocol_data.format_type) {
		case normal_addressing_format:
			response_message->pdu.iso15765_protocol_data.format_type = normal_addressing_format;
			break;
		case none_addressing_format:
		case fixed_normal_addressing_format:
		case extended_addressing_format:
		case mixed_addressing_format:
		case enhansed_addressing_format:
		case unknown_addressing_format:
		default:
			release_iso15765_tp_response_instance(response_message);
			release_iso15765_tp_request_instance(request_message);
			return;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------

		uint8 service = request_message->pdu.iso15765_service_data.data[0];
		uint8 response_code;
		suppress_uds_response = 0;

		// TODO !!!! if server receives a message from the same address after
		// receiving the app.indication primitive, the new data will destroy
		// the message which are reading now.
		//
		// Need to lock instance or copy the data after receiving the app.indication primitive.


		// Request message parameter and server response behaviour: pseudo code: page 27, ISO 14229-1 2013
		response_code = check_uds_service_permissions(service, uds_active_session, uds_active_security_level, uds_active_security_level);

		if (response_code == NRC_PR) {
			//Request message with sub-function parameter and server response behaviour is described on page 21 14229-1 2013
			if (with_subfunction(service)) {
				if (request_message->pdu.iso15765_protocol_data.length >= MIN_MESSAGE_LENGTH_WITH_SUBFUNCTION) {
					// services with sub-function
					// The sub-function parameter byte is divided into two parts (on bit-level) as defined in Table 11 on@ page 31 ISO 14229-1 2013.
					switch (service) {
					case DIAGSC:
						response_code = diagnostic_session_control(response_message, request_message);
						break;
//					case ER:
//						response_code = ecu_reset(response_message, request_message);
//						break;
					case SA:
						response_code = security_access(response_message, request_message);
						break;
	//				case CC:
	//					//response_code = communication_control(response_message, request_message);
	//					break;
					case TPRES:
						//TODO need to move to the session layer
						response_code = tester_present(response_message, request_message);
						break;
					case RDTCI:
						response_code = read_dtc_information(response_message, request_message);
						break;
	//				case RC:
	//					response_code = routine_control(response_message, request_message);
	//					break;
	//				case CDTCS:
	//					response_code = control_dtc_setting(response_message, request_message);
	//					break;
					default:
						response_code = NRC_SNS;
						break;
					}
				} else {
					response_code = NRC_IMLOIF;
				}

				uint8 suppress_pos_rsp_msg_indication_bit = (request_message->pdu.iso15765_service_data.data[1] & 0x80);

				if (suppress_pos_rsp_msg_indication_bit) {
					suppress_uds_response = 1;
				} else {
					suppress_uds_response = 0;
				}
			} else {
				//service without sub-function
				switch (service) {
//				case RDBI:
//					response_code = read_data_by_id(response_message, request_message);
//					break;
				case CDTCI:
					response_code = clear_dtc_information(response_message, request_message);
					break;
//				case RD:
//					response_code = request_download(response_message, request_message);
//					break;
//				case RU:
					//response_code = request_upload(response_message, request_message);
//					break;
//				case TD:
//					response_code = transfer_data(response_message, request_message);
//					break;
//				case RTE:
//					response_code = request_transfer_exit(response_message, request_message);
//					break;
				default:
					response_code = NRC_SNS;
					break;
				}
			}
		}

		if (response_code) {
			response_message->pdu.iso15765_service_data.buffer_idx = 0;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0x7F;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = service;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = response_code;
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
		}


		//todo
//		When 0x78 NRC is used, the server shall always send a final response (positive or
//		negative) independent of the suppressPosRspMsgIndicationBit value or the
//		suppress requirement for responses with NRCs SNS, SFNS, SNSIAS, SFNSIAS
//		and ROOR on functionally addressed requests.(page 329, NRC 0x78, ISO 14229-1 2013)

		//todo
//		0x78 NRC shall only be used in a negative response message
//		if the server will not be able to receive further request messages
//		from the client while completing the requested diagnostic service


		//todo
//		When functional addressing is used for the request message, and the negative response message with
//		NRC=RCRRP ( 0x78 - requestCorrectlyReceivedResponsePending) needs to be sent, then the final negative
//		response message using NRC=SNS (serviceNotSupported), NRC=SNSIAS (serviceNotSupportedIn-
//		ActiveSession), NRC=SFNS (sub-functionNotSupported), NRC=SFNSIAS (sub-functionNotSupportedIn-
//		ActiveSession) or NRC=ROOR (requestOutOfRange) shall also be sent if it is the result of the PDU analysis
//		of the received request message.(page 28, NRC 0x78, ISO 14229-1 2013)

		if (
				request_message->pdu.iso15765_protocol_data.target_address_type == functional_address_type &&
				(
					(response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_SNS) ||
					(response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_SFNS) ||
					(response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_SNSIAS) ||
					(response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_SFNSIAS) ||
					(response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_ROOR)
				)// 0�78 �� �� ����������� �������� 28 14229 1 2013 && (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] != NRC_RCRRP)
			) {
			// suppress negative response message
			release_iso15765_tp_response_instance(response_message);
		} else {
			if (suppress_uds_response) {
				release_iso15765_tp_response_instance(response_message);
			} else {
				write_response_message(response_message);
			}
		}

		release_iso15765_tp_request_instance(request_message);
		//TODO Initial start s3 timer of server is described on@ page 18, table 6, ISO 14229-2 2010
		if (uds_active_session != LEV_DS_DS) {
			start_uds_s_3_server_time_measurement();
		}
		return;
	} else {
		release_iso15765_tp_request_instance(request_message);

		//buffer is not available!!!)
//		uint8 service = request_message->pdu.iso15765_service_data.data[0];
//
//		response_message->pdu.iso15765_service_data.data[0] = 0x7F;
//		response_message->pdu.iso15765_service_data.data[1] = service;
//		response_message->pdu.iso15765_service_data.data[2] = NRC_BRR;
//		response_message->pdu.iso15765_protocol_data.length = 3;
//		response_message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = request_transmission;
//
//		write_response_message(response_message);
//		release_iso15765_tp_request_instance(response_message);
	}
}

static boolean with_subfunction(uint8 service)
{
	switch (service) {
	case DIAGSC:
	case ER:
	case SA:
	case CC:
	case TPRES:
	case RDTCI:
	case RC:
	case CDTCS:
		return TRUE;
	default:
		return FALSE;
	}
}
