#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 VCU_EMS_05_Checksum : 8;
	uint32 VCU_EMS_05_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 VCU_VehicleSpeed : 16;
	uint32 VCU_MinEmotFast : 10;
	uint32 VCU_MaxEmotFast : 10;
	uint32 reserved_1 : 12;
} VCU_EMS_05;

typedef char struct_size_test[sizeof(VCU_EMS_05) == 8? 1: -1];

typedef struct {
	uint32 VCU_EMS_04_Checksum : 8;
	uint32 VCU_EMS_04_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 VCU_IncTemp : 8;
	uint32 VCU_EMTemp : 8;
	uint32 VCU_AmbTemp : 8;
	uint32 VCU_CooLvLow : 1;
	uint32 reserved_1 : 23;
} VCU_EMS_04;

typedef char struct_size_test[sizeof(VCU_EMS_04) == 8? 1: -1];

typedef struct {
	uint32 VCU_EMS_03_Checksum : 8;
	uint32 VCU_EMS_03_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 VCU_EMSActualCurrent : 12;
	uint32 VCU_EMSActualVoltage : 12;
	uint32 VCU_EMSActualTorque : 12;
	uint32 reserved_1 : 12;
} VCU_EMS_03;

typedef char struct_size_test[sizeof(VCU_EMS_03) == 8? 1: -1];

typedef struct {
	uint32 VCU_EMS_02_Checksum : 8;
	uint32 VCU_EMS_02_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 VCU_MaxEmotSlow : 10;
	uint32 VCU_MinEmotSlow : 10;
	uint32 VCU_InvTrqMax : 10;
	uint32 VCU_InvTrqMin : 10;
	uint32 reserved_1 : 8;
} VCU_EMS_02;

typedef char struct_size_test[sizeof(VCU_EMS_02) == 8? 1: -1];

typedef struct {
	uint32 VCU_EMS_01_Checksum : 8;
	uint32 VCU_EMS_01_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 VCU_EMSPwrReq : 12;
	uint32 VCU_MaxPwrAvl : 12;
	uint32 VCU_FuelLvl : 9;
	uint32 VCU_VehRdy : 1;
	uint32 VCU_EMSStpCmd : 1;
	uint32 VCU_EMSRunCmd : 1;
	uint32 VCU_VcuRdy : 1;
	uint32 reserved_1 : 11;
} VCU_EMS_01;

typedef char struct_size_test[sizeof(VCU_EMS_01) == 8? 1: -1];

