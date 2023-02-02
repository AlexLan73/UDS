#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 EMS_VCU_03_Checksum : 8;
	uint32 EMS_VCU_03_AliveCounter : 4;
	uint32 EMS_MinCurrentStatySlow : 10;
	uint32 EMS_MinCurrentStatyFast : 10;
	uint32 EMS_MaxCurrentStatySlow : 10;
	uint32 EMS_MaxCurrentStatyFast : 10;
	uint32 EMS_PowerLimit : 12;
} EMS_VCU_03;

typedef char struct_size_test[sizeof(EMS_VCU_03) == 8? 1: -1];

typedef struct {
	uint32 EMS_VCU_02_Checksum : 8;
	uint32 EMS_VCU_02_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 EMS_InstFuelCons : 8;
	uint32 EMS_EmTrqMax : 10;
	uint32 EMS_EMTrqMin : 10;
	uint32 reserved_1 : 19;
	uint32 EMS_OilPressureWarning : 1;
} EMS_VCU_02;

typedef char struct_size_test[sizeof(EMS_VCU_02) == 8? 1: -1];

typedef struct {
	uint32 EMS_VCU_01_Checksum : 8;
	uint32 EMS_VCU_01_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 EMS_FaultState : 3;
	uint32 EMS_CoengSt : 3;
	uint32 EMS_EmgcyStop : 1;
	uint32 EMS_ReadyState : 1;
	uint32 EMS_ActualPwr : 12;
	uint32 EMS_FanReq : 7;
	uint32 EMS_Tcool : 8;
	uint32 EMS_TrqReq : 12;
	uint32 reserved_1 : 1;
} EMS_VCU_01;

typedef char struct_size_test[sizeof(EMS_VCU_01) == 8? 1: -1];

