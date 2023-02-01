#include "can_initialization.h"
#include "can_controller_settings.h"


IfxMultican_Can can;
IfxMultican_Can_Node canNode[CAN_MAX_CONTROLLERS];
IfxMultican_Can_MsgObj canMsgObj[256];

void module_configure(void);
void nodes_configure(void);
void message_objects_configure(void);

const struct can_message_config_s can_message_tx_config[CANIF_NUMBER_OF_CANTX_IDS] = {
	{FRAME_NAMI_EMS_04_ID,                    IfxMultican_DataLengthCode_8, HV, 0, 100}, 
	{FRAME_NAMI_EMS_03_ID,                    IfxMultican_DataLengthCode_8, HV, 1, 10}, 
	{FRAME_NAMI_EMS_02_ID,                    IfxMultican_DataLengthCode_8, HV, 2, 100}, 
	{FRAME_NAMI_EMS_01_ID,                    IfxMultican_DataLengthCode_8, HV, 3, 100}, 
	{FRAME_Diag_To_INC_ID,                    IfxMultican_DataLengthCode_8, HV, 4, 0}, 
	{FRAME_Diag_To_BMS_ID,                    IfxMultican_DataLengthCode_8, HV, 5, 0}, 
	{FRAME_Diag_Functional_ID,                IfxMultican_DataLengthCode_8, HV, 6, 0}, 
	{FRAME_BSC6LIM_ID,                        IfxMultican_DataLengthCode_6, HV, 7, 100}, 
	{FRAME_BSC6COM_ID,                        IfxMultican_DataLengthCode_3, HV, 8, 100}, 
	{FRAME_EMS_8_ID,                          IfxMultican_DataLengthCode_8, PT, 9, 10}, 
	{FRAME_EMS_7_ID,                          IfxMultican_DataLengthCode_4, PT, 10, 1000}, 
	{FRAME_EMS_4_ID,                          IfxMultican_DataLengthCode_7, PT, 11, 10}, 
	{FRAME_EMS_3_ID,                          IfxMultican_DataLengthCode_7, PT, 12, 10}, 
	{FRAME_EMS_2_ID,                          IfxMultican_DataLengthCode_6, PT, 13, 10}, 
	{FRAME_EMS_1_ID,                          IfxMultican_DataLengthCode_5, PT, 14, 1000}, 
	{FRAME_ECU_Indicators_ID,                 IfxMultican_DataLengthCode_3, PT, 15, 100}, 
	{FRAME_ECU_16_ID,                         IfxMultican_DataLengthCode_6, PT, 16, 20}, 
	{FRAME_ECU_14_ID,                         IfxMultican_DataLengthCode_8, PT, 17, 10}, 
	{FRAME_Diag_From_ECU_ID,                  IfxMultican_DataLengthCode_8, PT, 18, 0}, 
	{FRAME_EMS_HVC_Req_Msg_ID,                IfxMultican_DataLengthCode_3, PT, 19, 200}, 
	{FRAME_EMS_EEM_02_ID,                     IfxMultican_DataLengthCode_7, PT, 20, 100}, 
	{FRAME_EMS_EEM_01_ID,                     IfxMultican_DataLengthCode_7, PT, 21, 100}, 
	{FRAME_ECU_Veh_02_ID,                     IfxMultican_DataLengthCode_3, PT, 22, 20}, 
	{FRAME_ECU_Veh_ID,                        IfxMultican_DataLengthCode_8, PT, 23, 100}, 
	{FRAME_ECU_15_ID,                         IfxMultican_DataLengthCode_8, ESP, 24, 10}, 
};
const struct can_message_config_s can_message_rx_config[CANIF_NUMBER_OF_CANRX_IDS] = {
	{FRAME_Hyb_Sys_INV_05_ID,                 IfxMultican_DataLengthCode_8, HV, 255, 10}, 
	{FRAME_Hyb_Sys_INV_04_ID,                 IfxMultican_DataLengthCode_8, HV, 254, 500}, 
	{FRAME_Hyb_Sys_INV_03_ID,                 IfxMultican_DataLengthCode_8, HV, 253, 100}, 
	{FRAME_Hyb_Sys_INV_02_ID,                 IfxMultican_DataLengthCode_8, HV, 252, 100}, 
	{FRAME_Hyb_Sys_INV_01_ID,                 IfxMultican_DataLengthCode_8, HV, 251, 10}, 
	{FRAME_Hyb_Sys_DC_02_ID,                  IfxMultican_DataLengthCode_8, HV, 250, 100}, 
	{FRAME_Hyb_Sys_DC_01_ID,                  IfxMultican_DataLengthCode_8, HV, 249, 10}, 
	{FRAME_Hyb_Sys_BMS_04_ID,                 IfxMultican_DataLengthCode_8, HV, 248, 500}, 
	{FRAME_Hyb_Sys_BMS_03_ID,                 IfxMultican_DataLengthCode_8, HV, 247, 20}, 
	{FRAME_Hyb_Sys_BMS_02_ID,                 IfxMultican_DataLengthCode_8, HV, 246, 100}, 
	{FRAME_Hyb_Sys_BMS_01_ID,                 IfxMultican_DataLengthCode_8, HV, 245, 10}, 
	{FRAME_Diag_From_INC_ID,                  IfxMultican_DataLengthCode_8, HV, 244, 0}, 
	{FRAME_Diag_From_BMS_ID,                  IfxMultican_DataLengthCode_8, HV, 243, 0}, 
	{FRAME_BSC6VAL2_ID,                       IfxMultican_DataLengthCode_5, HV, 242, 100}, 
	{FRAME_BSC6VAL1_ID,                       IfxMultican_DataLengthCode_8, HV, 241, 100}, 
	{FRAME_TCU_R932_5_ID,                     IfxMultican_DataLengthCode_3, PT, 240, 100}, 
	{FRAME_TCU_R932_4_ID,                     IfxMultican_DataLengthCode_8, PT, 239, 10}, 
	{FRAME_TCU_R932_3_ID,                     IfxMultican_DataLengthCode_7, PT, 238, 10}, 
	{FRAME_TCU_R932_2_ID,                     IfxMultican_DataLengthCode_7, PT, 237, 10}, 
	{FRAME_HVC_HV_Status_Msg_ID,              IfxMultican_DataLengthCode_3, PT, 236, 50}, 
	{FRAME_Diag_To_ECU_ID,                    IfxMultican_DataLengthCode_8, PT, 235, 0}, 
	{FRAME_CDA_11_ID,                         IfxMultican_DataLengthCode_4, PT, 234, 20}, 
	{FRAME_VAU_EMS_Hash_Immo_RESP_ID,         IfxMultican_DataLengthCode_8, PT, 233, 0}, 
	{FRAME_TCU_R932_1_ID,                     IfxMultican_DataLengthCode_8, PT, 232, 10}, 
	{FRAME_SAS_Standard_ID,                   IfxMultican_DataLengthCode_5, PT, 231, 10}, 
	{FRAME_EPB_Status_ID,                     IfxMultican_DataLengthCode_5, PT, 230, 20}, 
	{FRAME_Diag_Functional_FromPT_ID,         IfxMultican_DataLengthCode_8, PT, 229, 0}, 
	{FRAME_DMS_01_ID,                         IfxMultican_DataLengthCode_3, PT, 228, 100}, 
	{FRAME_CCU_MSG3_ID,                       IfxMultican_DataLengthCode_5, PT, 227, 500}, 
	{FRAME_CCU_HVC_Req_Msg_ID,                IfxMultican_DataLengthCode_3, PT, 226, 200}, 
	{FRAME_BCM_VEH_STATE_ID,                  IfxMultican_DataLengthCode_8, PT, 225, 50}, 
	{FRAME_BCM_Powertrain_ID,                 IfxMultican_DataLengthCode_6, PT, 224, 10}, 
	{FRAME_BCM_EEM_ID,                        IfxMultican_DataLengthCode_8, PT, 223, 100}, 
	{FRAME_ACU_01_ID,                         IfxMultican_DataLengthCode_3, PT, 222, 100}, 
	{FRAME_ESP_YRS_03_ID,                     IfxMultican_DataLengthCode_8, ESP, 221, 10}, 
	{FRAME_ESP_01_ID,                         IfxMultican_DataLengthCode_8, ESP, 220, 10}, 
	{FRAME_ESP_03_ID,                         IfxMultican_DataLengthCode_8, ESP, 219, 10}, 
	{FRAME_ESP_02_ID,                         IfxMultican_DataLengthCode_8, ESP, 218, 10}, 
	{FRAME_ESP_04_ID,                         IfxMultican_DataLengthCode_8, ESP, 217, 20}, 
};

