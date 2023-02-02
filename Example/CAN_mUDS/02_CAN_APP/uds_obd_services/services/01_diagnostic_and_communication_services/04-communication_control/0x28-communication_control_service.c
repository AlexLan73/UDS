#include "communication_control_private.h"

uint8 communication_control(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	uint8 control_type = request_message->pdu.iso15765_service_data.data[1];
	enum communication_messages_type_e communication_type = request_message->pdu.iso15765_service_data.data[2] & 0x03; //B.1 communicationType parameter @ref ISO 14229-1 2013 page 333

	if (!check_condition_for_communication_control()) {
		return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_CNC;
	}

	switch (control_type) {
	case LEV_CTRLTP_ERXTX:
				if ((request_message->pdu.iso15765_protocol_data.length) != CC_LEN_WITHOUT_NIN) {
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
				}

				switch (communication_type) {
				case normal_cm:
					enable_tx();
					enable_rx();
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				case network_management_cm:
				case normal_and_network_management_cm:
				default:
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
				}
				break;
	case LEV_CTRLTP_ERXDTX:
				if ((request_message->pdu.iso15765_protocol_data.length) != CC_LEN_WITHOUT_NIN) {
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
				}

				switch (communication_type) {
				case normal_cm:
					disable_tx();
					enable_rx();
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				case network_management_cm:
				case normal_and_network_management_cm:
				default:
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
				}
				break;
	case LEV_CTRLTP_DRXTX:
				if ((request_message->pdu.iso15765_protocol_data.length) != CC_LEN_WITHOUT_NIN) {
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
				}

				switch(communication_type) {
				case normal_cm:
					disable_tx();
					disable_rx();
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				case network_management_cm:
				case normal_and_network_management_cm:
				default:
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
				}
				break;
	case LEV_CTRLTP_ERXDTXWEAI:
	case LEV_CTRLTP_DRXETX:
	case LEV_CTRLTP_ERXTXWEAI:
	default:
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SFNS;
	}
}

static uint8 check_condition_for_communication_control(void)
{
	//TODO ignition = on, engine = off, vehicle speed = 0 [kph] ????)
	return 1;
}


//static uint8 IfxMultican_MsgObj_disable_rx_mo(void)
//{
//	IfxMultican_Can_MsgObj* MO = &canMsgObj[2];
//	Ifx_CAN           *mcanSFR   = MO->node->mcan;
//	Ifx_CAN_MO        *hwObj     = IfxMultican_MsgObj_getPointer(mcanSFR, MO->msgObjId);
//	/*
//	Ifx_CAN_MO_CTR ctr;
//	ctr.B.RESRXEN        = 0;
//
//	ctr.U        = 1U << (flag + 16);
//	*/
//	hwObj->CTR.B.RESRXEN = 0;
//	return 1;
//}
//
//static uint8 IfxMultican_MsgObj_disable_tx_mo(void)
//{
//	IfxMultican_Can_MsgObj* MO = &canMsgObj[21];
//	Ifx_CAN           *mcanSFR   = MO->node->mcan;
//	Ifx_CAN_MO        *hwObj     = IfxMultican_MsgObj_getPointer(mcanSFR, MO->msgObjId);
//	/*
//	Ifx_CAN_MO_CTR ctr;
//	ctr.B.RESRXEN        = 0;
//
//	ctr.U        = 1U << (flag + 16);
//	*/
//	hwObj->CTR.B.SETTXEN0 = 0;
//	hwObj->CTR.B.RESTXEN0 = 1;
//	return 1;
//}
//
//static uint8 IfxMultican_MsgObj_enable_tx_mo(void)
//{
//	IfxMultican_Can_MsgObj* MO = &canMsgObj[21];
//	Ifx_CAN           *mcanSFR   = MO->node->mcan;
//	Ifx_CAN_MO        *hwObj     = IfxMultican_MsgObj_getPointer(mcanSFR, MO->msgObjId);
//	/*
//	Ifx_CAN_MO_CTR ctr;
//	ctr.B.RESRXEN        = 0;
//
//	ctr.U        = 1U << (flag + 16);
//	*/
//	hwObj->CTR.B.SETTXEN0 = 1;
//	hwObj->CTR.B.RESTXEN0 = 0;
//	return 1;
//}
//
//static uint8 IfxMultican_MsgObj_disable_rx_tx_mo(void)
//{
//	IfxMultican_MsgObj_disable_rx_mo();
//	IfxMultican_MsgObj_disable_tx_mo();
//	return 1;
//}
//
//IFX_INLINE void IfxMultican_Node_TXDIS(Ifx_CAN_N *hwNode, boolean enabled)
//{
//    hwNode->CR.B.TXDIS = enabled ? 1 : 0;
//}

//uint8 enable_tx(void)
//{
//
//}
//
//uint8 enable_rx(void)
//{
//
//}
//
//
//uint8 disable_tx(void)
//{
//
//}
//
//uint8 disable_rx(void)
//{
//
//}


