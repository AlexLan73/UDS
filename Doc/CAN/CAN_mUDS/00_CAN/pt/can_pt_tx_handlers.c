#include "can_pt_tx_handlers_private.h"

void data_collect_EMS_8(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 56;

		EMS_8_frame.tqPwrTrnNoIntv = (p_7_tqPwrTrnNoIntvToCAN - -500)/1;
		EMS_8_frame.ObdDriveCycleCmplt = (f_7_ObdDriveCycleCmpltToCAN - 0)/1;
		EMS_8_frame.ObdWarmUpCycleCmplt = (f_7_ObdWarmUpCycleCmpltToCAN - 0)/1;
		EMS_8_frame.AccPedPosADC2 = (p_7_AccPedPosADC2ToCAN - 0)/0.001;
		EMS_8_frame.EMS_8_RC = count_EMS_8;
		EMS_8_frame.AccPedPosADC1 = (p_7_AccPedPosADC1ToCAN - 0)/0.001;
		EMS_8_frame.EMS_8_CS = calc_chksum_XOR8((uint8*)&EMS_8_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_8_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_8_frame)+1));

		count_EMS_8++;
}
void data_collect_EMS_7(struct can_message_s* tx_mess)
{
		EMS_7_frame.ratThrottle = (p_7_ratThrottleToCAN - 0)/0.5;
		EMS_7_frame.pBoostPressure = (p_7_pBoostPressureToCAN - 0)/0.0125;
		EMS_7_frame.vVehicleEMS = (p_7_vVehicleEMSToCAN - 0)/1;

		tx_mess->data.word[0] = *((uint32*)&EMS_7_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_7_frame)+1));

}
void data_collect_EMS_4(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 48;

		EMS_4_frame.nICEngineSpeed1 = (p_7_nICEngineSpeed1ToCAN - 0)/0.25;
		EMS_4_frame.bICEngineFCO = (f_7_bICEngineFCOToCAN - 0)/1;
		EMS_4_frame.EMS_4_RC = count_EMS_4;
		EMS_4_frame.bPowertrainSignalSpdErr = (f_7_bPowertrainSignalSpdErrToCAN - 0)/1;
		EMS_4_frame.nPwrTrnSpd = (p_7_nPwrTrnSpdToCAN - 0)/0.25;
		EMS_4_frame.EMS_4_CS = calc_chksum_XOR8((uint8*)&EMS_4_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_4_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_4_frame)+1));

		count_EMS_4++;
}
void data_collect_EMS_3(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 48;

		EMS_3_frame.stKickDown = (p_7_stKickDownToCAN - 0)/1;
		EMS_3_frame.ratAccPed = (p_7_ratAccPedToCAN - 0)/0.39;
		EMS_3_frame.bPwrTrnTorqueEstErr = (f_7_bPwrTrnTorqueEstErrToCAN - 0)/1;
		EMS_3_frame.tqDriverTorqueDmd = (p_7_tqDriverTorqueDmdToCAN - -500)/1;
		EMS_3_frame.ratAccPedSts = (f_7_ratAccPedStsToCAN - 0)/1;
		EMS_3_frame.nIdleSpdTargetAct = (p_7_nIdleSpdTargetActToCAN - 0)/1;
		EMS_3_frame.bAccPedSensorFail = (f_7_bAccPedSensorFailToCAN - 0)/1;
		EMS_3_frame.EMS_3_RC = count_EMS_3;
		EMS_3_frame.EMS_3_CS = calc_chksum_XOR8((uint8*)&EMS_3_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_3_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_3_frame)+1));

		count_EMS_3++;
}
void data_collect_EMS_2(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 40;

		EMS_2_frame.tqTransInputTorqueEff = (p_7_tqTransInputTorqueEffToCAN - -500)/1;
		EMS_2_frame.tqEMotorTorque = (p_7_tqEMotorTorqueToCAN - -500)/1;
		EMS_2_frame.EMS_2_RC = count_EMS_2;
		EMS_2_frame.tqICEngineTorque = (p_7_tqICEngineTorqueToCAN - -500)/1;
		EMS_2_frame.EMS_2_CS = calc_chksum_XOR8((uint8*)&EMS_2_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_2_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_2_frame)+1));

		count_EMS_2++;
}
void data_collect_EMS_1(struct can_message_s* tx_mess)
{
		EMS_1_frame.stCrCtlState = (p_7_stCrCtlStateToCAN - 0)/1;
		EMS_1_frame.stLLimStatus = (p_7_stLLimStatusToCAN - 0)/1;
		EMS_1_frame.tCoolant = (p_7_tCoolantToCAN - -48)/0.75;
		EMS_1_frame.pAmbientPres = (p_7_pAmbientPresToCAN - 0)/7.8;
		EMS_1_frame.nPwrTrnSpdLimitCurr = (p_7_nPwrTrnSpdLimitCurrToCAN - 2300)/100;
		EMS_1_frame.vCrCtlVSetpoint = (p_7_vCrCtlVSetpointToCAN - 0)/1;
		EMS_1_frame.bT15on = (f_7_bT15onToCAN - 0)/1;

		tx_mess->data.word[0] = *((uint32*)&EMS_1_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_1_frame)+1));

}
void data_collect_ECU_Indicators(struct can_message_s* tx_mess)
{
		ECU_Indicators_frame.MIL_IND_BLINK = (f_7_MIL_IND_BLINKToCAN - 0)/1;
		ECU_Indicators_frame.EngOilTemp = (p_7_EngOilTempToCAN - -40)/1;
		ECU_Indicators_frame.OilPressureWarning = (f_7_OilPressureWarningToCAN - 0)/1;
		ECU_Indicators_frame.MIL_OnRq = (f_7_MIL_OnRqToCAN - 0)/1;
		ECU_Indicators_frame.OIL_Level = (p_7_OIL_LevelToCAN - -20)/1.15;
		ECU_Indicators_frame.EngOilLvInd = (p_7_EngOilLvIndToCAN - 0)/1;
		ECU_Indicators_frame.LTC_CoolantLvl = (f_7_LTC_CoolantLvlToCAN - 0)/1;

		tx_mess->data.word[0] = *((uint32*)&ECU_Indicators_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_Indicators_frame)+1));

}
void data_collect_ECU_16(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 40;

		ECU_16_frame.MMotMax = (p_7_MMotMaxToCAN - -30000)/1;
		ECU_16_frame.MMotActLm = (p_7_MMotActLmToCAN - -30000)/1;
		ECU_16_frame.ECU_16_RC = count_ECU_16;
		ECU_16_frame.ECU_16_CS = calc_CRC8((uint8*)&ECU_16_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&ECU_16_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_16_frame)+1));

		count_ECU_16++;
}
void data_collect_ECU_14(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 56;

		ECU_14_frame.M_MotClutch = (p_7_M_MotClutchToCAN - -30000)/1;
		ECU_14_frame.M_MotDrag = (p_7_M_MotDragToCAN - -30000)/1;
		ECU_14_frame.ECU_14_RC = count_ECU_14;
		ECU_14_frame.M_MotAct = (p_7_M_MotActToCAN - -30000)/1;
		ECU_14_frame.ECU_14_CS = calc_CRC8((uint8*)&ECU_14_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&ECU_14_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_14_frame)+1));

		count_ECU_14++;
}
void data_collect_Diag_From_ECU(struct can_message_s* tx_mess)
{
		Diag_From_ECU_frame.Diag_From_ECU_Sig = (p_7_Diag_From_ECU_SigToCAN - 0)/1;

		tx_mess->data.word[0] = *((uint32*)&Diag_From_ECU_frame);
		tx_mess->data.word[1] = *((((uint32*)&Diag_From_ECU_frame)+1));

}
void data_collect_EMS_HVC_Req_Msg(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 16;

		EMS_HVC_Req_Msg_frame.EMS_eCompOnPerm_Sig = (f_7_EMS_eCompOnPerm_SigToCAN - 0)/1;
		EMS_HVC_Req_Msg_frame.EMS_eCompHVStateRequest_Sig = (f_7_EMS_eCompHVStateRequest_SigToCAN - 0)/1;
		EMS_HVC_Req_Msg_frame.EMS_eCompHVCurLimit_Sig = (p_7_EMS_eCompHVCurLimit_SigToCAN - 0)/0.1;
		EMS_HVC_Req_Msg_frame.EMS_eCompChillerRequest_Sig = (f_7_EMS_eCompChillerRequest_SigToCAN - 0)/1;
		EMS_HVC_Req_Msg_frame.EMS_HVC_Req_AC = (p_7_EMS_HVC_Req_ACToCAN - 0)/1;
		EMS_HVC_Req_Msg_frame.EMS_HVC_Req_CS = calc_chksum_XOR8((uint8*)&EMS_HVC_Req_Msg_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_HVC_Req_Msg_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_HVC_Req_Msg_frame)+1));

}
void data_collect_EMS_EEM_02(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 48;

		EMS_EEM_02_frame.EMS_ErrPrfLim_DCDC2 = (f_7_EMS_ErrPrfLim_DCDC2ToCAN - 0)/1;
		EMS_EEM_02_frame.EMS_stMode_DCDC2 = (f_7_EMS_stMode_DCDC2ToCAN - 0)/1;
		EMS_EEM_02_frame.EMS_Err_DCDC2 = (f_7_EMS_Err_DCDC2ToCAN - 0)/1;
		EMS_EEM_02_frame.EMS_ActCurrLV_DCDC2 = (p_7_EMS_ActCurrLV_DCDC2ToCAN - -3276.7)/0.1;
		EMS_EEM_02_frame.EMS_ActVoltLV_DCDC2 = (p_7_EMS_ActVoltLV_DCDC2ToCAN - 0)/0.1;
		EMS_EEM_02_frame.EMS_UtilRate_DCDC2 = (p_7_EMS_UtilRate_DCDC2ToCAN - 0)/0.1;
		EMS_EEM_02_frame.EMS_EEM_02_RC = count_EMS_EEM_02;
		EMS_EEM_02_frame.EMS_EEM_02_CS = calc_CRC8((uint8*)&EMS_EEM_02_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_EEM_02_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_EEM_02_frame)+1));

		count_EMS_EEM_02++;
}
void data_collect_EMS_EEM_01(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 48;

		EMS_EEM_01_frame.EMS_Err_DCDC1 = (f_7_EMS_Err_DCDC1ToCAN - 0)/1;
		EMS_EEM_01_frame.EMS_ActCurrLV_DCDC1 = (p_7_EMS_ActCurrLV_DCDC1ToCAN - -3276.7)/0.1;
		EMS_EEM_01_frame.EMS_stMode_DCDC1 = (f_7_EMS_stMode_DCDC1ToCAN - 0)/1;
		EMS_EEM_01_frame.EMS_ActVoltLV_DCDC1 = (p_7_EMS_ActVoltLV_DCDC1ToCAN - 0)/0.1;
		EMS_EEM_01_frame.EMS_UtilRate_DCDC1 = (p_7_EMS_UtilRate_DCDC1ToCAN - 0)/0.1;
		EMS_EEM_01_frame.EMS_EEM_01_RC = count_EMS_EEM_01;
		EMS_EEM_01_frame.EMS_ErrPrfLim_DCDC1 = (f_7_EMS_ErrPrfLim_DCDC1ToCAN - 0)/1;
		EMS_EEM_01_frame.EMS_EEM_01_CS = calc_CRC8((uint8*)&EMS_EEM_01_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&EMS_EEM_01_frame);
		tx_mess->data.word[1] = *((((uint32*)&EMS_EEM_01_frame)+1));

		count_EMS_EEM_01++;
}
void data_collect_ECU_Veh_02(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 16;

		ECU_Veh_02_frame.CoEng_st = (p_7_CoEng_stToCAN - 0)/1;
		ECU_Veh_02_frame.ECU_Veh_02_RC = count_ECU_Veh_02;
		ECU_Veh_02_frame.BMS_ActualTemperature = (p_7_BMS_ActualTemperatureToCAN - -40)/0.5;
		ECU_Veh_02_frame.ECU_Veh_02_CS = calc_CRC8((uint8*)&ECU_Veh_02_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&ECU_Veh_02_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_Veh_02_frame)+1));

		count_ECU_Veh_02++;
}
void data_collect_ECU_Veh(struct can_message_s* tx_mess)
{
		ECU_Veh_frame.EngCoolTemp = (p_7_EngCoolTempToCAN - -40)/1;
		ECU_Veh_frame.InstFuelConsumption = (p_7_InstFuelConsumptionToCAN - 0)/1;
		ECU_Veh_frame.HvSystemFailure = (p_7_HvSystemFailureToCAN - 0)/1;
		ECU_Veh_frame.EngTrqStatic = (p_7_EngTrqStaticToCAN - -500)/0.25;
		ECU_Veh_frame.nICEngineSpeed3 = (p_7_nICEngineSpeed3ToCAN - 0)/0.25;
		ECU_Veh_frame.BARO_ENG = (p_7_BARO_ENGToCAN - 0)/1;
		ECU_Veh_frame.CoolLiquidLowWarning = (f_7_CoolLiquidLowWarningToCAN - 0)/1;
		ECU_Veh_frame.AccelPdlPosn_OBD = (p_7_AccelPdlPosn_OBDToCAN - 0)/0.3922;

		tx_mess->data.word[0] = *((uint32*)&ECU_Veh_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_Veh_frame)+1));

}