void can_initialize(void)
{
	module_configure();
	nodes_configure();
	message_objects_configure();
}

void module_configure(void)
{
	// create configuration
	IfxMultican_Can_Config canConfig;
	IfxMultican_Can_initModuleConfig(&canConfig, &MODULE_CAN);
	// initialize module
	IfxMultican_Can_initModule(&can, &canConfig);
}

void node_config(const Can_ControllerSettingsType *controller_settings, uint8 node_number)
{
	// create CAN node configuration
	IfxMultican_Can_NodeConfig canNodeConfig;
	IfxMultican_Can_Node_initConfig(&canNodeConfig, &can);

	// Source Node
	{
		canNodeConfig.baudrate =  controller_settings->baudrate;
		canNodeConfig.nodeId =    controller_settings->controllerID;
		canNodeConfig.rxPin =     controller_settings->setRxPin;
		canNodeConfig.rxPinMode = IfxPort_InputMode_pullUp;
		canNodeConfig.txPin =     controller_settings->setTxPin;
		canNodeConfig.txPinMode = IfxPort_OutputMode_pushPull;
		// initialize the node
		IfxMultican_Can_Node_init(&canNode[node_number], &canNodeConfig);
	}
}

void mess_object_tx_config(const struct can_message_config_s *mo_option)
{
	// IfxMultican_Can_MsgObj canSrcMsgObj; // defined globally
	{
		// create message object configuration
		IfxMultican_Can_MsgObjConfig canMsgObjConfig;
		IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode[mo_option->node_number]);
		// assigned message object:
		canMsgObjConfig.msgObjId = mo_option->message_object_id;
		canMsgObjConfig.messageId = mo_option->id;
		canMsgObjConfig.acceptanceMask = 0x7FFFFFFFUL;
		canMsgObjConfig.frame = IfxMultican_Frame_transmit;
		canMsgObjConfig.control.messageLen = mo_option->dlc;
		canMsgObjConfig.control.extendedFrame = FALSE;
		canMsgObjConfig.control.matchingId = TRUE;
		// initialize message object
		IfxMultican_Can_MsgObj_init(&canMsgObj[(mo_option->message_object_id)], &canMsgObjConfig);
	}
}

