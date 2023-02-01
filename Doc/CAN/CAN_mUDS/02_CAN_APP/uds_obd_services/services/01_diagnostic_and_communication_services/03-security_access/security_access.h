#ifndef SECURITY_ACCESS_H
#define SECURITY_ACCESS_H

#include "Platform_Types.h"
#include "uds_parameters.h"

extern uint8 security_access_counter; //TODO set to zero when a reset is performed
extern uint8 security_access(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message);

#endif /* SECURITY_ACCESS_H */
