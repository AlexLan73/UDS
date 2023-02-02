#ifndef READ_UDS_REQUEST_H
#define READ_UDS_REQUEST_H

#include "Platform_Types.h"
#include "uds_parameters.h"
#include "request_current_powertrain_diagnostic_data.h"
#include "request_vehicle_information.h"

extern void read_obd_message(struct iso15765_tp_s* request_message);

#endif /* READ_UDS_REQUEST_H */
