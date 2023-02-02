#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 tqPwrTrnNoIntv : 11;
	uint32 ObdDriveCycleCmplt : 1;
	uint32 ObdWarmUpCycleCmplt : 1;
	uint32 reserved_0 : 3;
	uint32 AccPedPosADC1 : 16;
	uint32 AccPedPosADC2 : 16;
	uint32 reserved_1 : 4;
	uint32 EMS_8_RC : 4;
	uint32 EMS_8_CS : 8;
} EMS_8;

typedef char struct_size_test[sizeof(EMS_8) == 8? 1: -1];

typedef struct {
	uint32 ratThrottle : 8;
	uint32 pBoostPressure : 8;
	uint32 vVehicleEMS : 9;
	uint32 reserved_0 : 7;
	uint32 reserved_1 : 32;
} EMS_7;

typedef char struct_size_test[sizeof(EMS_7) == 8? 1: -1];

typedef struct {
	uint32 nICEngineSpeed1 : 16;
	uint32 bPowertrainSignalSpdErr : 1;
	uint32 bICEngineFCO : 1;
	uint32 reserved_0 : 6;
	uint32 nPwrTrnSpd : 16;
	uint32 EMS_4_RC : 4;
	uint32 reserved_1 : 4;
	uint32 EMS_4_CS : 8;
	uint32 reserved_2 : 8;
} EMS_4;

typedef char struct_size_test[sizeof(EMS_4) == 8? 1: -1];

typedef struct {
	uint32 nIdleSpdTargetAct : 14;
	uint32 bPwrTrnTorqueEstErr : 1;
	uint32 tqDriverTorqueDmd : 11;
	uint32 ratAccPed : 8;
	uint32 stKickDown : 2;
	uint32 bAccPedSensorFail : 1;
	uint32 ratAccPedSts : 1;
	uint32 reserved_0 : 2;
	uint32 EMS_3_RC : 4;
	uint32 reserved_1 : 4;
	uint32 EMS_3_CS : 8;
	uint32 reserved_2 : 8;
} EMS_3;

typedef char struct_size_test[sizeof(EMS_3) == 8? 1: -1];

typedef struct {
	uint32 tqTransInputTorqueEff : 11;
	uint32 tqEMotorTorque : 11;
	uint32 tqICEngineTorque : 11;
	uint32 EMS_2_RC : 4;
	uint32 reserved_0 : 3;
	uint32 EMS_2_CS : 8;
	uint32 reserved_1 : 16;
} EMS_2;

typedef char struct_size_test[sizeof(EMS_2) == 8? 1: -1];

typedef struct {
	uint32 vCrCtlVSetpoint : 9;
	uint32 nPwrTrnSpdLimitCurr : 6;
	uint32 bT15on : 1;
	uint32 pAmbientPres : 8;
	uint32 stLLimStatus : 3;
	uint32 stCrCtlState : 3;
	uint32 reserved_0 : 2;
	uint32 tCoolant : 8;
	uint32 reserved_1 : 24;
} EMS_1;

typedef char struct_size_test[sizeof(EMS_1) == 8? 1: -1];

typedef struct {
	uint32 EngOilTemp : 8;
	uint32 OIL_Level : 7;
	uint32 reserved_0 : 1;
	uint32 MIL_IND_BLINK : 1;
	uint32 EngOilLvInd : 2;
	uint32 MIL_OnRq : 1;
	uint32 LTC_CoolantLvl : 1;
	uint32 OilPressureWarning : 1;
	uint32 reserved_1 : 10;
	uint32 reserved_2 : 32;
} ECU_Indicators;

typedef char struct_size_test[sizeof(ECU_Indicators) == 8? 1: -1];

typedef struct {
	uint32 MMotMax : 16;
	uint32 MMotActLm : 16;
	uint32 reserved_0 : 4;
	uint32 ECU_16_RC : 4;
	uint32 ECU_16_CS : 8;
	uint32 reserved_1 : 16;
} ECU_16;

