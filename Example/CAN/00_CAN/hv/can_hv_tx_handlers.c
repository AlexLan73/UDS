#include "can_hv_tx_handlers_private.h"

void data_collect_NAMI_EMS_04(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		NAMI_EMS_04_frame.EMS_MinCurrentStaty = ((p_7_EMS_MinCurrentStatyToCAN - -511)/1);
		NAMI_EMS_04_frame.EMS_MaxCurrentStaty = ((p_7_EMS_MaxCurrentStatyToCAN - -511)/1);
		NAMI_EMS_04_frame.EMS_MaxTorque = ((p_7_EMS_MaxTorqueToCAN - -511)/1);
		NAMI_EMS_04_frame.EMS_04_AliveCounter = count_NAMI_EMS_04;
		NAMI_EMS_04_frame.EMS_MinTorque = ((p_7_EMS_MinTorqueToCAN - -511)/1);
		NAMI_EMS_04_frame.EMS_04_Checksum = calc_chksum_XOR8((uint8*)&NAMI_EMS_04_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&NAMI_EMS_04_frame);
		tx_mess->data.word[1] = *((((uint32*)&NAMI_EMS_04_frame)+1));

		count_NAMI_EMS_04++;
}
void data_collect_NAMI_EMS_03(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		NAMI_EMS_03_frame.EMS_03_AliveCounter = count_NAMI_EMS_03;
		NAMI_EMS_03_frame.EMS_DesEMotorTorque = round((p_7_EMS_DesEMotorTorqueToCAN - -819.1)/0.1);
		NAMI_EMS_03_frame.EMS_DesInvMode = ((p_7_EMS_DesInvModeToCAN - 0)/1);
		NAMI_EMS_03_frame.EMS_03_Checksum = calc_chksum_XOR8((uint8*)&NAMI_EMS_03_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&NAMI_EMS_03_frame);
		tx_mess->data.word[1] = *((((uint32*)&NAMI_EMS_03_frame)+1));

		count_NAMI_EMS_03++;
}
void data_collect_NAMI_EMS_02(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		NAMI_EMS_02_frame.EMS_DCMinVoltageHV = round((p_7_EMS_DCMinVoltageHVToCAN - 0)/2);
		NAMI_EMS_02_frame.EMS_DCMinVoltageLV = round((p_7_EMS_DCMinVoltageLVToCAN - 0)/0.1);
		NAMI_EMS_02_frame.EMS_DCDesVoltageHV = round((p_7_EMS_DCDesVoltageHVToCAN - 0)/2);
		NAMI_EMS_02_frame.EMS_DCMaxCurrentLV = round((p_7_EMS_DCMaxCurrentLVToCAN - 0)/2);
		NAMI_EMS_02_frame.EMS_DCDesVoltageLV = round((p_7_EMS_DCDesVoltageLVToCAN - 0)/0.1);
		NAMI_EMS_02_frame.EMS_DCMaxCurrentHV = round((p_7_EMS_DCMaxCurrentHVToCAN - 0)/0.2);
		NAMI_EMS_02_frame.EMS_02_AliveCounter = count_NAMI_EMS_02;
		NAMI_EMS_02_frame.EMS_02_Checksum = calc_chksum_XOR8((uint8*)&NAMI_EMS_02_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&NAMI_EMS_02_frame);
		tx_mess->data.word[1] = *((((uint32*)&NAMI_EMS_02_frame)+1));

		count_NAMI_EMS_02++;
}
void data_collect_NAMI_EMS_01(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		NAMI_EMS_01_frame.EMS_DesDCMode = ((p_7_EMS_DesDCModeToCAN - 0)/1);
		NAMI_EMS_01_frame.EMS_DesBMSMode = ((p_7_EMS_DesBMSModeToCAN - 0)/1);
		NAMI_EMS_01_frame.ObdDriveCycleCmplt_ISig_4 = (f_7_ObdDriveCycleCmplt_ISig_4ToCAN - 0)/1;
		NAMI_EMS_01_frame.EMS_MonReqFastDischarge = (f_7_EMS_MonReqFastDischargeToCAN - 0)/1;
		NAMI_EMS_01_frame.EMS_IsolationMeasureReq = (f_7_EMS_IsolationMeasureReqToCAN - 0)/1;
		NAMI_EMS_01_frame.ObdWarmUpCycleCmplt_ISig_4 = (f_7_ObdWarmUpCycleCmplt_ISig_4ToCAN - 0)/1;
		NAMI_EMS_01_frame.EMS_01_AliveCounter = count_NAMI_EMS_01;
		NAMI_EMS_01_frame.EMS_ExtendedLimitsReq = (f_7_EMS_ExtendedLimitsReqToCAN - 0)/1;
		NAMI_EMS_01_frame.EMS_01_Checksum = calc_chksum_XOR8((uint8*)&NAMI_EMS_01_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&NAMI_EMS_01_frame);
		tx_mess->data.word[1] = *((((uint32*)&NAMI_EMS_01_frame)+1));

		count_NAMI_EMS_01++;
}
void data_collect_Diag_To_INC(struct can_message_s* tx_mess)
{

		tx_mess->data.word[0] = *((uint32*)&Diag_To_INC_frame);
		tx_mess->data.word[1] = *((((uint32*)&Diag_To_INC_frame)+1));

}
void data_collect_Diag_To_BMS(struct can_message_s* tx_mess)
{

		tx_mess->data.word[0] = *((uint32*)&Diag_To_BMS_frame);
		tx_mess->data.word[1] = *((((uint32*)&Diag_To_BMS_frame)+1));

}
void data_collect_Diag_Functional(struct can_message_s* tx_mess)
{

		tx_mess->data.word[0] = *((uint32*)&Diag_Functional_frame);
		tx_mess->data.word[1] = *((((uint32*)&Diag_Functional_frame)+1));

}
void data_collect_BSC6LIM(struct can_message_s* tx_mess)
{
	BSC6LIM_frame.BSC6_HVCUR_UPLIM_BOOST = (p_7_BSC6_HVCUR_UPLIM_BOOSTToCAN/0.1);//0;//p_286_BSC6_HVCUR_UPLIM_BOOSTToCAN;
	BSC6LIM_frame.BSC6_HVCUR_UPLIM_BUCK = (p_7_BSC6_HVCUR_UPLIM_BUCKToCAN/0.1);// 0x9E;//p_286_BSC6_HVCUR_UPLIM_BUCKToCAN;
	BSC6LIM_frame.BSC6_HVVOL_LOWLIM = (p_7_BSC6_HVVOL_LOWLIMToCAN-170);//0;//p_286_BSC6_HVVOL_LOWLIMToCAN;
	BSC6LIM_frame.BSC6_LVCUR_UPLIM_BOOST = (p_7_BSC6_LVCUR_UPLIM_BOOSTToCAN);//0; //p_286_BSC6_LVCUR_UPLIM_BOOSTToCAN;
	BSC6LIM_frame.BSC6_LVCUR_UPLIM_BUCK = (p_7_BSC6_LVCUR_UPLIM_BUCKToCAN);//0xA;//p_286_BSC6_LVCUR_UPLIM_BUCKToCAN;
	BSC6LIM_frame.BSC6_LVVOL_LOWLIM = (p_7_BSC6_LVVOL_LOWLIMToCAN/0.1);//0xA0; //p_286_BSC6_LVVOL_LOWLIMToCAN;
asm volatile("");
		tx_mess->data.word[0] = *((uint32*)&BSC6LIM_frame);
		tx_mess->data.word[1] = *((((uint32*)&BSC6LIM_frame)+1));

}
void data_collect_BSC6COM(struct can_message_s* tx_mess)
{
	BSC6COM_frame.BSC6_BOOST = f_7_BSC6_BOOSTToCAN;
	BSC6COM_frame.BSC6_EN_DEBUG_ID = f_7_BSC6_EN_DEBUG_IDToCAN;
	BSC6COM_frame.BSC6_HVVOL_COMM = p_7_BSC6_HVVOL_COMMToCAN-170 ;// 0x96; //p_286_BSC6_HVVOL_COMMToCAN;
	BSC6COM_frame.BSC6_LVVOL_COMM = p_7_BSC6_LVVOL_COMMToCAN/0.1;  //0x89; //p_286_BSC6_LVVOL_COMMToCAN;
	BSC6COM_frame.BSC6_RUNCOMM = f_7_BSC6_RUNCOMMToCAN;//P_0_EMS_DesDCMode;//f_286_BSC6_RUNCOMMToCAN;
asm volatile("");
		tx_mess->data.word[0] = *((uint32*)&BSC6COM_frame);
		tx_mess->data.word[1] = *((((uint32*)&BSC6COM_frame)+1));

}
