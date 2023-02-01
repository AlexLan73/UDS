#ifndef CLEAR_DTC_INFORMATION_PRIVATE_H
#define CLEAR_DTC_INFORMATION_PRIVATE_H

#include "clear_dtc_information.h"
//#include "global_low_vars.h"
//#include "global_high_vars.h"

#define MESSAGE_LENGTH_CDTCI	4

#define CDTCI 			0x14 // service id
#define CDTCIPR 		0x54 // positive response code

union id_of_group_of_dtc_u {
	struct group_of_dtc_s {
		uint8 low;
		uint8 middle;
		uint8 high;
	}B;
	uint32 U;
};

static void delete_group_of_dtc(union id_of_group_of_dtc_u group_id);

#endif /* CLEAR_DTC_INFORMATION_PRIVATE_H */
