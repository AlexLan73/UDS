#include "process_request_packet.h"
#include "can_initialization.h"
#include "j1939_rx_fsm.h"

/*
\brief function change fsm state

full description

\param[in] -
*/
static struct j1939_tp_s* j1939_tp_packet_is_rx_pending(uint32 can_i, struct j1939_tp_instance_s* can_tp_instance_array);

/*
\brief function change fsm state

full description

\param[in] -
*/
static void copy_extended_can_msg(IfxMultican_Message* rxMsg, struct j1939_tp_s* can_tp_instance_p);

/*
\brief function change fsm state

full description

\param[in] -
*/
static enum packet_type_e determine_packet_type(unsigned int pdu_format);

/*
\brief function change fsm state

full description

\param[in] -
*/
static enum control_type_e determine_control_type(uint8 first_byte_in_frame);

/*
\brief function change fsm state

full description

\param[in] -
*/
static void handle_received_packet(struct j1939_tp_s* instance);

/*
\brief function change fsm state

full description

\param[in] -
*/
static void check_rx_j1939_signal_change(struct j1939_tp_s* instance);

static void set_data_layer_primitive(enum j1939_message_type mt, struct j1939_tp_s* instance_p);

static boolean request_message_complete(struct j1939_tp_s* instance);

static void process_received_message_packet(struct j1939_tp_s* instance);


//-------------------------------------------------------------------------------------------------------------------------------

void can_tp_j1939_receive_message_packet(uint32 can_id, struct j1939_tp_instance_s* can_tp_instance_array)
{
	struct j1939_tp_s* j1939_tp_instance = j1939_tp_packet_is_rx_pending(can_id, can_tp_instance_array);

	if (j1939_tp_instance != NULL_PTR) {
		set_data_layer_primitive(unknown_message_j1939, j1939_tp_instance);
		handle_received_packet(j1939_tp_instance);

		if (request_message_complete(j1939_tp_instance)) {
//			read_j1939_request_message();
		}
	}
}

static struct j1939_tp_s* j1939_tp_packet_is_rx_pending(uint32 can_id, struct j1939_tp_instance_s* instance_array)
{
//	IfxMultican_Message rxMsg;
//
//	switch(can_id) {
//	case TP_CM_CAN_ID:
//		if (IfxMultican_Can_MsgObj_isRxPending(&canMsgObj[TP_CM_MO_ID])) {
//			IfxMultican_Can_MsgObj_readMessage(&canMsgObj[TP_CM_MO_ID], &rxMsg);
//
//			struct j1939_tp_s* instance = NULL_PTR;
//
//			// maybe reserved can_tp_instance for received ID
//			// get empty data_unit pointer
//			uint8 i = 0;
//			for (i = 0; i < NUMBER_OF_J1939_BUFFERS; i++) {
//				if ((instance_array[i].can_tp.pdu.j1939.pdu_field.source_address) == (can_id & 0x000000FF)) {
//					instance = &instance_array[i].can_tp;
//					break;
//				}
//			}
//
//			//if not reserved
//			if (instance == NULL_PTR) {
//				//search empty instance for save
//				for (i = 0; i<NUMBER_OF_J1939_BUFFERS; i++) {
//					if (instance_array[i].is_free) {
//						instance_array[i].is_free = FALSE;
//						instance = &instance_array[i].can_tp;
//						break;
//					}
//				}
//			}
//
//
//			if (instance == NULL_PTR) {
//				// all instances are busy
//				return NULL_PTR;
//			} else {
//				// found empty instance
//				copy_extended_can_msg(&rxMsg, instance);
//
//				instance->pdu.j1939.pdu = instance->can_frame.id;
////				instance->pdu.iso15765_protocol_data.target_address_type = physical_address_type;
//				instance->pdu.id_type = ID_CAN_29BIT;
//				instance->pdu.format_type = fixed_normal_addressing_format; //TODO check this field type. I could set wrong type
////				instance->pdu.iso15765_protocol_data.result[DATA_LAYER] = N_OK;
////
//				set_data_layer_primitive(indication_j1939, instance);
//
//				return instance;
//			}
//		} else {
//			return NULL_PTR;
//		}
//	default:
		return NULL_PTR;
//	}
}

