#include "can_pt_rx_handlers_private.h"

void TCU_R932_5_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.NoMsg = 0;
	TCU_R932_5_frame = *(TCU_R932_5*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 16;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == TCU_R932_5_frame.TCU_R932_5_CS) {
		((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.CRCErr = 0;
	p_7_nIdleSpeedReqFromCAN = 10*TCU_R932_5_frame.nIdleSpeedReq+0;
	f_7_bIdleSpeedReqFromCAN = 1*TCU_R932_5_frame.bIdleSpeedReq+0;
		if (!((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.firstMsg) {
			if(TCU_R932_5_frame.TCU_R932_5_RC != ((count_TCU_R932_5 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.firstMsg = 0;
		}
		count_TCU_R932_5 = TCU_R932_5_frame.TCU_R932_5_RC;
	} else {
		((rx_Err_flags*)&p_7_TCU_R932_5_Err)->B.CRCErr = 1;
	}
}
void TCU_R932_4_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.NoMsg = 0;
	TCU_R932_4_frame = *(TCU_R932_4*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 40;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == TCU_R932_4_frame.TCU_R932_4_CS) {
		((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.CRCErr = 0;
	p_7_tqGbxTorqueLossFromCAN = 1*TCU_R932_4_frame.tqGbxTorqueLoss+0;
	p_7_nGearBoxShaftOutSpeedFromCAN = 0.5*TCU_R932_4_frame.nGearBoxShaftOutSpeed+-3000;
	p_7_tiEngineSpeedCtrlSyncFromCAN = 1*TCU_R932_4_frame.tiEngineSpeedCtrlSync+0;
	p_7_tGbxOilFromCAN = 1*TCU_R932_4_frame.tGbxOil+-40;
		if (!((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.firstMsg) {
			if(TCU_R932_4_frame.TCU_R932_4_RC != ((count_TCU_R932_4 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.firstMsg = 0;
		}
		count_TCU_R932_4 = TCU_R932_4_frame.TCU_R932_4_RC;
	} else {
		((rx_Err_flags*)&p_7_TCU_R932_4_Err)->B.CRCErr = 1;
	}
}
void TCU_R932_3_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.NoMsg = 0;
	TCU_R932_3_frame = *(TCU_R932_3*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 48;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == TCU_R932_3_frame.TCU_R932_3_CS) {
		((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.CRCErr = 0;
	p_7_vGbxMaxVehSpdLimitFromCAN = 1*TCU_R932_3_frame.vGbxMaxVehSpdLimit+0;
	p_7_dTrqPwrTrnGradLimitFromCAN = 10*TCU_R932_3_frame.dTrqPwrTrnGradLimit+0;
	p_7_nEngineSpeedLimitFromCAN = 10*TCU_R932_3_frame.nEngineSpeedLimit+0;
	p_7_tqTransmInputMaxFromCAN = 1*TCU_R932_3_frame.tqTransmInputMax+-500;
	p_7_stFrcTrqAdapEMSFromCAN = 1*TCU_R932_3_frame.stFrcTrqAdapEMS+0;
		if (!((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.firstMsg) {
			if(TCU_R932_3_frame.TCU_R932_3_RC != ((count_TCU_R932_3 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.firstMsg = 0;
		}
		count_TCU_R932_3 = TCU_R932_3_frame.TCU_R932_3_RC;
	} else {
		((rx_Err_flags*)&p_7_TCU_R932_3_Err)->B.CRCErr = 1;
	}
}
void TCU_R932_2_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.NoMsg = 0;
	TCU_R932_2_frame = *(TCU_R932_2*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 48;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == TCU_R932_2_frame.TCU_R932_2_CS) {
		((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.CRCErr = 0;
	p_7_stAutoClutchStatusFromCAN = 1*TCU_R932_2_frame.stAutoClutchStatus+0;
	p_7_tqTransmInputReqFromCAN = 1*TCU_R932_2_frame.tqTransmInputReq+-500;
	p_7_nEngineSpeedDmdFromCAN = 10*TCU_R932_2_frame.nEngineSpeedDmd+0;
	p_7_stGbxLimpModeFromCAN = 1*TCU_R932_2_frame.stGbxLimpMode+0;
	f_7_bTorqueReqIncrFlagFromCAN = 1*TCU_R932_2_frame.bTorqueReqIncrFlag+0;
	p_7_stEngineSpeedReqFromCAN = 1*TCU_R932_2_frame.stEngineSpeedReq+0;
	f_7_bTorqueReqDecrFlagFromCAN = 1*TCU_R932_2_frame.bTorqueReqDecrFlag+0;
	p_7_stTorqueReqTypeFromCAN = 1*TCU_R932_2_frame.stTorqueReqType+0;
	p_7_tqTransmInputReqResvFromCAN = 1*TCU_R932_2_frame.tqTransmInputReqResv+-500;
		if (!((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.firstMsg) {
			if(TCU_R932_2_frame.TCU_R932_2_RC != ((count_TCU_R932_2 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.firstMsg = 0;
		}
		count_TCU_R932_2 = TCU_R932_2_frame.TCU_R932_2_RC;
	} else {
		((rx_Err_flags*)&p_7_TCU_R932_2_Err)->B.CRCErr = 1;
	}
}
void HVC_HV_Status_Msg_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.NoMsg = 0;
	HVC_HV_Status_Msg_frame = *(HVC_HV_Status_Msg*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 16;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == HVC_HV_Status_Msg_frame.HVC_HV_Status_CS) {
		((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.CRCErr = 0;
	p_7_HVC_HV_Status_ACFromCAN = 1*HVC_HV_Status_Msg_frame.HVC_HV_Status_AC+0;
	p_7_HVC_HV_State_SigFromCAN = 1*HVC_HV_Status_Msg_frame.HVC_HV_State_Sig+0;
	p_7_HVC_eCompHVcur_SigFromCAN = 0.5*HVC_HV_Status_Msg_frame.HVC_eCompHVcur_Sig+0;
		if (!((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.firstMsg = 0;
		}
	} else {
		((rx_Err_flags*)&p_7_HVC_HV_Status_Msg_Err)->B.CRCErr = 1;
	}
}
void Diag_To_ECU_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Diag_To_ECU_Err)->B.NoMsg = 0;
	Diag_To_ECU_frame = *(Diag_To_ECU*)rx_msg->data.byte;
	p_7_Diag_To_ECU_SigFromCAN = 1*Diag_To_ECU_frame.Diag_To_ECU_Sig+0;
		if (!((rx_Err_flags*)&p_7_Diag_To_ECU_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_Diag_To_ECU_Err)->B.firstMsg = 0;
		}
}
void CDA_11_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_CDA_11_Err)->B.NoMsg = 0;
	CDA_11_frame = *(CDA_11*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 24;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == CDA_11_frame.CDA_11_CS) {
		((rx_Err_flags*)&p_7_CDA_11_Err)->B.CRCErr = 0;
	p_7_ACCMotIncFromCAN = 1*CDA_11_frame.ACCMotInc+-30000;
	f_7_ACCMotIncReqFlagFromCAN = 1*CDA_11_frame.ACCMotIncReqFlag+0;
		if (!((rx_Err_flags*)&p_7_CDA_11_Err)->B.firstMsg) {
			if(CDA_11_frame.CDA_11_RC != ((count_CDA_11 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_CDA_11_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_CDA_11_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_CDA_11_Err)->B.firstMsg = 0;
		}
		count_CDA_11 = CDA_11_frame.CDA_11_RC;
	} else {
		((rx_Err_flags*)&p_7_CDA_11_Err)->B.CRCErr = 1;
	}
}
void VAU_EMS_Hash_Immo_RESP_handler(struct can_message_s* rx_msg)
{

//	((rx_Err_flags*)&p_7_VAU_EMS_Hash_Immo_RESP_Err)->B.NoMsg = 0;
//	VAU_EMS_Hash_Immo_RESP_frame = *(VAU_EMS_Hash_Immo_RESP*)rx_msg->data.byte;
//	p_7_Hash_EMSFromCAN = 1*VAU_EMS_Hash_Immo_RESP_frame.Hash_EMS+0;
//		if (!((rx_Err_flags*)&p_7_VAU_EMS_Hash_Immo_RESP_Err)->B.firstMsg) {
//		} else {
//			((rx_Err_flags*)&p_7_VAU_EMS_Hash_Immo_RESP_Err)->B.firstMsg = 0;
//		}
}
void TCU_R932_1_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.NoMsg = 0;
	TCU_R932_1_frame = *(TCU_R932_1*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == TCU_R932_1_frame.TCU_R932_1_CS) {
		((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.CRCErr = 0;
	p_7_TCU_VehicleSpeedFromCAN = 0.01*TCU_R932_1_frame.TCU_VehicleSpeed+0;
	p_7_stGearLvrFromCAN = 1*TCU_R932_1_frame.stGearLvr+0;
	p_7_stGearboxModeFromCAN = 1*TCU_R932_1_frame.stGearboxMode+0;
	p_7_ratEng2GbxTorqueRatioFromCAN = 0.01*TCU_R932_1_frame.ratEng2GbxTorqueRatio+0;
	f_7_TCU_DriverBrakeReqFromCAN = 1*TCU_R932_1_frame.TCU_DriverBrakeReq+0;
	f_7_stManualGbxModeFromCAN = 1*TCU_R932_1_frame.stManualGbxMode+0;
	f_7_bShiftInProgressFromCAN = 1*TCU_R932_1_frame.bShiftInProgress+0;
	p_7_stGbxMILReqFromCAN = 1*TCU_R932_1_frame.stGbxMILReq+0;
	p_7_numGearEngagedFromCAN = 1*TCU_R932_1_frame.numGearEngaged+0;
	p_7_numGearTargetFromCAN = 1*TCU_R932_1_frame.numGearTarget+0;
	f_7_TCU_VehicleSpeed_ValueErrorFromCAN = 1*TCU_R932_1_frame.TCU_VehicleSpeed_ValueError+0;
	p_7_stTransmissionWarningsFromCAN = 1*TCU_R932_1_frame.stTransmissionWarnings+0;
		if (!((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.firstMsg) {
			if(TCU_R932_1_frame.TCU_R932_1_RC != ((count_TCU_R932_1 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.firstMsg = 0;
		}
		count_TCU_R932_1 = TCU_R932_1_frame.TCU_R932_1_RC;
	} else {
		((rx_Err_flags*)&p_7_TCU_R932_1_Err)->B.CRCErr = 1;
	}
}
void SAS_Standard_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.NoMsg = 0;
	SAS_Standard_frame = *(SAS_Standard*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 36;

	if (calc_chksum_XOR4(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == SAS_Standard_frame.Chk_Sum) {
		((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.CRCErr = 0;
	f_7_CALFromCAN = 1*SAS_Standard_frame.CAL+0;
	p_7_SF1_5FromCAN = 1*SAS_Standard_frame.SF1_5+0;
	f_7_TRIMFromCAN = 1*SAS_Standard_frame.TRIM+0;
	p_7_SAS_SpeedFromCAN = 4*SAS_Standard_frame.SAS_Speed+0;
	p_7_SAS_AngleFromCAN = (real32_T)(0.1F * ((signed short)SAS_Standard_frame.SAS_Angle) + 0);
	//p_7_SAS_AngleFromCAN = 0.1*SAS_Standard_frame.SAS_Angle+0;
	f_7_OKFromCAN = 1*SAS_Standard_frame.OK+0;
		if (!((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.firstMsg) {
			if(SAS_Standard_frame.Msg_cnt != ((count_SAS_Standard + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.firstMsg = 0;
		}
		count_SAS_Standard = SAS_Standard_frame.Msg_cnt;
	} else {
		((rx_Err_flags*)&p_7_SAS_Standard_Err)->B.CRCErr = 1;
	}
}
void EPB_Status_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_EPB_Status_Err)->B.NoMsg = 0;
	EPB_Status_frame = *(EPB_Status*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 32;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == EPB_Status_frame.EPB_Status_CS) {
		((rx_Err_flags*)&p_7_EPB_Status_Err)->B.CRCErr = 0;
	p_7_EPB_CurrEPBSwStFromCAN = 1*EPB_Status_frame.EPB_CurrEPBSwSt+0;
	f_7_EPB_BrakeLightReqFromCAN = 1*EPB_Status_frame.EPB_BrakeLightReq+0;
	p_7_EPB_StatusIndReqFromCAN = 1*EPB_Status_frame.EPB_StatusIndReq+0;
	p_7_EPB_CurrParkBrakeStFromCAN = 1*EPB_Status_frame.EPB_CurrParkBrakeSt+0;
	f_7_EPB_AudibleChimeReqFromCAN = 1*EPB_Status_frame.EPB_AudibleChimeReq+0;
	p_7_EPB_TargetDecelFromCAN = 0.05*EPB_Status_frame.EPB_TargetDecel+-4;
	f_7_EPB_DynamicEmergencyApplyFromCAN = 1*EPB_Status_frame.EPB_DynamicEmergencyApply+0;
	p_7_EPB_AppliedForceStFromCAN = 1*EPB_Status_frame.EPB_AppliedForceSt+0;
	f_7_EPB_FailureStsFromCAN = 1*EPB_Status_frame.EPB_FailureSts+0;
		if (!((rx_Err_flags*)&p_7_EPB_Status_Err)->B.firstMsg) {
			if(EPB_Status_frame.EPB_Status_RC != ((count_EPB_Status + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_EPB_Status_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_EPB_Status_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_EPB_Status_Err)->B.firstMsg = 0;
		}
		count_EPB_Status = EPB_Status_frame.EPB_Status_RC;
	} else {
		((rx_Err_flags*)&p_7_EPB_Status_Err)->B.CRCErr = 1;
	}
}
void Diag_Functional_FromPT_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_Diag_Functional_FromPT_Err)->B.NoMsg = 0;
	Diag_Functional_FromPT_frame = *(Diag_Functional_FromPT*)rx_msg->data.byte;
	p_7_Diag_Functional_Sig_FromPTFromCAN = 1*Diag_Functional_FromPT_frame.Diag_Functional_Sig_FromPT+0;
		if (!((rx_Err_flags*)&p_7_Diag_Functional_FromPT_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_Diag_Functional_FromPT_Err)->B.firstMsg = 0;
		}
}
void DMS_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_DMS_01_Err)->B.NoMsg = 0;
	DMS_01_frame = *(DMS_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 16;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == DMS_01_frame.DMS_CRC) {
		((rx_Err_flags*)&p_7_DMS_01_Err)->B.CRCErr = 0;
	p_7_DMS_MsgCounterFromCAN = 1*DMS_01_frame.DMS_MsgCounter+0;
	f_7_UpwardPosReqFromCAN = 1*DMS_01_frame.UpwardPosReq+0;
	p_7_DrivingMode_SigFromCAN = 1*DMS_01_frame.DrivingMode_Sig+0;
	f_7_DMS_HDCReqFromCAN = 1*DMS_01_frame.DMS_HDCReq+0;
	f_7_DMS_ServiceModeFromCAN = 1*DMS_01_frame.DMS_ServiceMode+0;
	f_7_DownwardPosReqFromCAN = 1*DMS_01_frame.DownwardPosReq+0;
		if (!((rx_Err_flags*)&p_7_DMS_01_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_DMS_01_Err)->B.firstMsg = 0;
		}
	} else {
		((rx_Err_flags*)&p_7_DMS_01_Err)->B.CRCErr = 1;
	}
}
void CCU_MSG3_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.NoMsg = 0;
	CCU_MSG3_frame = *(CCU_MSG3*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 32;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == CCU_MSG3_frame.CCU_MSG3_CS) {
		((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.CRCErr = 0;
	p_7_CCU_FANReqFromCAN = 1*CCU_MSG3_frame.CCU_FANReq+0;
		if (!((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.firstMsg) {
			if(CCU_MSG3_frame.CCU_MSG3_RC != ((count_CCU_MSG3 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.firstMsg = 0;
		}
		count_CCU_MSG3 = CCU_MSG3_frame.CCU_MSG3_RC;
	} else {
		((rx_Err_flags*)&p_7_CCU_MSG3_Err)->B.CRCErr = 1;
	}
}
void CCU_HVC_Req_Msg_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.NoMsg = 0;
	CCU_HVC_Req_Msg_frame = *(CCU_HVC_Req_Msg*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 16;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == CCU_HVC_Req_Msg_frame.CCU_HVC_Req_CS) {
		((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.CRCErr = 0;
	f_7_CCU_eCompStateReq_SigFromCAN = 1*CCU_HVC_Req_Msg_frame.CCU_eCompStateReq_Sig+0;
	p_7_CCU_LowTempValveReqFromCAN = 1*CCU_HVC_Req_Msg_frame.CCU_LowTempValveReq+0;
	p_7_CCU_eCompSpeedReq_SigFromCAN = 50*CCU_HVC_Req_Msg_frame.CCU_eCompSpeedReq_Sig+0;
	p_7_CCU_HVC_Req_ACFromCAN = 1*CCU_HVC_Req_Msg_frame.CCU_HVC_Req_AC+0;
		if (!((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.firstMsg = 0;
		}
	} else {
		((rx_Err_flags*)&p_7_CCU_HVC_Req_Msg_Err)->B.CRCErr = 1;
	}
}
void BCM_VEH_STATE_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_BCM_VEH_STATE_Err)->B.NoMsg = 0;
	BCM_VEH_STATE_frame = *(BCM_VEH_STATE*)rx_msg->data.byte;
	f_7_T15_stateFromCAN = 1*BCM_VEH_STATE_frame.T15_state+0;
	f_7_PHline_stateFromCAN = 1*BCM_VEH_STATE_frame.PHline_state+0;
	p_7_SwitchesIndicatorIntensityFromCAN = 0.394*BCM_VEH_STATE_frame.SwitchesIndicatorIntensity+0;
	p_7_HUD_IntensityRequestFromCAN = 1*BCM_VEH_STATE_frame.HUD_IntensityRequest+0;
	f_7_T30c_stateFromCAN = 1*BCM_VEH_STATE_frame.T30c_state+0;
	p_7_VehicleBodyFromCAN = 1*BCM_VEH_STATE_frame.VehicleBody+0;
	p_7_BCM_LVBatteryVoltageFromCAN = 0.075*BCM_VEH_STATE_frame.BCM_LVBatteryVoltage+0;
	f_7_VehicleTypeFromCAN = 1*BCM_VEH_STATE_frame.VehicleType+0;
	f_7_T30i_DisableWarningFromCAN = 1*BCM_VEH_STATE_frame.T30i_DisableWarning+0;
	f_7_T30i_stateFromCAN = 1*BCM_VEH_STATE_frame.T30i_state+0;
	f_7_T30d_Fault_StatusFromCAN = 1*BCM_VEH_STATE_frame.T30d_Fault_Status+0;
	p_7_SwitchesBackgroundIntensityFromCAN = 0.394*BCM_VEH_STATE_frame.SwitchesBackgroundIntensity+0;
	f_7_StealthModeEnFromCAN = 1*BCM_VEH_STATE_frame.StealthModeEn+0;
	f_7_BCM_LaneKeepAssistPushStFromCAN = 1*BCM_VEH_STATE_frame.BCM_LaneKeepAssistPushSt+0;
	f_7_DSline_stateFromCAN = 1*BCM_VEH_STATE_frame.DSline_state+0;
	f_7_T15_Fault_StatusFromCAN = 1*BCM_VEH_STATE_frame.T15_Fault_Status+0;
	f_7_T30d_DisableWarningFromCAN = 1*BCM_VEH_STATE_frame.T30d_DisableWarning+0;
	f_7_T30i_Fault_StatusFromCAN = 1*BCM_VEH_STATE_frame.T30i_Fault_Status+0;
	p_7_VehicleModeStateFromCAN = 1*BCM_VEH_STATE_frame.VehicleModeState+0;
	f_7_T30d_stateFromCAN = 1*BCM_VEH_STATE_frame.T30d_state+0;
		if (!((rx_Err_flags*)&p_7_BCM_VEH_STATE_Err)->B.firstMsg) {
		} else {
			((rx_Err_flags*)&p_7_BCM_VEH_STATE_Err)->B.firstMsg = 0;
		}
}
void BCM_Powertrain_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.NoMsg = 0;
	BCM_Powertrain_frame = *(BCM_Powertrain*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 40;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == BCM_Powertrain_frame.BCM_Powertrain_CS) {
		((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.CRCErr = 0;
	p_7_BonnetAjarRawValStsFromCAN = 1*BCM_Powertrain_frame.BonnetAjarRawValSts+0;
	p_7_AvgFuelLvlFromCAN = 0.5*BCM_Powertrain_frame.AvgFuelLvl+0;
	f_7_RemoteICEStartReqFromCAN = 1*BCM_Powertrain_frame.RemoteICEStartReq+0;
	f_7_T50ActvFromCAN = 1*BCM_Powertrain_frame.T50Actv+0;
	p_7_AMB_TEMP_AVGFromCAN = 0.01*BCM_Powertrain_frame.AMB_TEMP_AVG+-40;
		if (!((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.firstMsg) {
			if(BCM_Powertrain_frame.BCM_Powertrain_RC != ((count_BCM_Powertrain + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.firstMsg = 0;
		}
		count_BCM_Powertrain = BCM_Powertrain_frame.BCM_Powertrain_RC;
	} else {
		((rx_Err_flags*)&p_7_BCM_Powertrain_Err)->B.CRCErr = 1;
	}
}
void BCM_EEM_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.NoMsg = 0;
	BCM_EEM_frame = *(BCM_EEM*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 32;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == BCM_EEM_frame.BCM_EEM_CS) {
		((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.CRCErr = 0;
	f_7_BCMEM_LvPwrNetStsFromCAN = 1*BCM_EEM_frame.BCMEM_LvPwrNetSts+0;
	p_7_BCMEM_VolReqLV_DCDC2FromCAN = 0.1*BCM_EEM_frame.BCMEM_VolReqLV_DCDC2+0;
	p_7_BCMEM_VolReqLV_DCDC1FromCAN = 0.1*BCM_EEM_frame.BCMEM_VolReqLV_DCDC1+0;
	p_7_BCMEM_StPowMgntFromCAN = 1*BCM_EEM_frame.BCMEM_StPowMgnt+0;
	p_7_BCMEM_CurrLimLV_DCDC2FromCAN = 0.1*BCM_EEM_frame.BCMEM_CurrLimLV_DCDC2+0;
	f_7_BCMEM_PowMngtReqDispFromCAN = 1*BCM_EEM_frame.BCMEM_PowMngtReqDisp+0;
	p_7_BCMEM_CurrLimLV_DCDC1FromCAN = 0.1*BCM_EEM_frame.BCMEM_CurrLimLV_DCDC1+0;
		if (!((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.firstMsg) {
			if(BCM_EEM_frame.BCM_EEM_RC != ((count_BCM_EEM + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.firstMsg = 0;
		}
		count_BCM_EEM = BCM_EEM_frame.BCM_EEM_RC;
	} else {
		((rx_Err_flags*)&p_7_BCM_EEM_Err)->B.CRCErr = 1;
	}
}
void ACU_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ACU_01_Err)->B.NoMsg = 0;
	ACU_01_frame = *(ACU_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 16;

	if (calc_chksum_XOR8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ACU_01_frame.ACU_01_CS) {
		((rx_Err_flags*)&p_7_ACU_01_Err)->B.CRCErr = 0;
	p_7_AirbagFrontPassengerStsFromCAN = 1*ACU_01_frame.AirbagFrontPassengerSts+0;
	f_7_ACUSysDeactEnFromCAN = 1*ACU_01_frame.ACUSysDeactEn+0;
	f_7_PassSeatBeltWarningFromCAN = 1*ACU_01_frame.PassSeatBeltWarning+0;
	p_7_RILRequestStatusFromCAN = 1*ACU_01_frame.RILRequestStatus+0;
	f_7_CrashEventDetectedFromCAN = 1*ACU_01_frame.CrashEventDetected+0;
	p_7_FrontBuckleDriver_LFromCAN = 1*ACU_01_frame.FrontBuckleDriver_L+0;
	f_7_RRSeatBeltWarningFromCAN = 1*ACU_01_frame.RRSeatBeltWarning+0;
	f_7_DrivSeatBeltWarningFromCAN = 1*ACU_01_frame.DrivSeatBeltWarning+0;
	f_7_RLSeatBeltWarningFromCAN = 1*ACU_01_frame.RLSeatBeltWarning+0;
		if (!((rx_Err_flags*)&p_7_ACU_01_Err)->B.firstMsg) {
			if(ACU_01_frame.ACU_01_RC != ((count_ACU_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ACU_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ACU_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ACU_01_Err)->B.firstMsg = 0;
		}
		count_ACU_01 = ACU_01_frame.ACU_01_RC;
	} else {
		((rx_Err_flags*)&p_7_ACU_01_Err)->B.CRCErr = 1;
	}
}
