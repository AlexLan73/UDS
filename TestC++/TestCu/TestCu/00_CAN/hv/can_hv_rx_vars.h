#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 INV_05_Checksum : 8;
	uint32 INV_05_AliveCounter : 4;
	uint32 INV_HVReady : 1;
	uint32 INV_SleepInd : 1;
	uint32 INV_InitFinished : 1;
	uint32 INV_TrqLimitsExtended : 1;
	uint32 INV_ErrEmergency : 1;
	uint32 INV_ErrEMotorFreeWheeling : 1;
	uint32 INV_ErrActvShoCirc : 1;
	uint32 INV_ErrPerformance : 1;
	uint32 INV_ActualMode : 4;
	uint32 INV_MinEMotorTorque : 10;
	uint32 INV_MaxEMotorTorque : 10;
	uint32 INV_MinEMotorTorqueFast : 10;
	uint32 INV_MaxEMotorTorqueFast : 10;
} Hyb_Sys_INV_05;

typedef char struct_size_test[sizeof(Hyb_Sys_INV_05) == 8? 1: -1];

typedef struct {
	uint32 INV_04_Checksum : 8;
	uint32 INV_04_AliveCounter : 4;
	uint32 INV_ErrorLampActive : 1;
	uint32 INV_MILReq : 1;
	uint32 INV_WarnLampActive : 1;
	uint32 reserved_0 : 1;
	uint32 INV_RotorTemperature : 8;
	uint32 INV_EMotorTemperature : 8;
	uint32 INV_Temperature : 8;
	uint32 reserved_1 : 24;
} Hyb_Sys_INV_04;

typedef char struct_size_test[sizeof(Hyb_Sys_INV_04) == 8? 1: -1];

typedef struct {
	uint32 INV_03_Checksum : 8;
	uint32 INV_03_AliveCounter : 4;
	uint32 INV_MinEMotorTorqueSlow : 10;
	uint32 INV_HVAuxTorque : 10;
	uint32 INV_MinTurnPointSpeed : 8;
	uint32 INV_MaxTurnPointSpeed : 8;
	uint32 INV_MaxEMotorTorqueSlow : 10;
	uint32 reserved_0 : 6;
} Hyb_Sys_INV_03;

typedef char struct_size_test[sizeof(Hyb_Sys_INV_03) == 8? 1: -1];

typedef struct {
	uint32 INV_02_Checksum : 8;
	uint32 INV_02_AliveCounter : 4;
	uint32 INV_DiagReq : 1;
	uint32 INV_ErrTempDerating : 1;
	uint32 reserved_0 : 2;
	uint32 INV_ActualVoltage : 12;
	uint32 INV_ActualCurrent : 12;
	uint32 INV_PowerLoss : 8;
	uint32 reserved_1 : 16;
} Hyb_Sys_INV_02;

typedef char struct_size_test[sizeof(Hyb_Sys_INV_02) == 8? 1: -1];

typedef struct {
	uint32 INV_01_Checksum : 8;
	uint32 INV_01_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 INV_ActualEngineSpeed : 16;
	uint32 INV_ActualTorque : 12;
	uint32 reserved_1 : 20;
} Hyb_Sys_INV_01;

typedef char struct_size_test[sizeof(Hyb_Sys_INV_01) == 8? 1: -1];

typedef struct {
	uint32 DC_02_Checksum : 8;
	uint32 DC_02_AliveCounter : 4;
	uint32 DC_ActCurrentLV : 10;
	uint32 DC_ErrTempDerating : 1;
	uint32 reserved_0 : 1;
	uint32 DC_RelLoad : 8;
	uint32 DC_ActualTemperature : 8;
	uint32 DC_ActVoltageLV : 8;
	uint32 reserved_1 : 16;
} Hyb_Sys_DC_02;

typedef char struct_size_test[sizeof(Hyb_Sys_DC_02) == 8? 1: -1];

typedef struct {
	uint32 DC_01_Checksum : 8;
	uint32 DC_01_AliveCounter : 4;
	uint32 DC_SleepInd : 1;
	uint32 DC_ErrInternal : 1;
	uint32 DC_ErrVoltage : 1;
	uint32 DC_ErrPerformance : 1;
	uint32 DC_ActCurrentHV : 10;
	uint32 reserved_0 : 2;
	uint32 DC_ActVoltageHV : 12;
	uint32 reserved_1 : 5;
	uint32 DC_ActualMode : 3;
	uint32 reserved_2 : 16;
} Hyb_Sys_DC_01;

