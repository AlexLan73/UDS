#ifndef UDS_OBD_INITIALIZATION_H
#define UDS_OBD_INITIALIZATION_H

#include "Platform_Types.h"
#include "uds_parameters.h"

extern void uds_initialization(void);
extern enum uds_result set_uds_parameter(enum uds_parameter parameter_name, uint16 value);

#endif /* UDS_OBD_INITIALIZATION_H*/
