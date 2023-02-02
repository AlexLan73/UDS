#include "write_flowcontrol_private.h"

void write_flow_control_frame(struct iso15765_tp_s* instance, uint8 flow_control_status)
{
	instance->can_frame.id = instance->pdu.iso15765_protocol_data.source_address;
	instance->can_frame.length = 8;
	instance->can_frame.data.byte[0] = (flow_control_frame_type<<4)|(flow_control_status&0xF);
	instance->can_frame.data.byte[1] = server_parameter[0].block_size;
	instance->can_frame.data.byte[2] = server_parameter[0].separation_time;
	instance->can_frame.data.byte[3] = server_parameter[0].padding_value;
	instance->can_frame.data.byte[4] = server_parameter[0].padding_value;
	instance->can_frame.data.byte[5] = server_parameter[0].padding_value;
	instance->can_frame.data.byte[6] = server_parameter[0].padding_value;
	instance->can_frame.data.byte[7] = server_parameter[0].padding_value;

	can_write_frame(instance->can_frame);

	instance->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
	set_next_rx_signal(instance, fc_wait_conf_signal);
}
