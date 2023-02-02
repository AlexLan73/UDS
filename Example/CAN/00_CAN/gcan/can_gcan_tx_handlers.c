#include "can_gcan_tx_handlers_private.h"

void data_collect_EMS_VCU_03(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		EMS_VCU_03_frame.EMS_PowerLimit = round((p_7_EMS_PowerLimitToCAN - 0)/0.05);
		EMS_VCU_03_frame.EMS_MaxCurrentStatyFast = ((p_7_EMS_MaxCurrentStatyFastToCAN - -511)/1);
		EMS_VCU_03_frame.EMS_MaxCurrentStatySlow = ((p_7_EMS_MaxCurrentStatySlowToCAN - -511)/1);
		EMS_VCU_03_frame.EMS_MinCurrentStatyFast = ((p_7_EMS_MinCurrentStatyFastToCAN - -511)/1);
		EMS_VCU_03_frame.EMS_MinCurrentStatySlow = ((p_7_EMS_MinCurrentStatySlowToCAN - -511)/1);
		EMS_VCU_03_frame.EMS_VCU_03_AliveCounter = count_EMS_VCU_03;
		EMS_VCU_03_frame.EMS_VCU_03_Checksum = calc_CRC8((uint8*)&EMS_VCU_03_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_VCU_03_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_VCU_03_frame)+1));

		count_EMS_VCU_03++;
}
void data_collect_EMS_VCU_02(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		EMS_VCU_02_frame.EMS_EMTrqMin = ((p_7_EMS_EMTrqMinToCAN - -511)/1);
		EMS_VCU_02_frame.EMS_EmTrqMax = ((p_7_EMS_EmTrqMaxToCAN - -511)/1);
		EMS_VCU_02_frame.EMS_OilPressureWarning = (f_7_EMS_OilPressureWarningToCAN - 0)/1;
		EMS_VCU_02_frame.EMS_InstFuelCons = ((p_7_EMS_InstFuelConsToCAN - 0)/1);
		EMS_VCU_02_frame.EMS_VCU_02_AliveCounter = count_EMS_VCU_02;
		EMS_VCU_02_frame.EMS_VCU_02_Checksum = calc_CRC8((uint8*)&EMS_VCU_02_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_VCU_02_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_VCU_02_frame)+1));

		count_EMS_VCU_02++;
}
void data_collect_EMS_VCU_01(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 0;

		EMS_VCU_01_frame.EMS_TrqReq = round((p_7_EMS_TrqReqToCAN - -511)/0.25);
		EMS_VCU_01_frame.EMS_Tcool = ((p_7_EMS_TcoolToCAN - 0)/1);
		EMS_VCU_01_frame.EMS_FanReq = ((p_7_EMS_FanReqToCAN - 0)/1);
		EMS_VCU_01_frame.EMS_ActualPwr = round((p_7_EMS_ActualPwrToCAN - 0)/0.05);
		EMS_VCU_01_frame.EMS_FaultState = ((p_7_EMS_FaultStateToCAN - 0)/1);
		EMS_VCU_01_frame.EMS_EmgcyStop = (f_7_EMS_EmgcyStopToCAN - 0)/1;
		EMS_VCU_01_frame.EMS_CoengSt = ((p_7_EMS_CoengStToCAN - 0)/1);
		EMS_VCU_01_frame.EMS_ReadyState = (f_7_EMS_ReadyStateToCAN - 0)/1;
		EMS_VCU_01_frame.EMS_VCU_01_AliveCounter = count_EMS_VCU_01;
		EMS_VCU_01_frame.EMS_VCU_01_Checksum = calc_CRC8((uint8*)&EMS_VCU_01_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_VCU_01_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_VCU_01_frame)+1));

		count_EMS_VCU_01++;
}
