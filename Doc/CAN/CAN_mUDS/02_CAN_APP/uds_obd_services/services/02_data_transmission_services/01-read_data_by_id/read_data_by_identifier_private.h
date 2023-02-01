#ifndef READ_DATA_BY_IDENTIFIER_PRIVATE_H
#define READ_DATA_BY_IDENTIFIER_PRIVATE_H

#include "read_data_by_identifier.h"
//#include "UDS_0x22_SCU.h"

#define MIN_RDBI_LEN 						3
#define MAX_RDBI_LEN						41	//maximum length is 1 byte (SI) + 2*n bytes (DID(s))
#define TOTAL_RESPONSE_LENGTH_EXCEEDED		20

#define UDS_VERSION							0xFF00
#define SYSTEM_NAME_ENGINE_TYPE				0xF197


#define ACCESS 0
#define NUM_ID_FOR_DS		 2
#define NUM_ID_FOR_PRGS		 2
#define NUM_ID_FOR_EXTDS	 2

//data record
#define DREC_DATA_1
#define DREC_DATA_2

//extern struct permission_t permission;

static boolean access_granted(uint16 parameter_id);
static uint16 add_pid_info_to_response_message(struct iso15765_tp_s* response_message, uint16  temp_index, uint16 parameter_id);


#endif /* READ_DATA_BY_IDENTIFIER_PRIVATE_H */
