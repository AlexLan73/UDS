#include "request_vehicle_information_private.h"

//---------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------

void request_vehicle_information(struct iso15765_tp_s* response_message, struct iso15765_tp_s* request_message)
{
	// The request message including supported INFOTYPEs may contain up to six (6) INFOTYPEs.(ISO 15031-5 2015 page 125)
	if ((request_message->pdu.iso15765_protocol_data.length >= 2/*SID + 1 INFOTYPE*/) &&
				(request_message->pdu.iso15765_protocol_data.length <= 7/*SID + 6 INFOTYPE*/)) {
		uint8   i;
		uint8   number_of_infotypes= (request_message->pdu.iso15765_protocol_data.length - 1);
		//SAE J1979-DA 2011, info_type, page 131
		uint8  	info_type;
		uint8   supported_infotypes_counter = 0;
		uint16  response_message_data_index = 0;
		response_message->pdu.iso15765_service_data.data[response_message_data_index++] = 0x49;
		response_message->pdu.iso15765_protocol_data.length = 0;

		/*
		 * 	External test equipment is not allowed to request
		 * 	a combination of INFOTYPEs supported and a single INFOTYPEs which report
		 * 	vihicle information.(ISO 15031-5 2015 page 125)
		 */
		if (check_type_condition(request_message, number_of_infotypes)) {
			for(i = 0; i < number_of_infotypes; i++) {
				info_type = request_message->pdu.iso15765_service_data.data[i+1];
				if (infotype_support_in_obd_service(info_type)) {
					supported_infotypes_counter++;
					//if "infotype" is not supported "response_message_data_index" is not changed
					response_message_data_index = add_infotype_info_to_response_message(
							response_message,
							response_message_data_index,
							info_type
							);
				}
			}
		}
		if (supported_infotypes_counter) {

		}
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
	} else {
		//TODO fulfill conditions for NRC 0x22 Page 36 Table 11 ISO 15031-5 2015
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
	}


	uint8 suppress_pos_rsp_msg_indication_bit;

	//if no pdid is supported - suppress response
	if (response_message->pdu.iso15765_protocol_data.length) {
		suppress_pos_rsp_msg_indication_bit = (request_message->pdu.iso15765_service_data.data[1] & 0x80);
	} else {
		suppress_pos_rsp_msg_indication_bit = 1;
	}

	if((suppress_pos_rsp_msg_indication_bit) && (response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] == NRC_PR)){// && (â€œnot yet a NRC NRC_RCRRP 0x78  response sentâ€�))
		suppress_uds_response = 1;
	} else {
		suppress_uds_response = 0;
	}
}

//---------------------------------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------------------------------
// STATIC
//---------------------------------------------------------------------------------------------------------------
static boolean check_type_condition(struct iso15765_tp_s* request_message, uint8 number_of_infotypes)
{
	uint8 	first_infotype_idx_number = 1;
	uint8   infotype_idx = first_infotype_idx_number;
	enum info_t {
		supported_infotype,
		single_infotype
	} curr;

	switch (request_message->pdu.iso15765_service_data.data[infotype_idx]) {
	case INFOTYPE_00:
	case INFOTYPE_20:
	case INFOTYPE_40:
	case INFOTYPE_60:
	case INFOTYPE_80:
	case INFOTYPE_A0:
	case INFOTYPE_C0:
	case INFOTYPE_E0:
		curr = supported_infotype;
		break;
	default:
		curr = single_infotype;
		break;
	}
	infotype_idx++;
	for(;infotype_idx < number_of_infotypes; infotype_idx++) {
		enum info_t temp;
		switch (request_message->pdu.iso15765_service_data.data[infotype_idx]) {
		case INFOTYPE_00:
		case INFOTYPE_20:
		case INFOTYPE_40:
		case INFOTYPE_60:
		case INFOTYPE_80:
		case INFOTYPE_A0:
		case INFOTYPE_C0:
		case INFOTYPE_E0:
			temp = supported_infotype;
			break;
		default:
			temp = single_infotype;
			break;
		}
		if (temp != curr) {return 0;}
	}
	return 1;
}


static uint16 add_infotype_info_to_response_message(struct iso15765_tp_s* response_message, uint16  temp_index, uint16 infotype)
{
	switch (infotype) {
	//------------------------------------------------------------
	// Supported INFOTYPEs (page 2 TABLE A1 SAE J1979-DA 2011)
	//------------------------------------------------------------
	case INFOTYPE_00://support for INFOTYPEs 0x01 through 0x20
		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x55; 	//0xFF ->11111111->order:bit7 - INFOTYPE1,bit6 - INFOTYPE2,INFOTYPE3...INFOTYPE8(1-support, 0-not) Example: 00010110 - >support INFOTYPEs: 0x04,0x06,0x07
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x4A;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_20: //support for INFOTYPEs 0x21 through 0x40 ()
		/*if infotype is not supported server doesn't add info*/
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_40: //support for INFOTYPEs 41 through 60
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_60:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_80:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_A0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_C0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_E0:
//		response_message->pdu.iso15765_service_data.data[temp_index++] = infotype;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_service_data.data[temp_index++] = 0x00;
//		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	//------------------------------------------------------------

	case INFOTYPE_VIN:
		// ECU may respond with 0xFF characters for VIN because the VIN has not been programmed(ISO 15031-5 2015 page 125)
		// MAX LENGH - 17 ASCII characters (page 131, table G2, SAE J1979-DA 2011)
		// description on page 131, SAE J1979-DA 2011
		response_message->pdu.iso15765_service_data.data[temp_index++] = INFOTYPE_VIN;
		response_message->pdu.iso15765_service_data.data[temp_index++] = 0xFF;
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_CALID:
		break;
	case INFOTYPE_CALCVN:
		break;
	case INFOTYPE_IPT:
		break;
	case INFOTYPE_ECU_NAME:
		// description on page 136, SAE J1979-DA 2011
		response_message->pdu.iso15765_service_data.data[temp_index++]   = infotype;

		//MAX LENGH - 20 ASCII characters (page 136, table G10, SAE J1979-DA 2011)
		uint8 ecu_name[] = "EMC1-DINGDONGMO0000R";
		uint8 char_idx = 0;
		for(; char_idx < 20/*sizeof(some_str)*/; char_idx++) {
			//TODO check total string length
			if (ecu_name[char_idx] == '\0') {
				break;
			}
			response_message->pdu.iso15765_service_data.data[temp_index++] = ecu_name[char_idx];
		}
		response_message->pdu.iso15765_protocol_data.length = temp_index;
		break;
	case INFOTYPE_ESN:
		break;
	case INFOTYPE_EROTAN:
		break;
	default:
		break;

	}

	return temp_index;
}

static uint8 infotype_support_in_obd_service(uint8 infotype)
{
	return 1;
}