void mess_object_rx_config(const struct can_message_config_s *mo_option)
{
	// IfxMultican_Can_MsgObj canSrcMsgObj; // defined globally
	{
		// create message object configuration
		IfxMultican_Can_MsgObjConfig canMsgObjConfig;
		IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canNode[mo_option->node_number]);
		// assigned message object:
		canMsgObjConfig.msgObjId = mo_option->message_object_id;
		canMsgObjConfig.messageId = mo_option->id;
		canMsgObjConfig.acceptanceMask = 0x7FFFFFFFUL;
		canMsgObjConfig.frame = IfxMultican_Frame_receive;
		canMsgObjConfig.control.messageLen = mo_option->dlc;
		canMsgObjConfig.control.extendedFrame = FALSE;
		canMsgObjConfig.control.matchingId = TRUE;

		// initialize message object
		IfxMultican_Can_MsgObj_init(&canMsgObj[(mo_option->message_object_id)], &canMsgObjConfig);
	}
}

void nodes_configure(void)
{
	uint8 i;
	for(i=0; i<CAN_MAX_CONTROLLERS; i++) {
		node_config(&Can_ControllerSettings[i], i);
	}
}

void message_objects_configure(void)
{
	uint8 i;
	for(i=0; i<CANIF_NUMBER_OF_CANTX_IDS; i++) {
		mess_object_tx_config(&can_message_tx_config[i]);
	}

	for(i=0; i<CANIF_NUMBER_OF_CANRX_IDS; i++) {
		mess_object_rx_config(&can_message_rx_config[i]);
	}
}
