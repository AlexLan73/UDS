#include "read_data_by_identifier_private.h"

//---------------------------------------------------------------------------------------------------------------
// GLOBAL
//---------------------------------------------------------------------------------------------------------------

uint8 read_data_by_id(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	if (!((request_message->pdu.iso15765_protocol_data.length - 1)%2) && (request_message->pdu.iso15765_protocol_data.length >= 3/*MIN_RDBI_LEN=SID+2byteId*/)) {
		uint8   i;
		uint8   number_of_parameter_id = ((request_message->pdu.iso15765_protocol_data.length - 1)/2);
		uint16  parameter_id;
		uint8   supported_did = 0;

		response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDBIPR;
		response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx; //because data[0] = SID

		for(i = 0; i < number_of_parameter_id; i++) {
			parameter_id = (((uint16)request_message->pdu.iso15765_service_data.data[(1+(i*2))])<<8)+request_message->pdu.iso15765_service_data.data[(2+(i*2))];
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = request_message->pdu.iso15765_service_data.data[(1+(i*2))];
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = request_message->pdu.iso15765_service_data.data[(2+(i*2))];
							response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
//			UDS_0x22_SCU(parameter_id);
			supported_did++;

//			if (access_granted(parameter_id)) {
//				supported_did++;
//				//if "pid" is not supported, "response_message->pdu.iso15765_service_data.buffer_idx" is not changed
//				response_message->pdu.iso15765_service_data.buffer_idx = add_pid_info_to_response_message(
//						response_message,
//						response_message->pdu.iso15765_service_data.buffer_idx,
//						parameter_id
//						);
//				response_mresponse_message->pdu.iso15765_service_data.buffer_idxol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
//			} else {
//				// This NRC shall be sent if at least one of the dataIdentifiers is secured and
//				//the server is not in an unlocked state.(@page 109 14229-1 2013 table 146)
//				response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SAD;
//				break;
//			}
		}

		if (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] != NRC_SAD) {
			if (supported_did) {
				if (supported_did <= TOTAL_RESPONSE_LENGTH_EXCEEDED) {
					return NRC_PR;
				} else {
					return NRC_RTL;
				}
			} else {
				return NRC_ROOR;
			}
		}
	} else {
		return NRC_IMLOIF;
	}
}
//---------------------------------------------------------------------------------------------------------------







//---------------------------------------------------------------------------------------------------------------
// STATIC
//---------------------------------------------------------------------------------------------------------------

static boolean access_granted(uint16 parameter_id)
{
	// TODO pid is support. Some predefined IDs, boundaries are described on @page 345 14229-1 2013 into table C.1
	// TODO support in active session
	// TODO security level eq 1 or 2


	switch (parameter_id) {
	case UDS_VERSION:
	case SYSTEM_NAME_ENGINE_TYPE:
		return TRUE;
	default:
		return FALSE;
	}
}

static uint16 add_pid_info_to_response_message(struct iso15765_tp_s* response_message, uint16  temp_index, uint16 parameter_id)
{
	//TODO need to determine these parameters in other file
	//Coding of UDS version number is described @page 352 14229-1 2013 into C.5 section
	uint8 uds_version[4] = {0x00, 0x01, 0x01, 0x01};
	uint8 ecu_name[] = "EMC1-DINGDONGMO0000R"; //TODO duplacate of 0x09 service

	switch (parameter_id) {
	//------------------------------------------------------------
	// Some predefined IDs, boundaries are described on
	//@page 345 14229-1 2013 into table C.1
	//------------------------------------------------------------
	case UDS_VERSION/*uds_version_did*/:
		//Coding of UDS version number is described @page 352 14229-1 2013 into annex C.5

		response_message->pdu.iso15765_service_data.data[temp_index++] = 0xFF;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;

		response_message->pdu.iso15765_service_data.data[temp_index++] = uds_version[0];
		response_message->pdu.iso15765_service_data.data[temp_index++] = uds_version[1];
		response_message->pdu.iso15765_service_data.data[temp_index++] = uds_version[2];
		response_message->pdu.iso15765_service_data.data[temp_index++] = uds_version[3];
		break;
	case SYSTEM_NAME_ENGINE_TYPE:
		response_message->pdu.iso15765_service_data.data[temp_index++]   = 0xF1;
		response_message->pdu.iso15765_service_data.data[temp_index++]   = 0x97;

		//MAX LENGH - 20 ASCII characters (page 136, table G10, SAE J1979-DA 2011
		uint8 char_idx = 0;
		for(; char_idx < 20/*sizeof(some_str)*/; char_idx++) {
			//TODO check total string length
			if (ecu_name[char_idx] == '\0') {
				break;
			}
			response_message->pdu.iso15765_service_data.data[temp_index++] = ecu_name[char_idx];
		}
		break;
	default:
		break;
	}

	return temp_index;
}
