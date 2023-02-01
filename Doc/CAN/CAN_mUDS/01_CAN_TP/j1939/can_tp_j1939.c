#include "can_tp_j1939_parameters.h"
#include "can_initialization.h"
#include "process_request_packet.h"


struct j1939_tp_instance_s can_tp_j1939_request_instances_array[NUMBER_OF_J1939_BUFFERS];

//--------------------------------------------------------------------------------

void can_j1939_request_handlers(void)
{
//	can_tp_j1939_receive_message_packet(TP_CM_CAN_ID, can_tp_j1939_request_instances_array);
}

void can_j1939_response_handlers(void)
{
//	handle_can_tp_j1939_response(&request_message);
}




