#ifndef READ_DTC_INFORMATION_H
#define READ_DTC_INFORMATION_H

#include "Platform_Types.h"
#include "uds_parameters.h"

extern uint8 read_dtc_information(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message);

#endif /* READ_DTC_INFORMATION_H */
