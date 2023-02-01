#ifndef CAN_TP_ISO15765_INITIALIZATION_H
#define CAN_TP_ISO15765_INITIALIZATION_H


#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"


enum can_tp_parameter
{
	BLOCK_SIZE = 0xE1,
	SEPARATION_TIME = 0xE2,
	WFT_MAX = 0xE3,
	API_VERSION = 0xE4,
	PADDING_VALUE = 0xE5,

	J1939_PRIORITY = 0xE6, //send message format j1939

	AS_TIMEOUT = 0xE7,
	BS_TIMEOUT = 0xE8,
	CS_TIMEOUT = 0xE9,
	AR_TIMEOUT = 0xEA,
	BR_TIMEOUT = 0xEB,
	CR_TIMEOUT = 0xEC,

	SERVER_ADDRESS = 0xED,
	CLIENT_ADDRESS = 0xEE,
	BROADCAST_ADDRESS = 0xEF,
};

void can_tp_iso15765_initialization(void);
enum iso15765_result set_iso15765_parameter(struct can_tp_iso15765_parameter_s* parameter_struct_p, enum can_tp_parameter parameter_name, unsigned int value);
void mapping_between_iso15765_addresses(uint32 source_address, uint32 destination_address, struct iso15765_tp_s* transport_layer_instance_p);

#endif /* CAN_TP_ISO15765_INITIALIZATION_H */
