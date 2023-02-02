#include "can_hv_rx_handlers_private.h"

void Hyb_Sys_INV_05_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.NoMsg = 0;
	Hyb_Sys_INV_05_frame = *(Hyb_Sys_INV_05*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_INV_05_frame.INV_05_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.CRCErr = 0;
	p_7_INV_MinEMotorTorqueFastFromCAN = 1*Hyb_Sys_INV_05_frame.INV_MinEMotorTorqueFast+-511;
	p_7_INV_MaxEMotorTorqueFastFromCAN = 1*Hyb_Sys_INV_05_frame.INV_MaxEMotorTorqueFast+-511;
	f_7_INV_SleepIndFromCAN = 1*Hyb_Sys_INV_05_frame.INV_SleepInd+0;
	f_7_INV_ErrEmergencyFromCAN = 1*Hyb_Sys_INV_05_frame.INV_ErrEmergency+0;
	p_7_INV_MaxEMotorTorqueFromCAN = 1*Hyb_Sys_INV_05_frame.INV_MaxEMotorTorque+-511;
	f_7_INV_ErrActvShoCircFromCAN = 1*Hyb_Sys_INV_05_frame.INV_ErrActvShoCirc+0;
	f_7_INV_HVReadyFromCAN = 1*Hyb_Sys_INV_05_frame.INV_HVReady+0;
	f_7_INV_ErrEMotorFreeWheelingFromCAN = 1*Hyb_Sys_INV_05_frame.INV_ErrEMotorFreeWheeling+0;
	f_7_INV_TrqLimitsExtendedFromCAN = 1*Hyb_Sys_INV_05_frame.INV_TrqLimitsExtended+0;
	f_7_INV_ErrPerformanceFromCAN = 1*Hyb_Sys_INV_05_frame.INV_ErrPerformance+0;
	p_7_INV_ActualModeFromCAN = 1*Hyb_Sys_INV_05_frame.INV_ActualMode+0;
	f_7_INV_InitFinishedFromCAN = 1*Hyb_Sys_INV_05_frame.INV_InitFinished+0;
	p_7_INV_MinEMotorTorqueFromCAN = 1*Hyb_Sys_INV_05_frame.INV_MinEMotorTorque+-511;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.firstMsg) {
			if(Hyb_Sys_INV_05_frame.INV_05_AliveCounter != ((count_Hyb_Sys_INV_05 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_INV_05 = Hyb_Sys_INV_05_frame.INV_05_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_05_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_INV_04_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.NoMsg = 0;
	Hyb_Sys_INV_04_frame = *(Hyb_Sys_INV_04*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_INV_04_frame.INV_04_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.CRCErr = 0;
	p_7_INV_TemperatureFromCAN = 1*Hyb_Sys_INV_04_frame.INV_Temperature+-40;
	f_7_INV_WarnLampActiveFromCAN = 1*Hyb_Sys_INV_04_frame.INV_WarnLampActive+0;
	f_7_INV_ErrorLampActiveFromCAN = 1*Hyb_Sys_INV_04_frame.INV_ErrorLampActive+0;
	p_7_INV_RotorTemperatureFromCAN = 1*Hyb_Sys_INV_04_frame.INV_RotorTemperature+-40;
	p_7_INV_EMotorTemperatureFromCAN = 1*Hyb_Sys_INV_04_frame.INV_EMotorTemperature+-40;
	f_7_INV_MILReqFromCAN = 1*Hyb_Sys_INV_04_frame.INV_MILReq+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.firstMsg) {
			if(Hyb_Sys_INV_04_frame.INV_04_AliveCounter != ((count_Hyb_Sys_INV_04 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_INV_04 = Hyb_Sys_INV_04_frame.INV_04_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_04_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_INV_03_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.NoMsg = 0;
	Hyb_Sys_INV_03_frame = *(Hyb_Sys_INV_03*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_INV_03_frame.INV_03_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.CRCErr = 0;
	p_7_INV_MaxEMotorTorqueSlowFromCAN = 1*Hyb_Sys_INV_03_frame.INV_MaxEMotorTorqueSlow+-511;
	p_7_INV_MinTurnPointSpeedFromCAN = 50*Hyb_Sys_INV_03_frame.INV_MinTurnPointSpeed+0;
	p_7_INV_HVAuxTorqueFromCAN = 1*Hyb_Sys_INV_03_frame.INV_HVAuxTorque+-511;
	p_7_INV_MinEMotorTorqueSlowFromCAN = 1*Hyb_Sys_INV_03_frame.INV_MinEMotorTorqueSlow+-511;
	p_7_INV_MaxTurnPointSpeedFromCAN = 50*Hyb_Sys_INV_03_frame.INV_MaxTurnPointSpeed+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.firstMsg) {
			if(Hyb_Sys_INV_03_frame.INV_03_AliveCounter != ((count_Hyb_Sys_INV_03 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_INV_03 = Hyb_Sys_INV_03_frame.INV_03_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_03_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_INV_02_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.NoMsg = 0;
	Hyb_Sys_INV_02_frame = *(Hyb_Sys_INV_02*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_INV_02_frame.INV_02_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.CRCErr = 0;
	p_7_INV_PowerLossFromCAN = 20*Hyb_Sys_INV_02_frame.INV_PowerLoss+0;
	p_7_INV_ActualVoltageFromCAN = 0.25*Hyb_Sys_INV_02_frame.INV_ActualVoltage+0;
	p_7_INV_ActualCurrentFromCAN = 0.25*Hyb_Sys_INV_02_frame.INV_ActualCurrent+-511;
	f_7_INV_ErrTempDeratingFromCAN = 1*Hyb_Sys_INV_02_frame.INV_ErrTempDerating+0;
	f_7_INV_DiagReqFromCAN = 1*Hyb_Sys_INV_02_frame.INV_DiagReq+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.firstMsg) {
			if(Hyb_Sys_INV_02_frame.INV_02_AliveCounter != ((count_Hyb_Sys_INV_02 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_INV_02 = Hyb_Sys_INV_02_frame.INV_02_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_02_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_INV_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.NoMsg = 0;
	Hyb_Sys_INV_01_frame = *(Hyb_Sys_INV_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_INV_01_frame.INV_01_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.CRCErr = 0;
	p_7_INV_ActualEngineSpeedFromCAN = 0.5*Hyb_Sys_INV_01_frame.INV_ActualEngineSpeed+-10000;
	p_7_INV_ActualTorqueFromCAN = 0.25*Hyb_Sys_INV_01_frame.INV_ActualTorque+-511;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.firstMsg) {
			if(Hyb_Sys_INV_01_frame.INV_01_AliveCounter != ((count_Hyb_Sys_INV_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_INV_01 = Hyb_Sys_INV_01_frame.INV_01_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_INV_01_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_DC_02_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.NoMsg = 0;
	Hyb_Sys_DC_02_frame = *(Hyb_Sys_DC_02*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_DC_02_frame.DC_02_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.CRCErr = 0;
	p_7_DC_ActualTemperatureFromCAN = 1*Hyb_Sys_DC_02_frame.DC_ActualTemperature+-40;
	p_7_DC_ActCurrentLVFromCAN = 1*Hyb_Sys_DC_02_frame.DC_ActCurrentLV+-511;
	p_7_DC_ActVoltageLVFromCAN = 0.1*Hyb_Sys_DC_02_frame.DC_ActVoltageLV+0;
	p_7_DC_RelLoadFromCAN = 0.4*Hyb_Sys_DC_02_frame.DC_RelLoad+0;
	f_7_DC_ErrTempDeratingFromCAN = 1*Hyb_Sys_DC_02_frame.DC_ErrTempDerating+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.firstMsg) {
			if(Hyb_Sys_DC_02_frame.DC_02_AliveCounter != ((count_Hyb_Sys_DC_02 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_DC_02 = Hyb_Sys_DC_02_frame.DC_02_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_DC_02_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_DC_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.NoMsg = 0;
	Hyb_Sys_DC_01_frame = *(Hyb_Sys_DC_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_DC_01_frame.DC_01_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.CRCErr = 0;
	p_7_DC_ActVoltageHVFromCAN = 0.25*Hyb_Sys_DC_01_frame.DC_ActVoltageHV+0;
	f_7_DC_ErrPerformanceFromCAN = 1*Hyb_Sys_DC_01_frame.DC_ErrPerformance+0;
	p_7_DC_ActCurrentHVFromCAN = 0.1*Hyb_Sys_DC_01_frame.DC_ActCurrentHV+-51.1;
	f_7_DC_ErrVoltageFromCAN = 1*Hyb_Sys_DC_01_frame.DC_ErrVoltage+0;
	f_7_DC_SleepIndFromCAN = 1*Hyb_Sys_DC_01_frame.DC_SleepInd+0;
	f_7_DC_ErrInternalFromCAN = 1*Hyb_Sys_DC_01_frame.DC_ErrInternal+0;
	p_7_DC_ActualModeFromCAN = 1*Hyb_Sys_DC_01_frame.DC_ActualMode+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.firstMsg) {
			if(Hyb_Sys_DC_01_frame.DC_01_AliveCounter != ((count_Hyb_Sys_DC_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_DC_01 = Hyb_Sys_DC_01_frame.DC_01_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_DC_01_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_BMS_04_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.NoMsg = 0;
	Hyb_Sys_BMS_04_frame = *(Hyb_Sys_BMS_04*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_BMS_04_frame.BMS_04_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.CRCErr = 0;
	p_7_BMS_MaxVoltageFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_MaxVoltage+0;
	p_7_BMS_BatteryHeaterStateFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_BatteryHeaterState+0;
	f_7_BMS_MILReqFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_MILReq+0;
	f_7_BMS_ErrorLampActiveFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_ErrorLampActive+0;
	p_7_BMS_ActualTemperature_ISig_4FromCAN = 0.5*Hyb_Sys_BMS_04_frame.BMS_ActualTemperature_ISig_4+-40;
	f_7_BMS_WarnLampActiveFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_WarnLampActive+0;
	p_7_BMS_MinVoltageFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_MinVoltage+0;
	f_7_BMS_BalancingReqFromCAN = 1*Hyb_Sys_BMS_04_frame.BMS_BalancingReq+0;
	p_7_BMS_Temperature_InletFromCAN = 0.5*Hyb_Sys_BMS_04_frame.BMS_Temperature_Inlet+-40;
	p_7_BMS_SOHFromCAN = 0.4*Hyb_Sys_BMS_04_frame.BMS_SOH+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.firstMsg) {
			if(Hyb_Sys_BMS_04_frame.BMS_04_AliveCounter != ((count_Hyb_Sys_BMS_04 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_BMS_04 = Hyb_Sys_BMS_04_frame.BMS_04_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_04_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_BMS_03_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.NoMsg = 0;
	Hyb_Sys_BMS_03_frame = *(Hyb_Sys_BMS_03*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_BMS_03_frame.BMS_03_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.CRCErr = 0;
	f_7_BMS_ExtCurLimitsActFromCAN = 1*Hyb_Sys_BMS_03_frame.BMS_ExtCurLimitsAct+0;
	p_7_BMS_MaxDisCharCurrentFastFromCAN = 1*Hyb_Sys_BMS_03_frame.BMS_MaxDisCharCurrentFast+0;
	p_7_BMS_MaxChargeVoltFastFromCAN = 1*Hyb_Sys_BMS_03_frame.BMS_MaxChargeVoltFast+0;
	p_7_BMS_MinDisChargeVoltFastFromCAN = 1*Hyb_Sys_BMS_03_frame.BMS_MinDisChargeVoltFast+0;
	p_7_BMS_MaxCharCurrentFastFromCAN = 1*Hyb_Sys_BMS_03_frame.BMS_MaxCharCurrentFast+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.firstMsg) {
			if(Hyb_Sys_BMS_03_frame.BMS_03_AliveCounter != ((count_Hyb_Sys_BMS_03 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_BMS_03 = Hyb_Sys_BMS_03_frame.BMS_03_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_03_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_BMS_02_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.NoMsg = 0;
	Hyb_Sys_BMS_02_frame = *(Hyb_Sys_BMS_02*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_BMS_02_frame.BMS_02_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.CRCErr = 0;
	p_7_BMS_SOCFromCAN = 0.4*Hyb_Sys_BMS_02_frame.BMS_SOC+0;
	p_7_BMS_MaxChargeVoltSlowFromCAN = 1*Hyb_Sys_BMS_02_frame.BMS_MaxChargeVoltSlow+0;
	p_7_BMS_MinDisChargeVoltSlowFromCAN = 1*Hyb_Sys_BMS_02_frame.BMS_MinDisChargeVoltSlow+0;
	p_7_BMS_MaxCharCurrentSlowFromCAN = 1*Hyb_Sys_BMS_02_frame.BMS_MaxCharCurrentSlow+0;
	p_7_BMS_MaxDisCharCurrentSlowFromCAN = 1*Hyb_Sys_BMS_02_frame.BMS_MaxDisCharCurrentSlow+0;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.firstMsg) {
			if(Hyb_Sys_BMS_02_frame.BMS_02_AliveCounter != ((count_Hyb_Sys_BMS_02 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_BMS_02 = Hyb_Sys_BMS_02_frame.BMS_02_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_02_Err)->B.CRCErr = 1;
	}
}
void Hyb_Sys_BMS_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.NoMsg = 0;
	Hyb_Sys_BMS_01_frame = *(Hyb_Sys_BMS_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 0;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == Hyb_Sys_BMS_01_frame.BMS_01_Checksum) {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.CRCErr = 0;
	f_7_BMS_ErrMCOpenFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrMCOpen+0;
	f_7_BMS_ErrHVBatLowPrioFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrHVBatLowPrio+0;
	f_7_BMS_ErrHVBatHighPrioFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrHVBatHighPrio+0;
	p_7_BMS_ActualVoltageFromCAN = 0.25*Hyb_Sys_BMS_01_frame.BMS_ActualVoltage+0;
	f_7_BMS_ErrPerformanceFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrPerformance+0;
	f_7_BMS_ErrMCWeldedFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrMCWelded+0;
	f_7_BMS_ErrEmergencyFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrEmergency+0;
	f_7_BMS_ErrIsolationFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrIsolation+0;
	f_7_BMS_IsolationCheckActiveFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_IsolationCheckActive+0;
	f_7_BMS_InitFinishedFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_InitFinished+0;
	p_7_BMS_ActualModeFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ActualMode+0;
	f_7_BMS_ErrPilotLineOpenFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrPilotLineOpen+0;
	f_7_BMS_SleepIndFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_SleepInd+0;
	f_7_BMS_bChrgrPlgInFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_bChrgrPlgIn+0;
	f_7_BMS_ErrColdStartFromCAN = 1*Hyb_Sys_BMS_01_frame.BMS_ErrColdStart+0;
	p_7_BMS_ActualCurrentFromCAN = 0.25*Hyb_Sys_BMS_01_frame.BMS_ActualCurrent+-511;
		if (!((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.firstMsg) {
			if(Hyb_Sys_BMS_01_frame.BMS_01_AliveCounter != ((count_Hyb_Sys_BMS_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.firstMsg = 0;
		}
		count_Hyb_Sys_BMS_01 = Hyb_Sys_BMS_01_frame.BMS_01_AliveCounter;
	} else {
		((rx_Err_flags*)&p_7_Hyb_Sys_BMS_01_Err)->B.CRCErr = 1;
	}
}
void Diag_From_INC_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Diag_From_INC_Err)->B.NoMsg = 0;
	Diag_From_INC_frame = *(Diag_From_INC*)rx_msg->data.byte;
		if (!((rx_Err_flags*)&p_7_Diag_From_INC_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_Diag_From_INC_Err)->B.firstMsg = 0;
		}
}
void Diag_From_BMS_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Diag_From_BMS_Err)->B.NoMsg = 0;
	Diag_From_BMS_frame = *(Diag_From_BMS*)rx_msg->data.byte;
		if (!((rx_Err_flags*)&p_7_Diag_From_BMS_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_Diag_From_BMS_Err)->B.firstMsg = 0;
		}
}
void BSC6VAL2_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_BSC6VAL2_Err)->B.NoMsg = 0;
//	BSC6VAL2_frame = *(BSC6VAL2*)rx_msg->data.byte;
	if (!((rx_Err_flags*)&p_7_BSC6VAL2_Err)->B.firstMsg) {
	} else {
		((rx_Err_flags*)&p_7_BSC6VAL2_Err)->B.firstMsg = 0;
	}

		p_7_BSC6_LVCUR_AVLFromCAN = rx_msg->data.byte[0];
		p_7_BSC6_TEMP_MAXFromCAN =  rx_msg->data.byte[1];

		f_7_BSC6_CRE_HV_FUSEFromCAN =		    rx_msg->data.byte[2] & 0x1;
		f_7_BSC6_CRE_LV_FUSEFromCAN = 		  ( rx_msg->data.byte[2] >> 1 ) & 0x1;
		f_7_BSC6_CRE_CUR_LSFromCAN =		  ( rx_msg->data.byte[2] >> 2 ) & 0x1;
		f_7_BSC6_CRE_CUR_DEVFromCAN = 		  ( rx_msg->data.byte[2] >> 3 ) & 0x1;
		f_7_BSC6_CRE_INTERLOCKFromCAN =  	  ( rx_msg->data.byte[2] >> 4 ) & 0x1;
		f_7_BSC6_CRE_INT_SUPPLY_12VFromCAN =  ( rx_msg->data.byte[2] >> 5 ) & 0x1;
		f_7_BSC6_CRE_INT_SUPPLY_6VFromCAN =   ( rx_msg->data.byte[2] >> 6 ) & 0x1;
		f_7_BSC6_CRE_VOL_DEVFromCAN = 		  ( rx_msg->data.byte[2] >> 7 ) & 0x1;

		f_7_BSC6_E_LV_UNDERVOLFromCAN =   rx_msg->data.byte[3] & 0x1;
		f_7_BSC6_E_LV_OVERVOLFromCAN =  ( rx_msg->data.byte[3] >> 1 ) & 0x1;
		f_7_BSC6_E_HV_UNDERVOLFromCAN = ( rx_msg->data.byte[3] >> 2 ) & 0x1;
		f_7_BSC6_E_HV_OVERVOLFromCAN =  ( rx_msg->data.byte[3] >> 3 ) & 0x1;
		f_7_BSC6_E_INT_SUPPLYFromCAN =  ( rx_msg->data.byte[3] >> 4 ) & 0x1;
		f_7_BSC6_E_TEMPFromCAN =  	( rx_msg->data.byte[3] >> 5 ) & 0x1;
		f_7_BSC6_E_TRAFO_BOOSTFromCAN = ( rx_msg->data.byte[3] >> 6 ) & 0x1;
		f_7_BSC6_E_OVERTEMPFromCAN =    ( rx_msg->data.byte[3] >> 7 ) & 0x1;

		f_7_BSC6_E_CAN_VALUEFromCAN =       rx_msg->data.byte[4] & 0x1;
		f_7_BSC6_E_CAN_MSG_COMMFromCAN =  ( rx_msg->data.byte[4] >> 1 )& 0x1;
		f_7_BSC6_E_CAN_MSG_LIMFromCAN =   ( rx_msg->data.byte[4] >> 2 )& 0x1;
		f_7_BSC6_CRE_INITFromCAN =  	  ( rx_msg->data.byte[4] >> 6 )& 0x1;
		f_7_BSC6_W_TEMPFromCAN =  		  ( rx_msg->data.byte[4] >> 7 )& 0x1;
}
void BSC6VAL1_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_BSC6VAL1_Err)->B.NoMsg = 0;
//	BSC6VAL1_frame = *(BSC6VAL1*)rx_msg->data.byte;
		if (!((rx_Err_flags*)&p_7_BSC6VAL1_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_BSC6VAL1_Err)->B.firstMsg = 0;
		}

		p_7_BSC6_HVVOL_ACTFromCAN = (((uint16)rx_msg->data.byte[0] )<<8) + rx_msg->data.byte[1];
		p_7_BSC6_LVVOLT_ACTFromCAN = rx_msg->data.byte[2];
		p_7_BSC6_HVCUR_ACTFromCAN = (((uint16)rx_msg->data.byte[3] )<<8) + rx_msg->data.byte[4];
		p_7_BSC6_LVCUR_ACTFromCAN = (((uint16)rx_msg->data.byte[5] )<<8) + rx_msg->data.byte[6];
		f_7_BSC6_STATEFromCAN = 	  rx_msg->data.byte[7] & 0x1;
		f_7_BSC6_READYFromCAN = 	( rx_msg->data.byte[7] >> 1) & 0x1;
//		f_7_BSC6_AUTOMATICFromCAN = ( rx_msg->data.byte[7] >> 2) & 0x1;
		p_7_BSC6_MODEFromCAN = 		( rx_msg->data.byte[7] >> 4) & 0xF;

		p_7_BSC6_HVVOL_ACTFromCAN *=0.1 ;
		p_7_BSC6_LVVOLT_ACTFromCAN *=0.1 ;
		p_7_BSC6_HVCUR_ACTFromCAN =p_7_BSC6_HVCUR_ACTFromCAN*0.1-25 ;
		p_7_BSC6_LVCUR_ACTFromCAN =p_7_BSC6_LVCUR_ACTFromCAN - 280 ;
}
