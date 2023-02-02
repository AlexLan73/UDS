#include "can_read_cyclic_frame_private.h"

#pragma GCC optimize O0

void can_read_cyclic_frame(uint32 can_id)
{
	uint8 message_configuration_number;

	for ( message_configuration_number = 0; message_configuration_number < CANIF_NUMBER_OF_CANRX_IDS; message_configuration_number++ ) {
		if (can_message_rx_config[message_configuration_number].id  == can_id) {
			enum can_status_e status  = can_read_frame(can_id, &rx_msg);

			if (status == new_data) {
				time_out_counter[can_message_rx_config[message_configuration_number].message_object_id] = 0;
				read_data(&rx_msg);
			} else {
				time_out_counter[can_message_rx_config[message_configuration_number].message_object_id]++;
				check_timeout(can_id, time_out_counter[can_message_rx_config[message_configuration_number].message_object_id]);
			}
			break;
		}
	}
}

static void read_data(struct can_message_s* rx_msg)
{
	switch(rx_msg->id) {
	case FRAME_Hyb_Sys_INV_05_ID : Hyb_Sys_INV_05_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_04_ID : Hyb_Sys_INV_04_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_03_ID : Hyb_Sys_INV_03_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_02_ID : Hyb_Sys_INV_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_01_ID : Hyb_Sys_INV_01_handler(rx_msg); break;
	case FRAME_Hyb_Sys_DC_02_ID : Hyb_Sys_DC_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_DC_01_ID : Hyb_Sys_DC_01_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_04_ID : Hyb_Sys_BMS_04_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_03_ID : Hyb_Sys_BMS_03_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_02_ID : Hyb_Sys_BMS_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_01_ID : Hyb_Sys_BMS_01_handler(rx_msg); break;
	case FRAME_Diag_From_INC_ID : Diag_From_INC_handler(rx_msg); break;
	case FRAME_Diag_From_BMS_ID : Diag_From_BMS_handler(rx_msg); break;
	case FRAME_BSC6VAL2_ID : BSC6VAL2_handler(rx_msg); break;
	case FRAME_BSC6VAL1_ID : BSC6VAL1_handler(rx_msg); break;
	case FRAME_TCU_R932_5_ID : TCU_R932_5_handler(rx_msg); break;
	case FRAME_TCU_R932_4_ID : TCU_R932_4_handler(rx_msg); break;
	case FRAME_TCU_R932_3_ID : TCU_R932_3_handler(rx_msg); break;
	case FRAME_TCU_R932_2_ID : TCU_R932_2_handler(rx_msg); break;
	case FRAME_HVC_HV_Status_Msg_ID : HVC_HV_Status_Msg_handler(rx_msg); break;
	case FRAME_Diag_To_ECU_ID : Diag_To_ECU_handler(rx_msg); break;
	case FRAME_CDA_11_ID : CDA_11_handler(rx_msg); break;
	case FRAME_VAU_EMS_Hash_Immo_RESP_ID : VAU_EMS_Hash_Immo_RESP_handler(rx_msg); break;
	case FRAME_TCU_R932_1_ID : TCU_R932_1_handler(rx_msg); break;
	case FRAME_SAS_Standard_ID : SAS_Standard_handler(rx_msg); break;
	case FRAME_EPB_Status_ID : EPB_Status_handler(rx_msg); break;
	case FRAME_Diag_Functional_FromPT_ID : Diag_Functional_FromPT_handler(rx_msg); break;
	case FRAME_DMS_01_ID : DMS_01_handler(rx_msg); break;
	case FRAME_CCU_MSG3_ID : CCU_MSG3_handler(rx_msg); break;
	case FRAME_CCU_HVC_Req_Msg_ID : CCU_HVC_Req_Msg_handler(rx_msg); break;
	case FRAME_BCM_VEH_STATE_ID : BCM_VEH_STATE_handler(rx_msg); break;
	case FRAME_BCM_Powertrain_ID : BCM_Powertrain_handler(rx_msg); break;
	case FRAME_BCM_EEM_ID : BCM_EEM_handler(rx_msg); break;
	case FRAME_ACU_01_ID : ACU_01_handler(rx_msg); break;
	case FRAME_ESP_YRS_03_ID : ESP_YRS_03_handler(rx_msg); break;
	case FRAME_ESP_01_ID : ESP_01_handler(rx_msg); break;
	case FRAME_ESP_03_ID : ESP_03_handler(rx_msg); break;
	case FRAME_ESP_02_ID : ESP_02_handler(rx_msg); break;
	case FRAME_ESP_04_ID : ESP_04_handler(rx_msg); break;
	default: return;
	}
}
static void set_no_message_flag(uint32 can_id)
{
	switch(can_id) {
	case FRAME_Hyb_Sys_INV_05_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_INV_04_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_INV_03_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_INV_02_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_INV_01_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_DC_02_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_DC_01_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_BMS_04_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_BMS_03_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_BMS_02_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.NoMsg=1; break;}
	case FRAME_Hyb_Sys_BMS_01_ID: {((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.NoMsg=1; break;}
	case FRAME_Diag_From_INC_ID: {((rx_Err_flags*)&p_7_Diag_From_INC_Err)->B.NoMsg=1; break;}
	case FRAME_Diag_From_BMS_ID: {((rx_Err_flags*)&p_7_Diag_From_BMS_Err)->B.NoMsg=1; break;}
	case FRAME_BSC6VAL2_ID: {((rx_Err_flags*)&p_7_BSC6VAL2_Err)->B.NoMsg=1; break;}
	case FRAME_BSC6VAL1_ID: {((rx_Err_flags*)&p_7_BSC6VAL1_Err)->B.NoMsg=1; break;}
	case FRAME_TCU_R932_5_ID: {((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.NoMsg=1; break;}
	case FRAME_TCU_R932_4_ID: {((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.NoMsg=1; break;}
	case FRAME_TCU_R932_3_ID: {((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.NoMsg=1; break;}
	case FRAME_TCU_R932_2_ID: {((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.NoMsg=1; break;}
	case FRAME_HVC_HV_Status_Msg_ID: {((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.NoMsg=1; break;}
	case FRAME_Diag_To_ECU_ID: {((rx_Err_flags*)&p_7_Diag_To_ECU_Err)->B.NoMsg=1; break;}
	case FRAME_CDA_11_ID: {((rx_Err_flags*)&p_7_CDA_11_Err)->B.NoMsg=1; break;}
	case FRAME_VAU_EMS_Hash_Immo_RESP_ID: {((rx_Err_flags*)&p_7_VAU_EMS_Hash_Immo_RESP_Err)->B.NoMsg=1; break;}
	case FRAME_TCU_R932_1_ID: {((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.NoMsg=1; break;}
	case FRAME_SAS_Standard_ID: {((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.NoMsg=1; break;}
	case FRAME_EPB_Status_ID: {((rx_Err_flags*)&p_7_EPB_Status_Err)->B.NoMsg=1; break;}
	case FRAME_Diag_Functional_FromPT_ID: {((rx_Err_flags*)&p_7_Diag_Functional_FromPT_Err)->B.NoMsg=1; break;}
	case FRAME_DMS_01_ID: {((rx_Err_flags*)&p_7_DMS_01_Err)->B.NoMsg=1; break;}
	case FRAME_CCU_MSG3_ID: {((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.NoMsg=1; break;}
	case FRAME_CCU_HVC_Req_Msg_ID: {((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.NoMsg=1; break;}
	case FRAME_BCM_VEH_STATE_ID: {((rx_Err_flags*)&p_7_BCM_VEH_STATE_Err)->B.NoMsg=1; break;}
	case FRAME_BCM_Powertrain_ID: {((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.NoMsg=1; break;}
	case FRAME_BCM_EEM_ID: {((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.NoMsg=1; break;}
	case FRAME_ACU_01_ID: {((rx_Err_flags*)&p_7_ACU_01_Err)->B.NoMsg=1; break;}
	case FRAME_ESP_YRS_03_ID: {((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.NoMsg=1; break;}
	case FRAME_ESP_01_ID: {((rx_Err_flags*)&p_7_ESP_01_Err)->B.NoMsg=1; break;}
	case FRAME_ESP_03_ID: {((rx_Err_flags*)&p_7_ESP_03_Err)->B.NoMsg=1; break;}
	case FRAME_ESP_02_ID: {((rx_Err_flags*)&p_7_ESP_02_Err)->B.NoMsg=1; break;}
	case FRAME_ESP_04_ID: {((rx_Err_flags*)&p_7_ESP_04_Err)->B.NoMsg=1; break;}
	default: return;
	}
}
static void check_timeout(uint32 can_id, uint16 counter_value)
{
	switch(can_id) {
	case FRAME_Hyb_Sys_INV_05_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_04_ID : 
		if (counter_value == 505) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_03_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_02_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_01_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_DC_02_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_DC_01_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_04_ID : 
		if (counter_value == 505) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_03_ID : 
		if (counter_value == 25) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_02_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_01_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_From_INC_ID : 
		if (counter_value == 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_From_BMS_ID : 
		if (counter_value == 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BSC6VAL2_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BSC6VAL1_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_TCU_R932_5_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_TCU_R932_4_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_TCU_R932_3_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_TCU_R932_2_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_HVC_HV_Status_Msg_ID : 
		if (counter_value == 55) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_To_ECU_ID : 
		if (counter_value == 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_CDA_11_ID : 
		if (counter_value == 25) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_VAU_EMS_Hash_Immo_RESP_ID : 
		if (counter_value == 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_TCU_R932_1_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_SAS_Standard_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_EPB_Status_ID : 
		if (counter_value == 25) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_Functional_FromPT_ID : 
		if (counter_value == 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_DMS_01_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_CCU_MSG3_ID : 
		if (counter_value == 505) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_CCU_HVC_Req_Msg_ID : 
		if (counter_value == 205) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BCM_VEH_STATE_ID : 
		if (counter_value == 55) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BCM_Powertrain_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BCM_EEM_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ACU_01_ID : 
		if (counter_value == 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ESP_YRS_03_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ESP_01_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ESP_03_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ESP_02_ID : 
		if (counter_value == 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_ESP_04_ID : 
		if (counter_value == 25) {
			set_no_message_flag(can_id);
		}		break;

	default: return;
	}
}
