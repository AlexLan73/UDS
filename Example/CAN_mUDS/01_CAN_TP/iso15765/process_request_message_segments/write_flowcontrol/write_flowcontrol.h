#ifndef WRITE_FLOWCONTROL_H
#define WRITE_FLOWCONTROL_H

#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"

void write_flow_control_frame(struct iso15765_tp_s* instance, uint8 flow_control_status);
#endif /* WRITE_FLOWCONTROL_H */
