#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 nIdleSpeedReq : 10;
	uint32 bIdleSpeedReq : 1;
	uint32 reserved_0 : 1;
	uint32 TCU_R932_5_RC : 4;
	uint32 TCU_R932_5_CS : 8;
	uint32 reserved_1 : 8;
	uint32 reserved_2 : 32;
} TCU_R932_5;

typedef char struct_size_test[sizeof(TCU_R932_5) == 8? 1: -1];

typedef struct {
	uint32 tiEngineSpeedCtrlSync : 10;
	uint32 tqGbxTorqueLoss : 11;
	uint32 reserved_0 : 3;
	uint32 tGbxOil : 8;
	uint32 reserved_1 : 4;
	uint32 TCU_R932_4_RC : 4;
	uint32 TCU_R932_4_CS : 8;
	uint32 nGearBoxShaftOutSpeed : 15;
	uint32 reserved_2 : 1;
} TCU_R932_4;

typedef char struct_size_test[sizeof(TCU_R932_4) == 8? 1: -1];

typedef struct {
	uint32 vGbxMaxVehSpdLimit : 9;
	uint32 tqTransmInputMax : 11;
	uint32 reserved_0 : 2;
	uint32 stFrcTrqAdapEMS : 2;
	uint32 dTrqPwrTrnGradLimit : 8;
	uint32 nEngineSpeedLimit : 10;
	uint32 reserved_1 : 2;
	uint32 TCU_R932_3_RC : 4;
	uint32 TCU_R932_3_CS : 8;
	uint32 reserved_2 : 8;
} TCU_R932_3;

typedef char struct_size_test[sizeof(TCU_R932_3) == 8? 1: -1];

typedef struct {
	uint32 tqTransmInputReq : 11;
	uint32 tqTransmInputReqResv : 11;
	uint32 bTorqueReqIncrFlag : 1;
	uint32 bTorqueReqDecrFlag : 1;
	uint32 stTorqueReqType : 2;
	uint32 nEngineSpeedDmd : 10;
	uint32 stAutoClutchStatus : 3;
	uint32 stEngineSpeedReq : 2;
	uint32 stGbxLimpMode : 3;
	uint32 TCU_R932_2_RC : 4;
	uint32 TCU_R932_2_CS : 8;
	uint32 reserved_0 : 8;
} TCU_R932_2;

typedef char struct_size_test[sizeof(TCU_R932_2) == 8? 1: -1];

typedef struct {
	uint32 HVC_HV_State_Sig : 3;
	uint32 HVC_eCompHVcur_Sig : 7;
	uint32 reserved_0 : 2;
	uint32 HVC_HV_Status_AC : 4;
	uint32 HVC_HV_Status_CS : 8;
	uint32 reserved_1 : 8;
	uint32 reserved_2 : 32;
} HVC_HV_Status_Msg;

typedef char struct_size_test[sizeof(HVC_HV_Status_Msg) == 8? 1: -1];

typedef struct {
	uint32 Diag_To_ECU_Sig : 8;
	uint32 reserved_0 : 24;
	uint32 reserved_1 : 32;
} Diag_To_ECU;

typedef char struct_size_test[sizeof(Diag_To_ECU) == 8? 1: -1];

typedef struct {
	uint32 ACCMotInc : 16;
	uint32 ACCMotIncReqFlag : 1;
	uint32 reserved_0 : 3;
	uint32 CDA_11_RC : 4;
	uint32 CDA_11_CS : 8;
	uint32 reserved_1 : 32;
} CDA_11;

typedef char struct_size_test[sizeof(CDA_11) == 8? 1: -1];

typedef struct {
	uint64 Hash_EMS : 64;
} VAU_EMS_Hash_Immo_RESP;

typedef char struct_size_test[sizeof(VAU_EMS_Hash_Immo_RESP) == 8? 1: -1];

typedef struct {
	uint32 numGearTarget : 4;
	uint32 numGearEngaged : 4;
	uint32 ratEng2GbxTorqueRatio : 11;
	uint32 stGearLvr : 3;
	uint32 stGbxMILReq : 2;
	uint32 stGearboxMode : 3;
	uint32 stTransmissionWarnings : 4;
	uint32 bShiftInProgress : 1;
	uint32 TCU_VehicleSpeed_ValueError : 1;
	uint32 stManualGbxMode : 1;
	uint32 TCU_DriverBrakeReq : 1;
	uint32 reserved_0 : 1;
	uint32 TCU_VehicleSpeed : 16;
	uint32 TCU_R932_1_RC : 4;
	uint32 TCU_R932_1_CS : 8;
} TCU_R932_1;

typedef char struct_size_test[sizeof(TCU_R932_1) == 8? 1: -1];

typedef struct {
	uint32 SAS_Angle : 16;
	uint32 SAS_Speed : 8;
	uint32 OK : 1;
	uint32 CAL : 1;
	uint32 TRIM : 1;
	uint32 SF1_5 : 5;
	uint32 Msg_cnt : 4;
	uint32 Chk_Sum : 4;
	uint32 reserved_0 : 24;
} SAS_Standard;

typedef char struct_size_test[sizeof(SAS_Standard) == 8? 1: -1];

typedef struct {
	uint32 EPB_AppliedForceSt : 3;
	uint32 EPB_BrakeLightReq : 1;
	uint32 EPB_CurrParkBrakeSt : 3;
	uint32 EPB_AudibleChimeReq : 1;
	uint32 EPB_TargetDecel : 8;
	uint32 EPB_CurrEPBSwSt : 3;
	uint32 reserved_0 : 1;
	uint32 EPB_DynamicEmergencyApply : 1;
	uint32 EPB_StatusIndReq : 2;
	uint32 EPB_FailureSts : 1;
	uint32 reserved_1 : 4;
	uint32 EPB_Status_RC : 4;
	uint32 EPB_Status_CS : 8;
	uint32 reserved_2 : 24;
} EPB_Status;

