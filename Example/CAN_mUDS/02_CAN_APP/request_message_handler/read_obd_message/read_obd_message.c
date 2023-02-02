#include "read_obd_message.h"
#include "process_request_message_segments.h"
#include "process_response_segment.h"
#include "uds_timers.h"
#include "can_initialization.h"

void read_obd_message(struct iso15765_tp_s* request_message)
{
	//TODO if response_message == NULL_PTR, need to process the request. Make a request later.
	struct iso15765_tp_s* response_message = get_iso15765_tp_response_instance_for(request_message->pdu.iso15765_protocol_data.source_address);
	if (response_message != NULL_PTR) {
		//---------------------------------------------------------------------------------------------------------------------------------------
		// response_message configuration
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

		if (0/*this server instance busy*/) { //TODO !!!! if server receives uds request after to receive app.indication primitive it will destroy the first message
			//need to lock instance after app.indication primitive

			response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_BRR;

			response_message->pdu.iso15765_service_data.data[0] = 0x7F;
			response_message->pdu.iso15765_service_data.data[1] = service;
			response_message->pdu.iso15765_service_data.data[2] = response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER];

			response_message->pdu.iso15765_protocol_data.length = 3;
		} else {
			switch (service) {
			//OBD services

			//	All emissions-related OBD ECUs which at least support one of the services defined
			//	in part of ISO 15031-5, shall support Service 01 and PID 00 (ISO 15031-5 2015, page 92)
//			case RCPDD:
//				request_current_powertrain_diagnostic_data(response_message, request_message);
//				break;
//			case RPFFD:
//				break;
//			case RERDTC:
//				break;
//			case CRERDI:
//				break;
//			case ROSMTR:
//				break;
//			case ROBMTRSMS:
//				break;
//			case RERDTCDDCLCDC:
//				break;
//			case RCOBSTC:
//				break;
//			case RVI:
//				request_vehicle_information(response_message, request_message);
//				break;
			default:
				response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SNS;

				response_message->pdu.iso15765_service_data.data[0] = 0x7F;
				response_message->pdu.iso15765_service_data.data[1] = service;
				response_message->pdu.iso15765_service_data.data[2] = response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER];

				response_message->pdu.iso15765_protocol_data.length = 3;

				suppress_uds_response = 0;
				break;
			}
		}


		// todo check below conditions
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
				// suppress response message
				release_iso15765_tp_response_instance(response_message);
			} else {
				// send negative or positive response
				write_response_message(response_message);
			}
		}

		release_iso15765_tp_request_instance(request_message);
		//TODO Initial start s3 timer of server is described on@ page 18, table 6, ISO 14229-2 2010
		if (uds_active_session != LEV_DS_DS) {
			start_uds_s_3_server_time_measurement();
		}

		if (response_message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] == confirmation) {
			if (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] != N_OK) { //TODO condition
				response_message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = unknown_message;
			} else {
				response_message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = unknown_message;
			}
		}
		return;
	} else {
		release_iso15765_tp_request_instance(request_message);
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


