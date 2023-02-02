#include "can_write_frame_private.h"
extern 	uint8 message_configuration_number_tx;


enum can_status_e can_write_frame(struct can_message_s msg)
{
	if (msg.length == 0) { return wrong_param; }

	uint8 num_of_cfg;

	tx_mess.id = msg.id;
	tx_mess.data[0] = msg.data.word[0];
	tx_mess.data[1] = msg.data.word[1];
	tx_mess.lengthCode = msg.length;

	//search MO ID in array CanIf_TxPdus[] for message_handler
	//for ( num_of_cfg = 0; num_of_cfg < CANIF_NUMBER_OF_CANTX_IDS; num_of_cfg++ )
	  {
//			if (can_message_tx_config[num_of_cfg].id  == tx_mess.id)
			{ num_of_cfg = message_configuration_number_tx;
							if(IfxMultican_Can_MsgObj_sendMessage(&canMsgObj[can_message_tx_config[num_of_cfg].message_object_id], &tx_mess) == IfxMultican_Status_notSentBusy)
							{
							if (!IfxMultican_Can_MsgObj_isTxPending(&canMsgObj[can_message_tx_config[num_of_cfg].message_object_id])) {
									return not_sent_busy;
							} else
							{
									IfxMultican_Can_MsgObj_clearTxPending(&canMsgObj[can_message_tx_config[num_of_cfg].message_object_id]);
									return success;
							}
					}
//					break;
			}
	}
	return wrong_param;
}


