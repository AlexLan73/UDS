#ifndef CAN_TP_J1939_H
#define CAN_TP_J1939_H

#define NUMBER_OF_J1939_BUFFERS       	5
#define BUFFER_SIZE             		1785
#define NUMBER_J1939_OF_LAYERS			3

#define SERVER_ADDRESS 0x01
#define GLOBAL_ADDESS  0xFF

#include "Platform_Types.h"
#include "j1939_rx_fsm.h"
#include "j1939_tx_fsm.h"

enum j1939_message_type {
	unknown_message_j1939 = 0,
	diagnostic_j1939,
	remote_diagnostic_j1939,
	request_transmission_j1939,
	idle_j1939,
	indication_j1939,
	confirmation_j1939
};

enum can_id_type
{
	ID_CAN_11BIT = 0x01,
	ID_CAN_29BIT = 0x02
};

enum addressing_format {
	unknown_addressing_format = 0xFF,
	none_addressing_format = 0x00,
	normal_addressing_format = 0x01,
	fixed_normal_addressing_format = 0x02,
	extended_addressing_format = 0x03,
	mixed_addressing_format = 0x04,
	enhansed_addressing_format = 0x05,
};

enum buffer_e {
	BUFFER_NUMBER_ONE   = 0,
	BUFFER_NUMBER_TWO   = 1,
	BUFFER_NUMBER_THREE = 2,
	BUFFER_NUMBER_FOUR  = 3,
	BUFFER_NUMBER_FIVE  = 4,
};

enum j1939_layer_e {
	DATA_LAYER			= 0,
	NETWORK_LAYER		= 1,
	APPLICATION_LAYER	= 2,
};

enum packet_type_e {//TODO DETERMINE TYPE
	UNKNOWN_PACKET_TYPE = 0,
	DT_PACKET_TYPE = 235, // DT - data: PGN 60160 == 0xEB00
	CM_PACKET_TYPE  = 236 // CM - connection menagments: PGN 60416 == 0xEC00
};

enum control_type_e {
	UNKNOWN_CONTROL_TYPE = 0,
	RTS_CONTROL_TYPE = 16,
	CTS_CONTROL_TYPE = 17,
	END_OF_MSG_ACK_CONTROL_TYPE = 19,
	CONN_ABORT_CONTROL_TYPE = 255,
	BAM_CONTROL_TYPE = 32
};

struct can_msg_s {
    unsigned int		id;
    unsigned char		lengthCode;
    union data_u {
	    unsigned int	word[2];
	    unsigned char	byte[8];
    }data;
};

struct j1939_rx_fsm_s {
	enum j1939_rx_state current_state;
	enum j1939_rx_signal current_signal;
	enum j1939_rx_signal new_signal;
};

struct j1939_tx_fsm_s {
	enum j1939_tx_state current_state;
	enum j1939_tx_signal current_signal;
	enum j1939_tx_signal new_signal;
};

//TODO do condition compiler for big-endian machines

//                      __________________________________
//j1939 pdu frame ->   |  P  | EDP | DP |  PF  |  PS | SA |
//       29bit         |28-26|   25|  24| 23-16| 15-8| 7-0|

struct j1939_s {
	union pdu_u {
		unsigned int pdu;
		struct j1939_pdu_s {
			unsigned int source_address:          8;
			unsigned int pdu_specific:            8; //todo need to change to destination_address?
			unsigned int pdu_format:              8; ///< indicates frame type(e.g. request, acknowlegement, command etc.)
			unsigned int data_page:               1;
			unsigned int extended_data_page:      1;
			unsigned int priority:                3;

			unsigned int reserved:                3;
		}pdu_field;
	}j1939;

	struct service_data_s {
		uint8  		data[BUFFER_SIZE];
	}j1939_service;

        //parameters for iso 15765
//	enum address_type					target_address_type;
//	uint8  								remote_address;
	enum can_id_type  					id_type;
	enum j1939_message_type  			message_type[NUMBER_J1939_OF_LAYERS];
	enum addressing_format				format_type;
//	uint16 								length;
//	enum iso15765_result				result[NUMBER_OF_LAYERS];
};

struct j1939_tp_s {
	struct can_msg_s		can_frame; //for check status, need have frame in structure

	struct j1939_s 			pdu;
	struct j1939_rx_fsm_s 	rx_fsm;
	struct j1939_tx_fsm_s 	tx_fsm;
//	struct j1939_tp_timer_s timer;

	uint16 					number_of_unprocessed_bytes;
	uint8 					sequence_number_counter;
	uint16					handled_messages_counter;
	uint8 					wait_frame_counter;

};

struct j1939_tp_instance_s {
	struct j1939_tp_s			can_tp;
	boolean 					is_free;
};

extern struct j1939_tp_instance_s can_tp_j1939_request_instances_array[NUMBER_OF_J1939_BUFFERS];

#endif /* CAN_TP_J1939_H */
