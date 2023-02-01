#ifndef REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_H
#define REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_H

#include "Platform_Types.h"
#include "uds_parameters.h"

extern void request_current_powertrain_diagnostic_data(struct iso15765_tp_s* response_message, struct iso15765_tp_s* request_message);

#endif /* REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_H */
