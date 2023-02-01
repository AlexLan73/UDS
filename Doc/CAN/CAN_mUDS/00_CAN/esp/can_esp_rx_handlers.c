#include "can_esp_rx_handlers_private.h"

void ESP_YRS_03_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.NoMsg = 0;
	ESP_YRS_03_frame = *(ESP_YRS_03*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ESP_YRS_03_frame.ESP_YRS_03_CS) {
		((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.CRCErr = 0;
	p_7_AX_STATFromCAN = 1*ESP_YRS_03_frame.AX_STAT+0;
	p_7_Reserve2FromCAN = 1*ESP_YRS_03_frame.Reserve2+0;
	p_7_AXFromCAN = 0.0001274*ESP_YRS_03_frame.AX+-4.1745;
	p_7_Reserve3FromCAN = 1*ESP_YRS_03_frame.Reserve3+0;
	p_7_HardCodedFromCAN = 1*ESP_YRS_03_frame.HardCoded+0;
	p_7_NotSupportedFromCAN = 1*ESP_YRS_03_frame.NotSupported+0;
		if (!((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.firstMsg) {
			if(ESP_YRS_03_frame.ESP_YRS_03_RC != ((count_ESP_YRS_03 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.firstMsg = 0;
		}
		count_ESP_YRS_03 = ESP_YRS_03_frame.ESP_YRS_03_RC;
	} else {
		((rx_Err_flags*)&p_7_ESP_YRS_03_Err)->B.CRCErr = 1;
	}
}
void ESP_01_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ESP_01_Err)->B.NoMsg = 0;
	ESP_01_frame = *(ESP_01*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ESP_01_frame.ESP_01_CS) {
		((rx_Err_flags*)&p_7_ESP_01_Err)->B.CRCErr = 0;
	f_7_BMsrFromCAN = 1*ESP_01_frame.BMsr+0;
	f_7_BAscFromCAN = 1*ESP_01_frame.BAsc+0;
	p_7_MMotIncFromCAN = 1*ESP_01_frame.MMotInc+-30000;
	p_7_MMotRedFastFromCAN = 1*ESP_01_frame.MMotRedFast+-30000;
	p_7_MMotRedFromCAN = 1*ESP_01_frame.MMotRed+-30000;
		if (!((rx_Err_flags*)&p_7_ESP_01_Err)->B.firstMsg) {
			if(ESP_01_frame.ESP_01_RC != ((count_ESP_01 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ESP_01_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ESP_01_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ESP_01_Err)->B.firstMsg = 0;
		}
		count_ESP_01 = ESP_01_frame.ESP_01_RC;
	} else {
		((rx_Err_flags*)&p_7_ESP_01_Err)->B.CRCErr = 1;
	}
}
void ESP_03_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ESP_03_Err)->B.NoMsg = 0;
	ESP_03_frame = *(ESP_03*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ESP_03_frame.ESP_03_CS) {
		((rx_Err_flags*)&p_7_ESP_03_Err)->B.CRCErr = 0;
	p_7_WheelDirectionInfo_RRFromCAN = 1*ESP_03_frame.WheelDirectionInfo_RR+0;
	p_7_WheelDirectionInfo_RLFromCAN = 1*ESP_03_frame.WheelDirectionInfo_RL+0;
	p_7_WheelSpeed_RRFromCAN = 0.01*ESP_03_frame.WheelSpeed_RR+0;
	f_7_WheelSpeed_ValueError_RLFromCAN = 1*ESP_03_frame.WheelSpeed_ValueError_RL+0;
	f_7_WheelSpeed_ValueError_RRFromCAN = 1*ESP_03_frame.WheelSpeed_ValueError_RR+0;
	p_7_WheelSpeed_RLFromCAN = 0.01*ESP_03_frame.WheelSpeed_RL+0;
		if (!((rx_Err_flags*)&p_7_ESP_03_Err)->B.firstMsg) {
			if(ESP_03_frame.ESP_03_RC != ((count_ESP_03 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ESP_03_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ESP_03_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ESP_03_Err)->B.firstMsg = 0;
		}
		count_ESP_03 = ESP_03_frame.ESP_03_RC;
	} else {
		((rx_Err_flags*)&p_7_ESP_03_Err)->B.CRCErr = 1;
	}
}
void ESP_02_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ESP_02_Err)->B.NoMsg = 0;
	ESP_02_frame = *(ESP_02*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ESP_02_frame.ESP_02_CS) {
		((rx_Err_flags*)&p_7_ESP_02_Err)->B.CRCErr = 0;
	p_7_WheelDirectionInfo_FLFromCAN = 1*ESP_02_frame.WheelDirectionInfo_FL+0;
	f_7_WheelSpeed_ValueError_FRFromCAN = 1*ESP_02_frame.WheelSpeed_ValueError_FR+0;
	p_7_WheelSpeed_FLFromCAN = 0.01*ESP_02_frame.WheelSpeed_FL+0;
	f_7_WheelSpeed_ValueError_FLFromCAN = 1*ESP_02_frame.WheelSpeed_ValueError_FL+0;
	p_7_WheelDirectionInfo_FRFromCAN = 1*ESP_02_frame.WheelDirectionInfo_FR+0;
	p_7_WheelSpeed_FRFromCAN = 0.01*ESP_02_frame.WheelSpeed_FR+0;
		if (!((rx_Err_flags*)&p_7_ESP_02_Err)->B.firstMsg) {
			if(ESP_02_frame.ESP_02_RC != ((count_ESP_02 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ESP_02_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ESP_02_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ESP_02_Err)->B.firstMsg = 0;
		}
		count_ESP_02 = ESP_02_frame.ESP_02_RC;
	} else {
		((rx_Err_flags*)&p_7_ESP_02_Err)->B.CRCErr = 1;
	}
}
void ESP_04_handler(struct can_message_s* rx_msg)
{

	((rx_Err_flags*)&p_7_ESP_04_Err)->B.NoMsg = 0;
	ESP_04_frame = *(ESP_04*)rx_msg->data.byte;
	uint8 crc_start_bit_position = 56;

	if (calc_CRC8(rx_msg->data.byte, rx_msg->length, crc_start_bit_position) == ESP_04_frame.ESP_04_CS) {
		((rx_Err_flags*)&p_7_ESP_04_Err)->B.CRCErr = 0;
	f_7_Bls_OutFromCAN = 1*ESP_04_frame.Bls_Out+0;
	f_7_CtlActiveAbsFromCAN = 1*ESP_04_frame.CtlActiveAbs+0;
	f_7_CtlActiveHDCFromCAN = 1*ESP_04_frame.CtlActiveHDC+0;
	f_7_BLS_FaultFromCAN = 1*ESP_04_frame.BLS_Fault+0;
	f_7_CtlActiveTcsFromCAN = 1*ESP_04_frame.CtlActiveTcs+0;
	f_7_ESP_LampFromCAN = 1*ESP_04_frame.ESP_Lamp+0;
	f_7_CddActive_2FromCAN = 1*ESP_04_frame.CddActive_2+0;
	f_7_CtlActiveVdcFromCAN = 1*ESP_04_frame.CtlActiveVdc+0;
	f_7_CDPDecelActiveFromCAN = 1*ESP_04_frame.CDPDecelActive+0;
	f_7_AVH_ActiveFromCAN = 1*ESP_04_frame.AVH_Active+0;
	p_7_RequestToEPBFromCAN = 1*ESP_04_frame.RequestToEPB+0;
	f_7_VehicleSpeed_ValueErrorFromCAN = 1*ESP_04_frame.VehicleSpeed_ValueError+0;
	f_7_BlaFromCAN = 1*ESP_04_frame.Bla+0;
	f_7_EBD_LampFromCAN = 1*ESP_04_frame.EBD_Lamp+0;
	f_7_CtlActiveEbdFromCAN = 1*ESP_04_frame.CtlActiveEbd+0;
	f_7_ABS_LampFromCAN = 1*ESP_04_frame.ABS_Lamp+0;
	f_7_HDC_rejectedFromCAN = 1*ESP_04_frame.HDC_rejected+0;
	f_7_EmergencyBrakingFromCAN = 1*ESP_04_frame.EmergencyBraking+0;
	p_7_VehicleSpeedFromCAN = 0.01*ESP_04_frame.VehicleSpeed+0;
	f_7_CDPDecelAvailableFromCAN = 1*ESP_04_frame.CDPDecelAvailable+0;
	f_7_Gearshift_InhibitFromCAN = 1*ESP_04_frame.Gearshift_Inhibit+0;
	f_7_TCS_FaultFromCAN = 1*ESP_04_frame.TCS_Fault+0;
	f_7_PEBWarningLampReqFromCAN = 1*ESP_04_frame.PEBWarningLampReq+0;
	f_7_Passive_LampFromCAN = 1*ESP_04_frame.Passive_Lamp+0;
	p_7_HDC_SpeedLimitFromCAN = 1*ESP_04_frame.HDC_SpeedLimit+0;
	f_7_HDC_ActivatedFromCAN = 1*ESP_04_frame.HDC_Activated+0;
		if (!((rx_Err_flags*)&p_7_ESP_04_Err)->B.firstMsg) {
			if(ESP_04_frame.ESP_04_RC != ((count_ESP_04 + 1)&0x0F)) {
				((rx_Err_flags*)&p_7_ESP_04_Err)->B.RCErr = 1;
			} else {
				((rx_Err_flags*)&p_7_ESP_04_Err)->B.RCErr = 0;
			}
		} else {
			((rx_Err_flags*)&p_7_ESP_04_Err)->B.firstMsg = 0;
		}
		count_ESP_04 = ESP_04_frame.ESP_04_RC;
	} else {
		((rx_Err_flags*)&p_7_ESP_04_Err)->B.CRCErr = 1;
	}
}
