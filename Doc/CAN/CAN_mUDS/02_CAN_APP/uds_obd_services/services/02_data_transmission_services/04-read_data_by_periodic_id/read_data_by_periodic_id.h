#ifndef READ_DATA_BY_PERIODIC_ID_H
#define READ_DATA_BY_PERIODIC_ID_H

#include "Platform_Types.h"
#include "uds_parameters.h"
#include "bitwise_array.h"

#define DS_MASK 0x0001 //default session mask
#define PS_MASK 0x0002 //programming session mask
#define ES_MASK 0x0004 //extended session mask
#define SS_MASK 0x0008 //s session mask

#define SEC_LEV_0_MASK 0x0001 //security access level 0 mask
#define SEC_LEV_1_MASK 0x0002 //security access level 1 mask
#define SEC_LEV_2_MASK 0x0004 //security access level 2 mask

struct periodic_data_id_descriptor {
	uint8 session_mode:		4; //0001 - default, 0010 - in programming, 0100 - extended, 1000 - SS??
	uint8 security_mode:	4; //0001 - security access level 1, 0010 - security access level 2...

	//uint8* pointer_to_parameter[7]; // uds mes: byte[0] - did, byte[1-7] - data
	uint8* pointer_to_parameter[6]; // uds mes: byte[0] - positive resp code -> 6A, byte[1] - did, byte[2-7] - data
};

struct rate_list {
	uint32 row[NUMBER_OF_BYTES_IN_ARRAY]; // 8 * 32 bit = 256 bit <=> 256 pdid //TODO bind with
	uint8 current_pdid_to_send;
};

struct scheduler_config {
	uint16 elapsed_time;
	uint8 parameter_counter;
	uint8 number_of_sent_parameters;
	uint8 number_of_requested_parameters;
	uint16 full_circle_time;
	uint8 max_number_of_parameters_per_full_circle_time;
};

extern void read_data_by_periodic_id(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message);
extern void read_data_by_periodic_id_service_initialization(uint8 raster);
extern void read_data_by_periodic_id_scheduler(void);

extern boolean sending_periodic_data_enable;
extern const struct periodic_data_id_descriptor periodic_did[];
extern struct rate_list slow_rate_list, medium_rate_list, fast_rate_list;
extern struct scheduler_config slow_rate_scheduler, medium_rate_scheduler, fast_rate_scheduler;

#endif /* READ_DATA_BY_PERIODIC_ID_H */
