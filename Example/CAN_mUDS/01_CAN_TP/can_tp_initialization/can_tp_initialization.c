#include "can_tp_initialization.h"


#include "can_tp_iso15765_initialization.h"
#include "can_tp_j1939_initialization.h"



void can_tp_initialization(void)
{
	can_tp_iso15765_initialization();
	can_tp_j1939_initialization();
}

