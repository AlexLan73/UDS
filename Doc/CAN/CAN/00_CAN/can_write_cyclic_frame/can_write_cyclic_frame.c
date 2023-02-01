#include "can_write_cyclic_frame_private.h"
extern void (*TXcollect_infoPtr[CANIF_NUMBER_OF_CANTX_IDS])(struct can_message_s* tx_mess);

uint8 message_configuration_number_tx;
void can_write_cyclic_frame(uint32 can_id, uint32 can_cfgnum)
{

	//search MO ID in array CanIf_TxPdus[] for message_handler
	for(message_configuration_number_tx = 0; message_configuration_number_tx < CANIF_NUMBER_OF_CANTX_IDS; message_configuration_number_tx++) {
		if (can_message_tx_config[message_configuration_number_tx].id  == can_id) {

			tx_cyclic_msg.data.word[0] = 0;
			tx_cyclic_msg.data.word[1] = 0;
			tx_cyclic_msg.id = can_message_tx_config[message_configuration_number_tx].id;
			tx_cyclic_msg.length = can_message_tx_config[message_configuration_number_tx].dlc;

			collect_info(&tx_cyclic_msg);
			
			can_write_frame(tx_cyclic_msg);
			break;
		}
	}
}


static void collect_info(struct can_message_s* tx_cyclic_msg) 
{
	TXcollect_infoPtr[message_configuration_number_tx](tx_cyclic_msg);
}

