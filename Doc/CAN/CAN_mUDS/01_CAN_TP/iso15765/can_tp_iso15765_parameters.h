#ifndef CAN_TP_ISO15765_PARAMETERS
#define CAN_TP_ISO15765_PARAMETERS

#include "Platform_Types.h"
#include "rx_fsm_enums.h"
#include "tx_fsm_enums.h"
#include "tp_timers_enums.h"
#include "can_frame_structure.h"
#pragma GCC optimize "O0"

#define ISO15765_MAX_NUM	1
//---------------------------------------------------------
#define NUMBER_OF_LAYERS		3
#define APPLICATION_LAYER		2
#define NETWORK_LAYER			1
#define DATA_LAYER			0
//---------------------------------------------------------

#define MAX_BLOCK_SIZE				0x00
#define CAN_TP_BUFFER_SIZE			0xFFF

//---------------------------------------------------------

#define CAN_UDS_DEF 1
#define CAN_FD_UDS_DEF 0

#define NORMAL_ADDRESSING 1
#define EXTENDED_ADDRESSING 0
#define MIXED_ADDRESSING 0

#if CAN_UDS_DEF
	#define CAN_FRAME_LENGTH 8
	#if EXTENDED_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 6
		#define FIRST_FRAME_MIN_LENGTH 	7

	#elif MIXED_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 6
		#define FIRST_FRAME_MIN_LENGTH 	7

	#elif NORMAL_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 7
		#define FIRST_FRAME_MIN_LENGTH 	8

	#endif
#else

	#define CAN_FRAME_LENGTH  12 /* Valid TX_DL value range: 12, 16, 20 , 24, 32, 48, 64;*/

	#if EXTENDED_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 9/*(CAN_LENGTH - 3)*/
		#define FIRST_FRAME_MIN_LENGTH 10/*(CAN_LENGTH - 2)*/

	#elif MIXED_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 9/*(CAN_LENGTH - 3)*/
		#define FIRST_FRAME_MIN_LENGTH 10/*(CAN_LENGTH - 2)*/

	#else NORMAL_ADDRESSING

		#define SINGLE_FRAME_MAX_LENGTH 10(CAN_LENGTH - 2)
		#define FIRST_FRAME_MIN_LENGTH 11(CAN_LENGTH - 1)

	#endif

#endif


#define FIRST_FRAME_LENGTH 			 0x06
#define CONSECUTIVE_FRAME_MAX_LENGTH 0x07

#define MAX_SEQUENCE_NUMBER 	0x0F
#define MAX_WAIT_FRAME_TRANSMISSIONS 0x04

enum iso_15765_frame_type {
	single_frame_type = 0,
	first_frame_type = 1,
	consecutive_frame_type = 2,
	flow_control_frame_type = 3,
	unknown_type = 4
};

enum flow_status {
	continue_to_send = 0,
	wait_fc,
	overflow
};

enum iso15765_message_type {
	unknown_message = 0,
	diagnostic,
	remote_diagnostic,
	request_transmission,
	idle,
	indication,
	indication_ff,
	confirmation
};

enum can_id_type
{
	ID_CAN_11BIT = 0x01,
	ID_CAN_29BIT = 0x02
};

enum address_type {
//	unknown_address_type = 0,
	physical_address_type,
	functional_address_type
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

enum iso15765_result {
	N_OK = 0x00,
	N_TIMEOUT_A = 0x01,
	N_TIMEOUT_Bs = 0x02,
	N_TIMEOUT_Br = 0x04,
	N_TIMEOUT_Cr = 0x05,
	N_TIMEOUT_Cs = 0x06,
	N_WRONG_SN = 0x07,
	N_INVALID_FS = 0x08,
	N_UNEXP_PDU = 0x09,
	N_WFT_OVRN = 0x0A,
	N_BUFFER_OVFLW = 0x0B,
	N_ERROR = 0x0C,
};

struct can_tp_max_time_value {
	uint16 a_sender;
	uint16 b_sender;
	uint16 c_sender;

	uint16 a_receiver;
	uint16 b_receiver;
	uint16 c_receiver;
};

/*
	for all can_tp instances
*/
struct can_tp_iso15765_parameter_s {
	uint16 block_size;
	uint16 wtf_max;
	uint16 separation_time;
	uint8  padding_value;
	struct can_tp_max_time_value max_time_value;

	uint32 server_address;
	uint32 client_address;
	uint32 broadcast_address;
};

struct can_tp_pdu_s {
	struct protocol_data_s {
		uint32 								source_address;	//todo fix type(need uint8) @page 13 ISO15765-2 2016
		uint32 								target_address; //todo fix type(need uint8) @page 13 ISO15765-2 2016
		enum address_type					target_address_type;
		uint8  								remote_address;
		enum can_id_type  					id_type;
		enum iso15765_message_type  		message_type[NUMBER_OF_LAYERS];
		enum addressing_format				format_type;
		uint16 								length;
		enum iso15765_result				result[NUMBER_OF_LAYERS];
	} iso15765_protocol_data;

	struct service_data_s {
		uint8  					data[CAN_TP_BUFFER_SIZE];
		uint16					buffer_idx;
	} iso15765_service_data;
};

struct can_tp_rx_fsm_s {
	enum network_rx_state  current_rx_state;// = RX_DEFAULT_STATE;
	enum network_rx_signal current_rx_signal;// = rx_default_signal;
	enum network_rx_signal new_rx_signal;// = rx_default_signal;
};

struct can_tp_tx_fsm_s {
	enum network_tx_state  current_tx_state;// = RX_DEFAULT_STATE;
	enum network_tx_signal current_tx_signal;// = rx_default_signal;
	enum network_tx_signal new_tx_signal;// = rx_default_signal;
};

struct can_tp_timer_s {
	enum tp_timer_state current_state;
	enum tp_timer_signal current_signal;
	enum tp_timer_signal new_signal;

	uint16 first_tp_time_measurement;
};

struct iso15765_tp_s {
	struct can_message_s	can_frame; //need to keep can frame in structure for status checking

	struct can_tp_pdu_s 	pdu;
	struct can_tp_rx_fsm_s 	rx_fsm;
	struct can_tp_tx_fsm_s 	tx_fsm;
	struct can_tp_timer_s 	timer;

	uint16 					number_of_unprocessed_bytes;
	uint8 					sequence_number_counter;
	uint16					handled_message_counter;
	uint8 					wait_frame_counter;
};

struct can_tp_iso15765_instance_s {
	struct iso15765_tp_s				can_tp;
	boolean 							is_free;
};


//------------------------------------------------------------------------------------

extern struct can_tp_iso15765_parameter_s 	server_parameter[ISO15765_MAX_NUM];
extern struct can_tp_iso15765_parameter_s 	client_parameter[ISO15765_MAX_NUM];

extern struct can_tp_iso15765_instance_s can_tp_iso15765_request_instance[ISO15765_MAX_NUM];	//TODO BUFFER * 4095 kByte
extern struct can_tp_iso15765_instance_s can_tp_iso15765_response_instance[ISO15765_MAX_NUM];	//TODO BUFFER * 4095 kByte

extern void can_request_handlers(void);
extern void can_response_handlers(void);

#endif /* CAN_TP_ISO15765_PARAMETERS */
