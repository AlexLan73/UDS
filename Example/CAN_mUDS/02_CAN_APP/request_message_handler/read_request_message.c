#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"
#include "can_initialization.h"
#include "process_request_message_segments.h"
#include "read_obd_message.h"
#include "read_uds_message.h"
#include "uds_timers.h"

enum protocol_type {
	unknown_protocol,
	obd_protocol,
	uds_protocol
};

static enum protocol_type determine_protocol(uint8 byte);

void read_request_message(struct iso15765_tp_s* message)
{
	message->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = unknown_message;
	message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = unknown_message;

	if (message->pdu.iso15765_protocol_data.result[NETWORK_LAYER] == N_OK) {
		if (message->pdu.iso15765_protocol_data.target_address == server_parameter[0].server_address ||
				message->pdu.iso15765_protocol_data.target_address == server_parameter[0].broadcast_address) {
			switch (determine_protocol(message->pdu.iso15765_service_data.data[0])) {
			case obd_protocol:
				read_obd_message(message);
				break;
			case uds_protocol:
				start_uds_p_2_server_time_measurement();
				//TODO Need to determine "tester present" service. That is session layer.
				read_uds_message(message);
				break;
			case unknown_protocol:
			default:
				release_iso15765_tp_request_instance(message);
				break;
			}
		} else {
			release_iso15765_tp_request_instance(message);
		}



//		switch (message->pdu.iso15765_protocol_data.target_address) {
//		case PHY_DIAG_REQ_CAN_ID:
//		case FUNC_DIAG_REQ_CAN_ID:
//			switch (determine_protocol(message->pdu.iso15765_service_data.data[0])) {
//			case obd_protocol:
//				read_obd_message(message);
//				break;
//			case uds_protocol:
//				start_uds_p_2_server_time_measurement();
//				//TODO Need to determine "tester present" service. That is session layer.
//				read_uds_message(message);
//				break;
//			case unknown_protocol:
//			default:
//				release_iso15765_tp_request_instance(message);
//				break;
//			}
//			break;
//		default:
//			release_iso15765_tp_request_instance(message);
//			break;
//		}
	} else {
		message->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK; //TODO error handler
		release_iso15765_tp_request_instance(message);
	}
}

void function_to_get_first_frame(struct iso15765_tp_s* message)
{
	//start some timers; todo something!!
	message->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = idle;
}

static enum protocol_type determine_protocol(uint8 byte)
{//TODO
	switch (byte) {
	case 0:
	case RCPDD:
	case RPFFD:
	case RERDTC:
	case CRERDI:
	case ROSMTR:
	case ROBMTRSMS:
	case RERDTCDDCLCDC:
	case RCOBSTC:
	case RVI:
		return obd_protocol;
	case DIAGSC:
	case ER:
	case SA:
	case CC:
	case TPRES:
    case ATP:
    case SDATAT:
    case CDTCS:
    case ROE:
    case LC:
    case RDBI:
    case RMBA:
    case RSDBI:
    case RDBPI:
    case DDDI:
    case WDBI:
    case WMBA:
    case CDTCI:
    case RDTCI:
    case IOCBI:
    case RC:
    case RD:
    case RU:
    case TD:
    case RTE:
    case RFT:
//	case DIAGSC:
//	case ER:
//	case SA:
//	case CC:
//	case TPRES:
//	case RDTCI:
//	case RC:
//	case RDBI:
//	case CDTCI:
		return uds_protocol;
	default:
		return unknown_protocol;
	}
	return unknown_protocol;
}
