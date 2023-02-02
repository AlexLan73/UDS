#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 NotSupported : 16;
	uint32 Reserve2 : 4;
	uint32 HardCoded : 4;
	uint32 Reserve3 : 8;
	uint32 AX : 16;
	uint32 ESP_YRS_03_RC : 4;
	uint32 AX_STAT : 4;
	uint32 ESP_YRS_03_CS : 8;
} ESP_YRS_03;

typedef char struct_size_test[sizeof(ESP_YRS_03) == 8? 1: -1];

typedef struct {
	uint32 MMotInc : 16;
	uint32 MMotRedFast : 16;
	uint32 MMotRed : 16;
	uint32 BMsr : 1;
	uint32 BAsc : 1;
	uint32 reserved_0 : 2;
	uint32 ESP_01_RC : 4;
	uint32 ESP_01_CS : 8;
} ESP_01;

typedef char struct_size_test[sizeof(ESP_01) == 8? 1: -1];

typedef struct {
	uint32 WheelSpeed_RL : 16;
	uint32 WheelSpeed_RR : 16;
	uint32 WheelSpeed_ValueError_RL : 1;
	uint32 WheelDirectionInfo_RL : 2;
	uint32 reserved_0 : 5;
	uint32 WheelSpeed_ValueError_RR : 1;
	uint32 WheelDirectionInfo_RR : 2;
	uint32 reserved_1 : 9;
	uint32 ESP_03_RC : 4;
	uint32 ESP_03_CS : 8;
} ESP_03;

typedef char struct_size_test[sizeof(ESP_03) == 8? 1: -1];

typedef struct {
	uint32 WheelSpeed_FL : 16;
	uint32 WheelSpeed_FR : 16;
	uint32 WheelSpeed_ValueError_FL : 1;
	uint32 WheelDirectionInfo_FL : 2;
	uint32 reserved_0 : 5;
	uint32 WheelSpeed_ValueError_FR : 1;
	uint32 WheelDirectionInfo_FR : 2;
	uint32 reserved_1 : 9;
	uint32 ESP_02_RC : 4;
	uint32 ESP_02_CS : 8;
} ESP_02;

typedef char struct_size_test[sizeof(ESP_02) == 8? 1: -1];

typedef struct {
	uint32 VehicleSpeed : 16;
	uint32 VehicleSpeed_ValueError : 1;
	uint32 ESP_Lamp : 1;
	uint32 AVH_Active : 1;
	uint32 Bls_Out : 1;
	uint32 Bla : 1;
	uint32 ABS_Lamp : 1;
	uint32 EBD_Lamp : 1;
	uint32 TCS_Fault : 1;
	uint32 CDPDecelActive : 1;
	uint32 BLS_Fault : 1;
	uint32 CtlActiveAbs : 1;
	uint32 CtlActiveEbd : 1;
	uint32 CtlActiveTcs : 1;
	uint32 CtlActiveVdc : 1;
	uint32 Passive_Lamp : 1;
	uint32 Gearshift_Inhibit : 1;
	uint32 HDC_Activated : 1;
	uint32 CtlActiveHDC : 1;
	uint32 HDC_rejected : 1;
	uint32 EmergencyBraking : 1;
	uint32 RequestToEPB : 2;
	uint32 CDPDecelAvailable : 1;
	uint32 PEBWarningLampReq : 1;
	uint32 HDC_SpeedLimit : 8;
	uint32 CddActive_2 : 1;
	uint32 reserved_0 : 3;
	uint32 ESP_04_RC : 4;
	uint32 ESP_04_CS : 8;
} ESP_04;

typedef char struct_size_test[sizeof(ESP_04) == 8? 1: -1];

