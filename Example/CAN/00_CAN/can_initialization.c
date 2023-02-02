#include "can_initialization.h"
#include "can_controller_settings.h"


IfxMultican_Can can;
IfxMultican_Can_Node canNode[CAN_MAX_CONTROLLERS];
IfxMultican_Can_MsgObj canMsgObj[256];

void module_configure(void);
void nodes_configure(void);
void message_objects_configure(void);

void (*TXcollect_infoPtr[CANIF_NUMBER_OF_CANTX_IDS])(struct can_message_s* tx_mess);
#define GCAN PT
const struct can_message_config_s can_message_tx_config[CANIF_NUMBER_OF_CANTX_IDS] = {
	{FRAME_EMS_VCU_03_ID,                     IfxMultican_DataLengthCode_8, GCAN, 0, 10}, 
	{FRAME_EMS_VCU_02_ID,                     IfxMultican_DataLengthCode_8, GCAN, 1, 10}, 
	{FRAME_EMS_VCU_01_ID,                     IfxMultican_DataLengthCode_8, GCAN, 2, 10}, 
	{FRAME_NAMI_EMS_04_ID,                    IfxMultican_DataLengthCode_8, HV, 3, 100}, 
	{FRAME_NAMI_EMS_03_ID,                    IfxMultican_DataLengthCode_8, HV, 4, 10}, 
	{FRAME_NAMI_EMS_02_ID,                    IfxMultican_DataLengthCode_8, HV, 5, 100}, 
	{FRAME_NAMI_EMS_01_ID,                    IfxMultican_DataLengthCode_8, HV, 6, 100}, 
	{FRAME_Diag_To_INC_ID,                    IfxMultican_DataLengthCode_8, HV, 7, 0}, 
	{FRAME_Diag_To_BMS_ID,                    IfxMultican_DataLengthCode_8, HV, 8, 0}, 
	{FRAME_Diag_Functional_ID,                IfxMultican_DataLengthCode_8, HV, 9, 0}, 
	{FRAME_BSC6LIM_ID,                        IfxMultican_DataLengthCode_6, HV, 10, 100}, 
	{FRAME_BSC6COM_ID,                        IfxMultican_DataLengthCode_3, HV, 11, 100}, 
};
const struct can_message_config_s can_message_rx_config[CANIF_NUMBER_OF_CANRX_IDS] = {
	{FRAME_VCU_EMS_05_ID,                     IfxMultican_DataLengthCode_8, GCAN, 255, 10}, 
	{FRAME_VCU_EMS_04_ID,                     IfxMultican_DataLengthCode_8, GCAN, 254, 10}, 
	{FRAME_VCU_EMS_03_ID,                     IfxMultican_DataLengthCode_8, GCAN, 253, 10}, 
	{FRAME_VCU_EMS_02_ID,                     IfxMultican_DataLengthCode_8, GCAN, 252, 10}, 
	{FRAME_VCU_EMS_01_ID,                     IfxMultican_DataLengthCode_8, GCAN, 251, 10}, 
	{FRAME_Hyb_Sys_INV_05_ID,                 IfxMultican_DataLengthCode_8, HV, 250, 10}, 
	{FRAME_Hyb_Sys_INV_04_ID,                 IfxMultican_DataLengthCode_8, HV, 249, 500}, 
	{FRAME_Hyb_Sys_INV_03_ID,                 IfxMultican_DataLengthCode_8, HV, 248, 100}, 
	{FRAME_Hyb_Sys_INV_02_ID,                 IfxMultican_DataLengthCode_8, HV, 247, 100}, 
	{FRAME_Hyb_Sys_INV_01_ID,                 IfxMultican_DataLengthCode_8, HV, 246, 10}, 
	{FRAME_Hyb_Sys_DC_02_ID,                  IfxMultican_DataLengthCode_8, HV, 245, 100}, 
	{FRAME_Hyb_Sys_DC_01_ID,                  IfxMultican_DataLengthCode_8, HV, 244, 10}, 
	{FRAME_Hyb_Sys_BMS_04_ID,                 IfxMultican_DataLengthCode_8, HV, 243, 500}, 
	{FRAME_Hyb_Sys_BMS_03_ID,                 IfxMultican_DataLengthCode_8, HV, 242, 20}, 
	{FRAME_Hyb_Sys_BMS_02_ID,                 IfxMultican_DataLengthCode_8, HV, 241, 100}, 
	{FRAME_Hyb_Sys_BMS_01_ID,                 IfxMultican_DataLengthCode_8, HV, 240, 10}, 
	{FRAME_Diag_From_INC_ID,                  IfxMultican_DataLengthCode_8, HV, 239, 0}, 
	{FRAME_Diag_From_BMS_ID,                  IfxMultican_DataLengthCode_8, HV, 238, 0}, 
	{FRAME_BSC6VAL2_ID,                       IfxMultican_DataLengthCode_5, HV, 237, 100}, 
	{FRAME_BSC6VAL1_ID,                       IfxMultican_DataLengthCode_8, HV, 236, 100}, 
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
	TXcollect_infoPtr[0] =	 data_collect_EMS_VCU_03 ;
	TXcollect_infoPtr[1] =	 data_collect_EMS_VCU_02 ;
	TXcollect_infoPtr[2] =	 data_collect_EMS_VCU_01 ;
	TXcollect_infoPtr[3] =	 data_collect_NAMI_EMS_04 ;
	TXcollect_infoPtr[4] =	 data_collect_NAMI_EMS_03 ;
	TXcollect_infoPtr[5] =	 data_collect_NAMI_EMS_02 ;
	TXcollect_infoPtr[6] =	 data_collect_NAMI_EMS_01 ;
	TXcollect_infoPtr[7] =	 data_collect_Diag_To_INC ;
	TXcollect_infoPtr[8] =	 data_collect_Diag_To_BMS ;
	TXcollect_infoPtr[9] =	 data_collect_Diag_Functional ;
	TXcollect_infoPtr[10] =	 data_collect_BSC6LIM ;
	TXcollect_infoPtr[11] =	 data_collect_BSC6COM ;

        // IfxMultican_Can_MsgObj canSrcMsgObj; // defined globally
        
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
