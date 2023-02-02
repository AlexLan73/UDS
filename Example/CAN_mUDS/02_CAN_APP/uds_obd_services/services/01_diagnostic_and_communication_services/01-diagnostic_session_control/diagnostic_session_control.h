#ifndef DIAGNOSTIC_SESSION_CONTROL_H
#define DIAGNOSTIC_SESSION_CONTROL_H

#include "Platform_Types.h"
#include "uds_parameters.h"
#include "process_response_segment.h"

extern uint8 diagnostic_session_control(
		struct iso15765_tp_s* response_message,
		struct iso15765_tp_s*  request_message
		);

#endif
