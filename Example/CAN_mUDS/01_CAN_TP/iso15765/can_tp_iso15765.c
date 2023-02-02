#include "process_request_message_segments.h"
#include "process_response_segment.h"
#include "can_tp_iso15765_parameters.h"
#include "can_initialization.h"
#include "tx_fsm.h"
#include "rx_fsm.h"

struct can_tp_iso15765_parameter_s 	server_parameter[ISO15765_MAX_NUM];
struct can_tp_iso15765_parameter_s 	client_parameter[ISO15765_MAX_NUM];

struct can_tp_iso15765_instance_s can_tp_iso15765_request_instance[ISO15765_MAX_NUM];	//TODO BUFFER * 4095 kByte
struct can_tp_iso15765_instance_s can_tp_iso15765_response_instance[ISO15765_MAX_NUM];	//TODO BUFFER * 4095 kByte
//--------------------------------------------------------------------------------
//REQUEST
void can_request_handlers(void)
{
	can_tp_read_segment(server_parameter[0].server_address);
	can_tp_read_segment(server_parameter[0].broadcast_address);
}


//--------------------------------------------------------------------------------
//RESPONSE - TODO this handler would need to be added to the fastest raster. Call time depends on the parameter STmin
void can_response_handlers(void)
{
	can_tp_iso15765_send_message_segments();
}

