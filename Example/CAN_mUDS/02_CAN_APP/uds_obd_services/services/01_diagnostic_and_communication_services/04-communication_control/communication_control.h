#ifndef COMMUNICATION_CONTROL_H
#define COMMUNICATION_CONTROL_H

#include "Platform_Types.h"
#include "uds_parameters.h"

extern uint8 communication_control(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message);

#endif /* COMMUNICATION_CONTROL_H */
