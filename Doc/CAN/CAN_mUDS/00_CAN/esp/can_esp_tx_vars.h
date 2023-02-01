#include "Platform_Types.h"
#include "IfxMultican.h"

typedef struct {
	uint32 MotPedPos_Driver : 8;
	uint32 reserved_0 : 8;
	uint32 M_DriverRequest : 16;
	uint32 nICEngineSpeed2 : 16;
	uint32 DrvUnitType : 3;
	uint32 ExtSpeedControlActive : 1;
	uint32 ECU_15_RC : 4;
	uint32 ECU_15_CS : 8;
} ECU_15;

typedef char struct_size_test[sizeof(ECU_15) == 8? 1: -1];