typedef char struct_size_test[sizeof(Hyb_Sys_DC_01) == 8? 1: -1];

typedef struct {
	uint32 BMS_04_Checksum : 8;
	uint32 BMS_04_AliveCounter : 4;
	uint32 BMS_ErrorLampActive : 1;
	uint32 BMS_MILReq : 1;
	uint32 BMS_BalancingReq : 1;
	uint32 BMS_WarnLampActive : 1;
	uint32 BMS_Temperature_Inlet : 8;
	uint32 BMS_SOH : 8;
	uint32 BMS_ActualTemperature_ISig_4 : 8;
	uint32 BMS_MinVoltage : 10;
	uint32 BMS_MaxVoltage : 10;
	uint32 reserved_0 : 2;
	uint32 BMS_BatteryHeaterState : 2;
} Hyb_Sys_BMS_04;

typedef char struct_size_test[sizeof(Hyb_Sys_BMS_04) == 8? 1: -1];

typedef struct {
	uint32 BMS_03_Checksum : 8;
	uint32 BMS_03_AliveCounter : 4;
	uint32 BMS_ExtCurLimitsAct : 1;
	uint32 reserved_0 : 3;
	uint32 BMS_MinDisChargeVoltFast : 10;
	uint32 BMS_MaxDisCharCurrentFast : 10;
	uint32 BMS_MaxCharCurrentFast : 10;
	uint32 BMS_MaxChargeVoltFast : 10;
	uint32 reserved_1 : 8;
} Hyb_Sys_BMS_03;

typedef char struct_size_test[sizeof(Hyb_Sys_BMS_03) == 8? 1: -1];

typedef struct {
	uint32 BMS_02_Checksum : 8;
	uint32 BMS_02_AliveCounter : 4;
	uint32 BMS_MaxDisCharCurrentSlow : 10;
	uint32 BMS_SOC : 8;
	uint32 BMS_MaxChargeVoltSlow : 10;
	uint32 BMS_MinDisChargeVoltSlow : 10;
	uint32 BMS_MaxCharCurrentSlow : 10;
	uint32 reserved_0 : 4;
} Hyb_Sys_BMS_02;

typedef char struct_size_test[sizeof(Hyb_Sys_BMS_02) == 8? 1: -1];

typedef struct {
	uint32 BMS_01_Checksum : 8;
	uint32 BMS_01_AliveCounter : 4;
	uint32 BMS_ActualMode : 3;
	uint32 BMS_SleepInd : 1;
	uint32 BMS_ActualCurrent : 12;
	uint32 BMS_InitFinished : 1;
	uint32 BMS_IsolationCheckActive : 1;
	uint32 BMS_ErrPilotLineOpen : 1;
	uint32 BMS_ErrHVBatLowPrio : 1;
	uint32 BMS_ActualVoltage : 12;
	uint32 BMS_ErrHVBatHighPrio : 1;
	uint32 BMS_ErrMCWelded : 1;
	uint32 BMS_ErrMCOpen : 1;
	uint32 BMS_ErrPerformance : 1;
	uint32 BMS_ErrIsolation : 1;
	uint32 BMS_ErrColdStart : 1;
	uint32 BMS_ErrEmergency : 1;
	uint32 BMS_bChrgrPlgIn : 1;
	uint32 reserved_0 : 12;
} Hyb_Sys_BMS_01;

typedef char struct_size_test[sizeof(Hyb_Sys_BMS_01) == 8? 1: -1];

typedef struct {
// Diag_From_INC message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} Diag_From_INC;

typedef char struct_size_test[sizeof(Diag_From_INC) == 8? 1: -1];

typedef struct {
// Diag_From_BMS message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} Diag_From_BMS;

typedef char struct_size_test[sizeof(Diag_From_BMS) == 8? 1: -1];

typedef struct {
// BSC6VAL2 message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} BSC6VAL2;

typedef char struct_size_test[sizeof(BSC6VAL2) == 8? 1: -1];

typedef struct {
// BSC6VAL1 message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} BSC6VAL1;

typedef char struct_size_test[sizeof(BSC6VAL1) == 8? 1: -1];

