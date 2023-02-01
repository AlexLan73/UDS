#include "routine_conrtol_private.h"

uint8 routine_control(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	return NRC_SNS;
}
