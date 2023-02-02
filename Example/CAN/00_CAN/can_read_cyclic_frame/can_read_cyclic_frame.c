#include "can_read_cyclic_frame_private.h"
#include "msg2id.h"
 uint8 message_configuration_number_rx;
int naminumerrl = 0;

void can_read_cyclic_frame(uint32 can_id, uint32 can_cfgnum)
{
//	uint8 message_configuration_number;
	message_configuration_number_rx=255-can_cfgnum;
	//for ( message_configuration_number = 0; message_configuration_number < CANIF_NUMBER_OF_CANRX_IDS; message_configuration_number++ )
	   {
	//	if (can_message_rx_config[message_configuration_number].id  == can_id)
		 {
			enum can_status_e status  = can_read_frame(can_id,message_configuration_number_rx, &rx_msg);

			if (status == new_data) {
				time_out_counter[can_message_rx_config[message_configuration_number_rx].message_object_id] = 0;
				read_data(&rx_msg, can_cfgnum);
			} else {
				time_out_counter[can_message_rx_config[message_configuration_number_rx].message_object_id]+=2;
				check_timeout(can_id, time_out_counter[can_message_rx_config[message_configuration_number_rx].message_object_id]);
			}
	//		break;
		}
	}
}


static void read_data(struct can_message_s* rx_msg , uint32 can_cfgnum)
{
	switch(can_cfgnum) {
	case FRAME_VCU_EMS_05_MO : VCU_EMS_05_handler(rx_msg); break;
	case FRAME_VCU_EMS_04_MO : VCU_EMS_04_handler(rx_msg); break;
	case FRAME_VCU_EMS_03_MO : VCU_EMS_03_handler(rx_msg); break;
	case FRAME_VCU_EMS_02_MO : VCU_EMS_02_handler(rx_msg); break;
	case FRAME_VCU_EMS_01_MO : VCU_EMS_01_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_05_MO : Hyb_Sys_INV_05_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_04_MO : Hyb_Sys_INV_04_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_03_MO : Hyb_Sys_INV_03_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_02_MO : Hyb_Sys_INV_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_INV_01_MO : Hyb_Sys_INV_01_handler(rx_msg); break;
	case FRAME_Hyb_Sys_DC_02_MO : Hyb_Sys_DC_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_DC_01_MO : Hyb_Sys_DC_01_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_04_MO : Hyb_Sys_BMS_04_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_03_MO : Hyb_Sys_BMS_03_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_02_MO : Hyb_Sys_BMS_02_handler(rx_msg); break;
	case FRAME_Hyb_Sys_BMS_01_MO : Hyb_Sys_BMS_01_handler(rx_msg); break;
	case FRAME_Diag_From_INC_MO : Diag_From_INC_handler(rx_msg); break;
	case FRAME_Diag_From_BMS_MO : Diag_From_BMS_handler(rx_msg); break;
	case FRAME_BSC6VAL2_MO : BSC6VAL2_handler(rx_msg); break;
	case FRAME_BSC6VAL1_MO : BSC6VAL1_handler(rx_msg); break;
	default: return;
	}
}
static void set_no_message_flag(uint32 can_id)
{
	switch(can_id) {
	case FRAME_VCU_EMS_05_ID: {((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.NoMsg=1; break;}
	case FRAME_VCU_EMS_04_ID: {((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.NoMsg=1; break;}
	case FRAME_VCU_EMS_03_ID: {((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.NoMsg=1; break;}
	case FRAME_VCU_EMS_02_ID: {((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.NoMsg=1; break;}
	case FRAME_VCU_EMS_01_ID: {((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.NoMsg=1; break;}
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
	default: return;
	}
}
static void check_timeout(uint32 can_id, uint16 counter_value)
{
	switch(can_id) {
	case FRAME_VCU_EMS_05_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_VCU_EMS_04_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_VCU_EMS_03_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_VCU_EMS_02_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_VCU_EMS_01_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_05_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_04_ID : 
		if (counter_value >= 505) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_03_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_02_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_INV_01_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_DC_02_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_DC_01_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_04_ID : 
		if (counter_value >= 505) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_03_ID : 
		if (counter_value >= 25) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_02_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Hyb_Sys_BMS_01_ID : 
		if (counter_value >= 15) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_From_INC_ID : 
		if (counter_value >= 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_Diag_From_BMS_ID : 
		if (counter_value >= 5) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BSC6VAL2_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	case FRAME_BSC6VAL1_ID : 
		if (counter_value >= 105) {
			set_no_message_flag(can_id);
		}		break;

	default: return;
	}
}
