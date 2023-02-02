#ifndef SECURITY_ACCESS_PRIVATE_H
#define SECURITY_ACCESS_PRIVATE_H

#include "security_access.h"
#include "calculate_key_for_scu.h"

#define ER_RDS_LENGTH 			0x02
#define ER_SK_LENGTH 			0x06
#define MAX_SECURITY_COUNTER 	0x05

#define LEV_SAT_RSD_00 			0x01 //requestSeed 0x01 - 0x7D
#define LEV_SAT_SK_00 			0x02 //sendKey 0x02 - 0x7E

#define LEV_SAT_RSD_01 			0x03
#define LEV_SAT_SK_01			0x04

#define LEV_SAT_RSD_03 			0x05
#define LEV_SAT_SK_03			0x06

struct security_access_flags_s
{
	uint8 seed_0_is_requested:1;
	uint8 seed_1_is_requested:1;
	uint8 key_is_valid:  1;
};

uint8 security_access_counter = 0;

static struct security_access_flags_s security_access_flag = {0,0,0};

static uint32 generate_seed_for_uds_security_level(void);

#endif /* SECURITY_ACCESS_PRIVATE_H */
