#include "can_tp_j1939_initialization.h"

static void can_j1939_server_parameter_init(void);
static void can_tp_j1939_instances_init(void);

void can_tp_j1939_initialization(void)
{
	can_j1939_server_parameter_init();
	can_tp_j1939_instances_init();
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


static void can_j1939_server_parameter_init(void)
{
	set_j1939_parameter();
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

static void can_tp_j1939_instances_init(void)
{

}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void set_j1939_parameter(void)
{

}