typedef char struct_size_test[sizeof(EPB_Status) == 8? 1: -1];

typedef struct {
	uint32 Diag_Functional_Sig_FromPT : 8;
	uint32 reserved_0 : 24;
	uint32 reserved_1 : 32;
} Diag_Functional_FromPT;

typedef char struct_size_test[sizeof(Diag_Functional_FromPT) == 8? 1: -1];

typedef struct {
	uint32 DrivingMode_Sig : 4;
	uint32 DMS_HDCReq : 1;
	uint32 UpwardPosReq : 1;
	uint32 DownwardPosReq : 1;
	uint32 DMS_ServiceMode : 1;
	uint32 DMS_MsgCounter : 4;
	uint32 reserved_0 : 4;
	uint32 DMS_CRC : 8;
	uint32 reserved_1 : 8;
	uint32 reserved_2 : 32;
} DMS_01;

typedef char struct_size_test[sizeof(DMS_01) == 8? 1: -1];

typedef struct {
	uint32 CCU_FANReq : 7;
	uint32 reserved_0 : 17;
	uint32 CCU_MSG3_RC : 4;
	uint32 reserved_1 : 4;
	uint32 CCU_MSG3_CS : 8;
	uint32 reserved_2 : 24;
} CCU_MSG3;

typedef char struct_size_test[sizeof(CCU_MSG3) == 8? 1: -1];

typedef struct {
	uint32 CCU_eCompSpeedReq_Sig : 8;
	uint32 CCU_eCompStateReq_Sig : 1;
	uint32 CCU_LowTempValveReq : 2;
	uint32 reserved_0 : 1;
	uint32 CCU_HVC_Req_AC : 4;
	uint32 CCU_HVC_Req_CS : 8;
	uint32 reserved_1 : 8;
	uint32 reserved_2 : 32;
} CCU_HVC_Req_Msg;

typedef char struct_size_test[sizeof(CCU_HVC_Req_Msg) == 8? 1: -1];

typedef struct {
	uint32 T15_state : 1;
	uint32 T30d_state : 1;
	uint32 T30i_state : 1;
	uint32 T30c_state : 1;
	uint32 DSline_state : 1;
	uint32 PHline_state : 1;
	uint32 StealthModeEn : 1;
	uint32 VehicleType : 1;
	uint32 VehicleBody : 4;
	uint32 BCM_LaneKeepAssistPushSt : 1;
	uint32 T15_Fault_Status : 1;
	uint32 T30i_DisableWarning : 1;
	uint32 T30i_Fault_Status : 1;
	uint32 HUD_IntensityRequest : 8;
	uint32 T30d_DisableWarning : 1;
	uint32 T30d_Fault_Status : 1;
	uint32 reserved_0 : 6;
	uint32 SwitchesIndicatorIntensity : 8;
	uint32 SwitchesBackgroundIntensity : 8;
	uint32 VehicleModeState : 4;
	uint32 reserved_1 : 4;
	uint32 BCM_LVBatteryVoltage : 8;
} BCM_VEH_STATE;

typedef char struct_size_test[sizeof(BCM_VEH_STATE) == 8? 1: -1];

typedef struct {
	uint32 AMB_TEMP_AVG : 16;
	uint32 AvgFuelLvl : 9;
	uint32 BonnetAjarRawValSts : 4;
	uint32 T50Actv : 1;
	uint32 RemoteICEStartReq : 1;
	uint32 reserved_0 : 1;
	uint32 BCM_Powertrain_RC : 4;
	uint32 reserved_1 : 4;
	uint32 BCM_Powertrain_CS : 8;
	uint32 reserved_2 : 16;
} BCM_Powertrain;

typedef char struct_size_test[sizeof(BCM_Powertrain) == 8? 1: -1];

typedef struct {
	uint32 BCMEM_VolReqLV_DCDC1 : 10;
	uint32 BCMEM_StPowMgnt : 3;
	uint32 BCMEM_PowMngtReqDisp : 1;
	uint32 BCMEM_LvPwrNetSts : 1;
	uint32 reserved_0 : 1;
	uint32 BCMEM_VolReqLV_DCDC2 : 10;
	uint32 reserved_1 : 2;
	uint32 BCM_EEM_RC : 4;
	uint32 BCM_EEM_CS : 8;
	uint32 BCMEM_CurrLimLV_DCDC1 : 12;
	uint32 BCMEM_CurrLimLV_DCDC2 : 12;
} BCM_EEM;

typedef char struct_size_test[sizeof(BCM_EEM) == 8? 1: -1];

typedef struct {
	uint32 CrashEventDetected : 1;
	uint32 ACUSysDeactEn : 1;
	uint32 DrivSeatBeltWarning : 1;
	uint32 PassSeatBeltWarning : 1;
	uint32 RILRequestStatus : 2;
	uint32 AirbagFrontPassengerSts : 2;
	uint32 RLSeatBeltWarning : 1;
	uint32 RRSeatBeltWarning : 1;
	uint32 FrontBuckleDriver_L : 2;
	uint32 ACU_01_RC : 4;
	uint32 ACU_01_CS : 8;
	uint32 reserved_0 : 8;
	uint32 reserved_1 : 32;
} ACU_01;

typedef char struct_size_test[sizeof(ACU_01) == 8? 1: -1];

