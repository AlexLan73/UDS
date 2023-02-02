#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 EMS_04_Checksum : 8;
	uint32 EMS_04_AliveCounter : 4;
	uint32 EMS_MaxCurrentStaty : 10;
	uint32 EMS_MinCurrentStaty : 10;
	uint32 reserved_0 : 4;
	uint32 EMS_MaxTorque : 10;
	uint32 EMS_MinTorque : 10;
	uint32 reserved_1 : 8;
} NAMI_EMS_04;

typedef char struct_size_test[sizeof(NAMI_EMS_04) == 8? 1: -1];

typedef struct {
	uint32 EMS_03_Checksum : 8;
	uint32 EMS_03_AliveCounter : 4;
	uint32 EMS_DesEMotorTorque : 14;
	uint32 reserved_0 : 2;
	uint32 EMS_DesInvMode : 4;
	uint32 reserved_1 : 32;
} NAMI_EMS_03;

typedef char struct_size_test[sizeof(NAMI_EMS_03) == 8? 1: -1];

typedef struct {
	uint32 EMS_02_Checksum : 8;
	uint32 EMS_02_AliveCounter : 4;
	uint32 reserved_0 : 4;
	uint32 EMS_DCMinVoltageHV : 8;
	uint32 EMS_DCDesVoltageLV : 8;
	uint32 EMS_DCMinVoltageLV : 8;
	uint32 EMS_DCMaxCurrentHV : 8;
	uint32 EMS_DCDesVoltageHV : 8;
	uint32 EMS_DCMaxCurrentLV : 8;
} NAMI_EMS_02;

typedef char struct_size_test[sizeof(NAMI_EMS_02) == 8? 1: -1];

typedef struct {
	uint32 EMS_01_Checksum : 8;
	uint32 EMS_01_AliveCounter : 4;
	uint32 EMS_IsolationMeasureReq : 1;
	uint32 EMS_ExtendedLimitsReq : 1;
	uint32 ObdDriveCycleCmplt_ISig_4 : 1;
	uint32 EMS_MonReqFastDischarge : 1;
	uint32 EMS_DesBMSMode : 3;
	uint32 EMS_DesDCMode : 3;
	uint32 ObdWarmUpCycleCmplt_ISig_4 : 1;
	uint32 reserved_0 : 9;
	uint32 reserved_1 : 32;
} NAMI_EMS_01;

typedef char struct_size_test[sizeof(NAMI_EMS_01) == 8? 1: -1];

typedef struct {
// Diag_To_INC message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} Diag_To_INC;

typedef char struct_size_test[sizeof(Diag_To_INC) == 8? 1: -1];

typedef struct {
// Diag_To_BMS message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} Diag_To_BMS;

typedef char struct_size_test[sizeof(Diag_To_BMS) == 8? 1: -1];

typedef struct {
// Diag_Functional message contains motorola byte order
	uint32 reserved_0 : 32;
	uint32 reserved_1 : 32;
} Diag_Functional;

typedef char struct_size_test[sizeof(Diag_Functional) == 8? 1: -1];

typedef struct
{
	uint32 BSC6_RUNCOMM:1;
	uint32 BSC6_BOOST:1;
	uint32 reserved_1:5;
	uint32 BSC6_EN_DEBUG_ID:1;
	uint32 BSC6_LVVOL_COMM:8;
	uint32 BSC6_HVVOL_COMM:8;
	uint32 reserved_2:8;
	uint32 reserved_3:32;

}BSC6COM;

typedef char struct_size_test[sizeof(BSC6COM) == 8? 1: -1];

typedef struct
{
	uint32 BSC6_HVVOL_LOWLIM:8;
	uint32 BSC6_LVCUR_UPLIM_BUCK:8;
	uint32 BSC6_HVCUR_UPLIM_BUCK:8;
	uint32 BSC6_LVVOL_LOWLIM:8;
	uint32 BSC6_LVCUR_UPLIM_BOOST:8;
	uint32 BSC6_HVCUR_UPLIM_BOOST:8;
	uint32 reserved_1:8;
	uint32 reserved_2:8;
}BSC6LIM;

typedef char struct_size_test[sizeof(BSC6LIM) == 8? 1: -1];
