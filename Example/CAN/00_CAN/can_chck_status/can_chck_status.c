#include "can_chck_status_private.h"

enum can_status_e can_frame_chck_status(uint32 can_id)
{
	uint8 message_configuration_number;

	for ( message_configuration_number = 0; message_configuration_number < CANIF_NUMBER_OF_CANRX_IDS; message_configuration_number++ ) {
		if (can_message_rx_config[message_configuration_number].id  == can_id) {
			if (IfxMultican_Can_MsgObj_isRxPending(&canMsgObj[can_message_rx_config[message_configuration_number].message_object_id])) {
				return new_data;
			} else {
				return receive_empty;
			}
		}
	}

	for ( message_configuration_number = 0; message_configuration_number < CANIF_NUMBER_OF_CANTX_IDS; message_configuration_number++ ) {
		if (can_message_tx_config[message_configuration_number].id  == can_id) {
			if (IfxMultican_Can_MsgObj_isTransmitRequested(&canMsgObj[can_message_tx_config[message_configuration_number].message_object_id])) {
				return not_sent_busy;
			} else {
				return success;
			}
		}
	}
	return wrong_param;
}


