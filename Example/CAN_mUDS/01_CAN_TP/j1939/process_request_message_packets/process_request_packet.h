#ifndef PROCESS_J1939_REQUEST_H
#define PROCESS_J1939_REQUEST_H

#include "Platform_Types.h"
#include "can_tp_j1939_parameters.h"

/*
\brief function change fsm state

full description

\param[in] -
*/
void can_tp_j1939_receive_message_packet(uint32 can_id, struct j1939_tp_instance_s* can_tp_instance_array);

#endif /* PROCESS_J1939_REQUEST_H */
