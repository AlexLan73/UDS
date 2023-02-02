//#include "control_dtc_setting_private.h"
//
//void control_dtc_setting(struct data_units* response_message,struct data_units* request_message)
//{
//	if ((request_message->length) >= MIN_MESSAGE_LENGTH_WITH_SUBFUNCTION) {
//		if ((active_session == LEV_DS_PRGS) || (active_session == LEV_DS_EXTDS)) {
//			uint8 sub_function = request_message->data[1];
//			switch (sub_function) {
//			case LEV_DTCSTP_ON:
//				if ((request_message->length) == CDTCS_LEN) {
//					if (switch_on_the_dtc_status_bit_updating()) { //TODO p363  -DTC Status Update Condition
//						response_message->data[0] = RDTCSPR;
//						response_message->data[1] = LEV_DTCSTP_ON;
//						response_message->length = 2;
//					} else {
//						response_message->result[APPLICATION_LAYER] = NRC_CNC;
//					}
//				} else {
//					response_message->result[APPLICATION_LAYER] = NRC_IMLOIF;
//				}
//				break;
//			case LEV_DTCSTP_OFF:
//				if ((request_message->length) == CDTCS_LEN) {
//					if (switch_off_the_dtc_status_bit_updating()) { //TODO
//						response_message->data[0] = RDTCSPR;
//						response_message->data[1] = LEV_DTCSTP_OFF;
//						response_message->length = 2;
//					} else {
//						response_message->result[APPLICATION_LAYER] = NRC_CNC;
//					}
//				} else {
//					response_message->result[APPLICATION_LAYER] = NRC_IMLOIF;
//				}
//				break;
//			default:
//				response_message->result[APPLICATION_LAYER] = NRC_SFNS;
//				break;
//			}
//		} else {
//			response_message->result[APPLICATION_LAYER] = NRC_SNSIAS;
//		}
//	} else {
//		response_message->result[APPLICATION_LAYER] = NRC_IMLOIF;
//	}
//
//	if (response_message->result[APPLICATION_LAYER]) {
//		response_message->data[0] = 0x7F;
//		response_message->data[1] = CDTCS;
//		response_message->data[2] = response_message->result[APPLICATION_LAYER];
//
//		response_message->length = 3;
//	}
//
//	uint8 suppress_pos_rsp_msg_indication_bit = (request_message->data[1] & 0x80);
//
//	if((suppress_pos_rsp_msg_indication_bit) && (response_message->result[APPLICATION_LAYER] == NRC_PR)) { // && (“not yet a NRC NRC_RCRRP 0x78  response sent”))
//		suppress_response = 1;
//	} else {
//		suppress_response = 0;
//	}
//}
//
//static uint8 switch_on_the_dtc_status_bit_updating(void)
//{
//	return 1;
//}
//
//static uint8 switch_off_the_dtc_status_bit_updating(void)
//{
//	return 1;
//}
