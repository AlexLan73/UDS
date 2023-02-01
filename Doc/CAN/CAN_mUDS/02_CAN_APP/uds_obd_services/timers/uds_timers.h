#ifndef UDS_TIMERS_H
#define UDS_TIMERS_H

#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"

struct uds_timer_s {
	uint8 enable;
	uint16 first_measurement;
	uint16 value;
};

extern struct uds_timer_s uds_p2_server_timer;
extern struct uds_timer_s uds_s3_server_timer;

void track_uds_p_2_server_time(void); //P2 need for client initialization and learn server features??
void track_uds_s_3_server_time(void);

void start_uds_p_2_server_time_measurement(void);
void start_uds_s_3_server_time_measurement(void);

#endif /* UDS_TIMERS_H */