static void handle_received_packet(struct j1939_tp_s* instance)
{
	enum packet_type_e pt = determine_packet_type(instance->pdu.j1939.pdu_field.pdu_format);

	switch (pt) {
	case DT_PACKET_TYPE:
		set_next_j1939_rx_signal(instance, rx_data_j1939_signal);
		break;
	case CM_PACKET_TYPE: {
		enum control_type_e control_type = determine_control_type(instance->pdu.j1939_service.data[0]);

		switch (control_type) {
		case RTS_CONTROL_TYPE:
			set_next_j1939_rx_signal(instance, rx_rts_j1939_signal);
			break;



			//TODO TX_FSM: server receive CTS and END_OF_MSG_ACK when it send response
		case CTS_CONTROL_TYPE:
			//set_next_j1939_rx_signal(instance,tx_cts_j1939_signal);
			break;
		case END_OF_MSG_ACK_CONTROL_TYPE:
			//set_next_j1939_rx_signal(instance,);
			break;
		case CONN_ABORT_CONTROL_TYPE:
			//set_next_j1939_rx_signal(instance,);
			break;

		case BAM_CONTROL_TYPE:
			//TODO split BAM packet in fsm
			//set_next_j1939_rx_signal(instance,);
			break;
		case UNKNOWN_CONTROL_TYPE:
		default:
			return;
		}
		break;
	}
	case UNKNOWN_PACKET_TYPE:
	default:
		return;
	}

	process_received_message_packet(instance);
}

static void process_received_message_packet(struct j1939_tp_s* instance)
{
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RECEIVE_RTS) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TRANSMIT_CTS) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_CONFIRM_TRANSMIT_CTS) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_DT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RECEIVE_DT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TIMEOUT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RX_ERROR) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TRANSMIT_END_OF_MSG_ACK) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_CONFIRM_TX_END_OF_MSG_ACK) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == UNEXP_RECEIVE_RTS) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TX_CONN_ABORT_TIMEOUT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_CONFIRM_TRANSMIT_CONN_ABORT_TIMEOUT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TX_CONN_ABORT_RESOURCES_END) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_CONFIRM_TRANSMIT_CONN_ABORT_RESOURCES_END) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TRANSMIT_CONN_ABORT_SESSION_SETUP_EARLY) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_CONFIRM_TRANSMIT_CONN_ABORT_SESSION_SETUP_EARLY) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RX_CONN_ABORT_TIMEOUT) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RX_CONN_ABORT_RESOURCES_END) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RECEIVE_FIRST_BAM) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == WAIT_DATA_BAM) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == RECEIVE_DATA_BAM) {
	}
	check_rx_j1939_signal_change(instance);
	if(instance->rx_fsm.current_state == TIMEOUT_RECEIVE_BAM) {
	}
}

static enum packet_type_e determine_packet_type(unsigned int pdu_format)
{
	switch (pdu_format) {
	case 235:
		return DT_PACKET_TYPE;
	case 236:
		return CM_PACKET_TYPE;
	default:
		return UNKNOWN_PACKET_TYPE;
	}
}

static enum control_type_e determine_control_type(uint8 first_byte_in_frame)
{
    switch(first_byte_in_frame){
    case 16:
		return RTS_CONTROL_TYPE;
    case 17:
    	return CTS_CONTROL_TYPE;
    case 19:
    	return END_OF_MSG_ACK_CONTROL_TYPE;
    case 255:
    	return CONN_ABORT_CONTROL_TYPE;
    case 32:
    	return BAM_CONTROL_TYPE;
    case 0:
    default:
    	return UNKNOWN_CONTROL_TYPE;
    }
}

static boolean request_message_complete(struct j1939_tp_s* instance)
{
	return (instance->pdu.message_type[NETWORK_LAYER] == indication_j1939)?TRUE:FALSE;
}

static void set_data_layer_primitive(enum j1939_message_type mt, struct j1939_tp_s* instance_p)
{
	instance_p->pdu.message_type[DATA_LAYER] = mt;
}

static void copy_extended_can_msg(
		IfxMultican_Message* rxMsg,
		struct j1939_tp_s* can_tp_instance_p)
{
	can_tp_instance_p->can_frame.id 			= rxMsg->id;
	can_tp_instance_p->pdu.j1939.pdu 			= rxMsg->id;

	can_tp_instance_p->can_frame.data.word[0]   = rxMsg->data[0];
	can_tp_instance_p->can_frame.data.word[1]   = rxMsg->data[1];

	can_tp_instance_p->can_frame.lengthCode 	= rxMsg->lengthCode;
}

static void check_rx_j1939_signal_change(struct j1939_tp_s* instance)
{
	if(instance->rx_fsm.new_signal != instance->rx_fsm.current_signal) {
		enum j1939_rx_state new_rx_state_temp = instance->rx_fsm.current_state;
		enum j1939_rx_signal new_rx_signal_temp = instance->rx_fsm.current_signal;

		instance->rx_fsm.current_signal = instance->rx_fsm.new_signal;
		instance->rx_fsm.current_state = get_next_j1939_rx_step(instance);
		if (instance->rx_fsm.current_state == RX_IGNORE_J1939) {
			instance->rx_fsm.current_state = new_rx_state_temp;
			instance->rx_fsm.current_signal = instance->rx_fsm.new_signal = new_rx_signal_temp;

		}
	}
}
