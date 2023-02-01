#include "can_read_frame_private.h"

enum can_status_e can_read_frame(uint32 can_id, uint32 can_numofcfg, struct can_message_s* rx_msg)
{
	IfxMultican_Status status;

	rx_msg->id = 0;
	rx_msg->data.word[0] = 0;
	rx_msg->data.word[1] = 0;
	rx_msg->length = 0;

	uint8 num_of_cfg;
	num_of_cfg=can_numofcfg;
//	for ( num_of_cfg = 0; num_of_cfg < CANIF_NUMBER_OF_CANRX_IDS; num_of_cfg++ ) {
//			if (can_message_rx_config[num_of_cfg].id  == can_id)
			 {
					//rx_msg->id = can_message_rx_config[num_of_cfg].id;
					//rx_msg->length = can_message_rx_config[num_of_cfg].dlc;

					if (IfxMultican_Can_MsgObj_isRxPending(&canMsgObj[can_message_rx_config[num_of_cfg].message_object_id])) {
							status = IfxMultican_Can_MsgObj_readMessage(&canMsgObj[can_message_rx_config[num_of_cfg].message_object_id], &msg);
							if (status & IfxMultican_Status_newData) {
									rx_msg->data.word[0] = msg.data[0];
									rx_msg->data.word[1] = msg.data[1];
									rx_msg->id = msg.id;              // can_message_rx_config[num_of_cfg].id;
									rx_msg->length = msg.lengthCode; //  can_message_rx_config[num_of_cfg].dlc;
									//if(rx_msg->id == can_message_rx_config[num_of_cfg].id)
									return new_data;
									//else p_0_test++;
							}
							if (status & IfxMultican_Status_receiveEmpty) {p_0_test++; return receive_empty;}

					} else {
						return receive_empty;
					}
			}
//	}
	return wrong_param;
}
