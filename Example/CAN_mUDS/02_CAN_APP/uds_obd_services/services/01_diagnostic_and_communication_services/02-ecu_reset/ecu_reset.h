#ifndef ECU_RESET_H
#define ECU_RESET_H

#include "Platform_Types.h"
#include "uds_parameters.h"
#include "process_response_segment.h"

extern uint8 ecu_reset(
		struct iso15765_tp_s* response_message,
		struct iso15765_tp_s*  request_message
		);



#endif /* ECU_RESET_H */
