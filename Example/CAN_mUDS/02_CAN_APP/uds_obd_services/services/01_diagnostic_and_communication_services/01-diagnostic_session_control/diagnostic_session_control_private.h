#ifndef DIAGNOSTIC_SESSION_CONTROL_PRIVATE_H
#define DIAGNOSTIC_SESSION_CONTROL_PRIVATE_H

#include "diagnostic_session_control.h"
#include "err_flags.h"

#define VEHICLE_SPEED	TCU_R932_1_TCU_VehicleSpeedFromCAN
#define NO_MESSAGE		((rx_Err_flags*)&TCU_R932_1_Err)->B.NoMsg
#define DIAGNOSTIC_SESSION_CONTROL_LENGTH   2 // This service does not support data-parameters in the request message

static enum uds_session_type_e determine_session_type(uint8 request_message_byte);

#endif /* DIAGNOSTIC_SESSION_CONTROL_PRIVATE_H */
