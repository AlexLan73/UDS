#ifndef TESTER_PRESENT_H
#define TESTER_PRESENT_H

#include "uds_parameters.h"

extern uint8 tester_present(
		struct iso15765_tp_s* response_message,
		struct iso15765_tp_s*  request_message
		);

#endif /* TESTER_PRESENT_H */
