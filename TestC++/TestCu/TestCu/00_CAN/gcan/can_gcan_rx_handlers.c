#include "can_gcan_rx_handlers_private.h"

void VCU_EMS_05_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.NoMsg = 0;
	VCU_EMS_05_frame = *(VCU_EMS_05*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

//	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == VCU_EMS_05_frame.VCU_EMS_05_Checksum) {
		((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.CRCErr = 0;
	p_7_VCU_MaxEmotFastFromCAN = (1*VCU_EMS_05_frame.VCU_MaxEmotFast+-511);
	p_7_VCU_MinEmotFastFromCAN = (1*VCU_EMS_05_frame.VCU_MinEmotFast+-511);
	p_7_VCU_VehicleSpeedFromCAN = (0.01*VCU_EMS_05_frame.VCU_VehicleSpeed+0);
		if (!((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.firstMsg) {
			if(VCU_EMS_05_frame.VCU_EMS_05_AliveCounter != ((count_VCU_EMS_05 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.firstMsg = 0;
		}
		count_VCU_EMS_05 = VCU_EMS_05_frame.VCU_EMS_05_AliveCounter;
//	} else {
//		((rx_Err_flags*)&p_7_VCU_EMS_05_Err)->B.CRCErr = 1;
//	}
}
void VCU_EMS_04_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.NoMsg = 0;
	VCU_EMS_04_frame = *(VCU_EMS_04*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

//	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == VCU_EMS_04_frame.VCU_EMS_04_Checksum) {
		((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.CRCErr = 0;
	f_7_VCU_CooLvLowFromCAN = (1*VCU_EMS_04_frame.VCU_CooLvLow+0);
	p_7_VCU_AmbTempFromCAN = (1*VCU_EMS_04_frame.VCU_AmbTemp+-50);
	p_7_VCU_EMTempFromCAN = (1*VCU_EMS_04_frame.VCU_EMTemp+-50);
	p_7_VCU_IncTempFromCAN = (1*VCU_EMS_04_frame.VCU_IncTemp+-50);
		if (!((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.firstMsg) {
			if(VCU_EMS_04_frame.VCU_EMS_04_AliveCounter != ((count_VCU_EMS_04 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.firstMsg = 0;
		}
		count_VCU_EMS_04 = VCU_EMS_04_frame.VCU_EMS_04_AliveCounter;
//	} else {
//		((rx_Err_flags*)&p_7_VCU_EMS_04_Err)->B.CRCErr = 1;
//	}
}
void VCU_EMS_03_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.NoMsg = 0;
	VCU_EMS_03_frame = *(VCU_EMS_03*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

//	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == VCU_EMS_03_frame.VCU_EMS_03_Checksum) {
		((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.CRCErr = 0;
	p_7_VCU_EMSActualVoltageFromCAN = (0.25*VCU_EMS_03_frame.VCU_EMSActualVoltage+0);
	p_7_VCU_EMSActualTorqueFromCAN = (0.25*VCU_EMS_03_frame.VCU_EMSActualTorque+-511);
	p_7_VCU_EMSActualCurrentFromCAN = (0.25*VCU_EMS_03_frame.VCU_EMSActualCurrent+-511);
		if (!((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.firstMsg) {
			if(VCU_EMS_03_frame.VCU_EMS_03_AliveCounter != ((count_VCU_EMS_03 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.firstMsg = 0;
		}
		count_VCU_EMS_03 = VCU_EMS_03_frame.VCU_EMS_03_AliveCounter;
//	} else {
//		((rx_Err_flags*)&p_7_VCU_EMS_03_Err)->B.CRCErr = 1;
//	}
}
void VCU_EMS_02_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.NoMsg = 0;
	VCU_EMS_02_frame = *(VCU_EMS_02*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

//	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == VCU_EMS_02_frame.VCU_EMS_02_Checksum) {
		((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.CRCErr = 0;
	p_7_VCU_InvTrqMinFromCAN = (1*VCU_EMS_02_frame.VCU_InvTrqMin+-511);
	p_7_VCU_InvTrqMaxFromCAN = (1*VCU_EMS_02_frame.VCU_InvTrqMax+-511);
	p_7_VCU_MaxEmotSlowFromCAN = (1*VCU_EMS_02_frame.VCU_MaxEmotSlow+-511);
	p_7_VCU_MinEmotSlowFromCAN = (1*VCU_EMS_02_frame.VCU_MinEmotSlow+-511);
		if (!((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.firstMsg) {
			if(VCU_EMS_02_frame.VCU_EMS_02_AliveCounter != ((count_VCU_EMS_02 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.firstMsg = 0;
		}
		count_VCU_EMS_02 = VCU_EMS_02_frame.VCU_EMS_02_AliveCounter;
//	} else {
//		((rx_Err_flags*)&p_7_VCU_EMS_02_Err)->B.CRCErr = 1;
//	}
}
void VCU_EMS_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.NoMsg = 0;
	VCU_EMS_01_frame = *(VCU_EMS_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

//	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == VCU_EMS_01_frame.VCU_EMS_01_Checksum) {
		((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.CRCErr = 0;
	p_7_VCU_FuelLvlFromCAN = (0.25*VCU_EMS_01_frame.VCU_FuelLvl+0);
	p_7_VCU_MaxPwrAvlFromCAN = (0.05*VCU_EMS_01_frame.VCU_MaxPwrAvl+0);
	f_7_VCU_VehRdyFromCAN = (1*VCU_EMS_01_frame.VCU_VehRdy+0);
	f_7_VCU_VcuRdyFromCAN = (1*VCU_EMS_01_frame.VCU_VcuRdy+0);
	p_7_VCU_EMSPwrReqFromCAN = (0.05*VCU_EMS_01_frame.VCU_EMSPwrReq+0);
	f_7_VCU_EMSStpCmdFromCAN = (1*VCU_EMS_01_frame.VCU_EMSStpCmd+0);
	f_7_VCU_EMSRunCmdFromCAN = (1*VCU_EMS_01_frame.VCU_EMSRunCmd+0);
		if (!((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.firstMsg) {
			if(VCU_EMS_01_frame.VCU_EMS_01_AliveCounter != ((count_VCU_EMS_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.firstMsg = 0;
		}
		count_VCU_EMS_01 = VCU_EMS_01_frame.VCU_EMS_01_AliveCounter;
//	} else {
//		((rx_Err_flags*)&p_7_VCU_EMS_01_Err)->B.CRCErr = 1;
//	}
}
