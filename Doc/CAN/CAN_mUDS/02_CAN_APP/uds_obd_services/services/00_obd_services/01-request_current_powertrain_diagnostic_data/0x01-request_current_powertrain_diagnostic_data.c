#include "request_current_powertrain_diagnostic_data_private.h"

//---------------------------------------------------------------------------------------------------------------
// GLOBAL
//---------------------------------------------------------------------------------------------------------------

void request_current_powertrain_diagnostic_data(struct iso15765_tp_s* response_message, struct iso15765_tp_s* request_message)
{
	//ISO 15031-5 2015
	//To request PIDs supported range from C1 to FF, another request message with PID#1 = C0 and PID#2 = E0 shall be sent to the vehicle.


	/* The request message may contain up to six (6) PIDs.(ISO 15031-5 2015 page 92)*/
	if ((request_message->pdu.iso15765_protocol_data.length >= 2/*SID + 1 PID*/) &&
			(request_message->pdu.iso15765_protocol_data.length <= 7/*SID + 6 PID*/)) {
		uint8 i;
		uint8 number_of_parameter_ids= (request_message->pdu.iso15765_protocol_data.length - 1);
		uint8 pid;
		uint8 supported_pid_counter = 0;
		uint8 response_message_data_index = 0;
		response_message->pdu.iso15765_service_data.data[response_message_data_index++] = 0x41;
		response_message->pdu.iso15765_protocol_data.length = 1;

		/*The request message may contain the same PID multiple times. The ECU shall treat
			each PID as a separate parameter and respond with data for each PID (ISO 15031-5 2015 page 92)*/

		/*
		 * 	External test equipment is not allowed to request
		 * 	a combination of PIDs supported and PIDs which report
		 * 	data values.(ISO 15031-5 2015 page 92)
		 */
		if (check_type_condition(request_message, number_of_parameter_ids)) {
			for(i = 0; i < number_of_parameter_ids; i++) {
				pid = request_message->pdu.iso15765_service_data.data[i+1];
				if (pid_support_in_obd_service(pid)) {
					supported_pid_counter++;
					//if "pid" is not supported, "response_message_data_index" is not changed
					response_message_data_index = add_pid_info_to_response_message(
							response_message,
							response_message_data_index,
							pid
							);
				}
			}
		}
		if (supported_pid_counter) {

		}
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
	} else {
		//TODO fulfill conditions for NRC 0x21(Page 34 Table 11 ISO 15031-5 2015)
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
	}

	//if no pdid is supported - suppress response
	if (response_message->pdu.iso15765_protocol_data.length) {
		suppress_uds_response = 0;
	} else {
		suppress_uds_response = 1;
	}
}
//---------------------------------------------------------------------------------------------------------------







//---------------------------------------------------------------------------------------------------------------
// STATIC
//---------------------------------------------------------------------------------------------------------------

static boolean check_type_condition(struct iso15765_tp_s* request_message, uint8 number_of_parameter_id)
{
	uint8 	first_pid_idx_number = 1;
	uint8   pid_idx = first_pid_idx_number;
	enum info_t {
		supported_pid,
		data_pid
	} curr;

	switch (request_message->pdu.iso15765_service_data.data[pid_idx++]) {
	case PID_00:
	case PID_20:
	case PID_40:
	case PID_60:
	case PID_80:
	case PID_A0:
	case PID_C0:
	case PID_E0:
		curr = supported_pid;
		break;
	default:
		curr = data_pid;
		break;
	}

	for(;pid_idx < number_of_parameter_id; pid_idx++) {
		enum info_t temp;
		switch (request_message->pdu.iso15765_service_data.data[pid_idx]) {
		case PID_00:
		case PID_20:
		case PID_40:
		case PID_60:
		case PID_80:
		case PID_A0:
		case PID_C0:
		case PID_E0:
			temp = supported_pid;
			break;
		default:
			temp = data_pid;
			break;
		}
		if (temp != curr) {return FALSE;}
	}
	return TRUE;
}

static uint16 add_pid_info_to_response_message(struct iso15765_tp_s* response_message, uint16  temp_index, uint16 parameter_id)
{
	switch (parameter_id) {
	//------------------------------------------------------------
	// Supported parameters request (page 2 TABLE A1 SAE J1979-DA 2011)
	//------------------------------------------------------------
	case PID_00://support for PIDs 0x01 through 0x20
		//A range is defined as a block of 32 PIDs
		//TODO for pid 00: Positive response is required or	negative response for max of !! 5 times !!. Page 34 Table 11 ISO 15031-5 2015
		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00; 	//0xFF ->11111111->order:bit7 - PID1,bit6 - PID2,PID3...PID8(1-support, 0-not) Example: 00010110 - >support pids: 4,6,7
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_20: //support for PIDs 21 through 40
		/*if pid is not supported server doesn't add info*/
		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;			//DATA_A
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;			//DATA_B
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;			//DATA_C
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;			//DATA_D
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_40: //support for PIDs 41 through 60
		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_60:
		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_80:
//		response_message->pdu.iso15765_service_data.data[temp_index++]   = parameter_id;
//		response_message->pdu.iso15765_service_data.data[temp_index++]   = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_A0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_C0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case PID_E0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = parameter_id;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
//------------------------------------------------------------


	default:
		break;

	}
	return temp_index;
}

static uint8 pid_support_in_obd_service(uint8 parameter_id)
{
	return 1;
}