typedef char struct_size_test[sizeof(ECU_16) == 8? 1: -1];

typedef struct {
	uint32 M_MotAct : 16;
	uint32 M_MotDrag : 16;
	uint32 M_MotClutch : 16;
	uint32 reserved_0 : 4;
	uint32 ECU_14_RC : 4;
	uint32 ECU_14_CS : 8;
} ECU_14;

typedef char struct_size_test[sizeof(ECU_14) == 8? 1: -1];

typedef struct {
	uint32 Diag_From_ECU_Sig : 8;
	uint32 reserved_0 : 24;
	uint32 reserved_1 : 32;
} Diag_From_ECU;

typedef char struct_size_test[sizeof(Diag_From_ECU) == 8? 1: -1];

typedef struct {
	uint32 EMS_eCompHVStateRequest_Sig : 1;
	uint32 EMS_eCompOnPerm_Sig : 1;
	uint32 EMS_eCompChillerRequest_Sig : 1;
	uint32 EMS_eCompHVCurLimit_Sig : 9;
	uint32 EMS_HVC_Req_AC : 4;
	uint32 EMS_HVC_Req_CS : 8;
	uint32 reserved_0 : 8;
	uint32 reserved_1 : 32;
} EMS_HVC_Req_Msg;

typedef char struct_size_test[sizeof(EMS_HVC_Req_Msg) == 8? 1: -1];

typedef struct {
	uint32 EMS_ActCurrLV_DCDC2 : 16;
	uint32 EMS_ActVoltLV_DCDC2 : 10;
	uint32 EMS_ErrPrfLim_DCDC2 : 1;
	uint32 EMS_Err_DCDC2 : 1;
	uint32 EMS_stMode_DCDC2 : 1;
	uint32 reserved_0 : 3;
	uint32 EMS_UtilRate_DCDC2 : 10;
	uint32 reserved_1 : 2;
	uint32 EMS_EEM_02_RC : 4;
	uint32 EMS_EEM_02_CS : 8;
	uint32 reserved_2 : 8;
} EMS_EEM_02;

typedef char struct_size_test[sizeof(EMS_EEM_02) == 8? 1: -1];

typedef struct {
	uint32 EMS_ActCurrLV_DCDC1 : 16;
	uint32 EMS_ActVoltLV_DCDC1 : 10;
	uint32 EMS_ErrPrfLim_DCDC1 : 1;
	uint32 EMS_Err_DCDC1 : 1;
	uint32 EMS_stMode_DCDC1 : 1;
	uint32 reserved_0 : 3;
	uint32 EMS_UtilRate_DCDC1 : 10;
	uint32 reserved_1 : 2;
	uint32 EMS_EEM_01_RC : 4;
	uint32 EMS_EEM_01_CS : 8;
	uint32 reserved_2 : 8;
} EMS_EEM_01;

typedef char struct_size_test[sizeof(EMS_EEM_01) == 8? 1: -1];

typedef struct {
	uint32 CoEng_st : 3;
	uint32 BMS_ActualTemperature : 8;
	uint32 reserved_0 : 1;
	uint32 ECU_Veh_02_RC : 4;
	uint32 ECU_Veh_02_CS : 8;
	uint32 reserved_1 : 8;
	uint32 reserved_2 : 32;
} ECU_Veh_02;

typedef char struct_size_test[sizeof(ECU_Veh_02) == 8? 1: -1];

typedef struct {
	uint32 nICEngineSpeed3 : 16;
	uint32 EngCoolTemp : 8;
	uint32 BARO_ENG : 8;
	uint32 AccelPdlPosn_OBD : 8;
	uint32 EngTrqStatic : 13;
	uint32 HvSystemFailure : 2;
	uint32 CoolLiquidLowWarning : 1;
	uint32 InstFuelConsumption : 8;
} ECU_Veh;

typedef char struct_size_test[sizeof(ECU_Veh) == 8? 1: -1];

