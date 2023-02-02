#include "write_response_message.h"


void write_response_message(struct iso15765_tp_s* message)
{
	// send negative or positive response
	message->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = request_transmission;
	can_tp_write(message);
}




