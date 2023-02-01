#include "can_write_cyclic_frame_private.h"


void can_write_cyclic_frame(uint32 can_id)
{
	uint8 message_configuration_number;

	//search MO ID in array CanIf_TxPdus[] for message_handler
	for(message_configuration_number = 0; message_configuration_number < CANIF_NUMBER_OF_CANTX_IDS; message_configuration_number++) {
		if (can_message_tx_config[message_configuration_number].id  == can_id) {

			tx_cyclic_msg.data.word[0] = 0;
			tx_cyclic_msg.data.word[1] = 0;
			tx_cyclic_msg.id = can_message_tx_config[message_configuration_number].id;
			tx_cyclic_msg.length = can_message_tx_config[message_configuration_number].dlc;

			collect_info(&tx_cyclic_msg);
			
			can_write_frame(tx_cyclic_msg);
			break;
		}
	}
}


static void collect_info(struct can_message_s* tx_cyclic_msg) 
{
	switch(tx_cyclic_msg->id) {
	case FRAME_NAMI_EMS_04_ID : data_collect_NAMI_EMS_04(tx_cyclic_msg); break;
	case FRAME_NAMI_EMS_03_ID : data_collect_NAMI_EMS_03(tx_cyclic_msg); break;
	case FRAME_NAMI_EMS_02_ID : data_collect_NAMI_EMS_02(tx_cyclic_msg); break;
	case FRAME_NAMI_EMS_01_ID : data_collect_NAMI_EMS_01(tx_cyclic_msg); break;
	case FRAME_Diag_To_INC_ID : data_collect_Diag_To_INC(tx_cyclic_msg); break;
	case FRAME_Diag_To_BMS_ID : data_collect_Diag_To_BMS(tx_cyclic_msg); break;
	case FRAME_Diag_Functional_ID : data_collect_Diag_Functional(tx_cyclic_msg); break;
	case FRAME_BSC6LIM_ID : data_collect_BSC6LIM(tx_cyclic_msg); break;
	case FRAME_BSC6COM_ID : data_collect_BSC6COM(tx_cyclic_msg); break;
	case FRAME_EMS_8_ID : data_collect_EMS_8(tx_cyclic_msg); break;
	case FRAME_EMS_7_ID : data_collect_EMS_7(tx_cyclic_msg); break;
	case FRAME_EMS_4_ID : data_collect_EMS_4(tx_cyclic_msg); break;
	case FRAME_EMS_3_ID : data_collect_EMS_3(tx_cyclic_msg); break;
	case FRAME_EMS_2_ID : data_collect_EMS_2(tx_cyclic_msg); break;
	case FRAME_EMS_1_ID : data_collect_EMS_1(tx_cyclic_msg); break;
	case FRAME_ECU_Indicators_ID : data_collect_ECU_Indicators(tx_cyclic_msg); break;
	case FRAME_ECU_16_ID : data_collect_ECU_16(tx_cyclic_msg); break;
	case FRAME_ECU_14_ID : data_collect_ECU_14(tx_cyclic_msg); break;
	case FRAME_Diag_From_ECU_ID : data_collect_Diag_From_ECU(tx_cyclic_msg); break;
	case FRAME_EMS_HVC_Req_Msg_ID : data_collect_EMS_HVC_Req_Msg(tx_cyclic_msg); break;
	case FRAME_EMS_EEM_02_ID : data_collect_EMS_EEM_02(tx_cyclic_msg); break;
	case FRAME_EMS_EEM_01_ID : data_collect_EMS_EEM_01(tx_cyclic_msg); break;
	case FRAME_ECU_Veh_02_ID : data_collect_ECU_Veh_02(tx_cyclic_msg); break;
	case FRAME_ECU_Veh_ID : data_collect_ECU_Veh(tx_cyclic_msg); break;
	case FRAME_ECU_15_ID : data_collect_ECU_15(tx_cyclic_msg); break;
	default: return;
	}
}

