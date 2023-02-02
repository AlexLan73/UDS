#include "uds_timers.h"
#include "uds_parameters.h"
#include "process_response_segment.h"

extern uint16 get_current_time(void);


//------------------------------------------------------------------------------------------------------------
// P2
//------------------------------------------------------------------------------------------------------------
struct uds_timer_s uds_p2_server_timer = {0, 0, 0}; // max_value parameter is described on @page 11, ISO 14229-2, 2013

void start_uds_p_2_server_time_measurement(void)
{
	uds_p2_server_timer.enable = 1;
	uds_p2_server_timer.first_measurement = get_current_time();
}


//TODO It depends on when this function is called (Will occur an error if this function is called before the start_uds_time_measurement() function)
void track_uds_p_2_server_time(void)
{
	uint16 current_uds_time = get_current_time();
	uint16 elapsed_time = current_uds_time - uds_p2_server_timer.first_measurement;

	if ( elapsed_time < uds_p2_server_timer.value ) {
		//all ok//
	} else {
		uds_default_session_configuration();
		uds_p2_server_timer.enable = 0;
	}
}
//------------------------------------------------------------------------------------------------------------
// S3
//------------------------------------------------------------------------------------------------------------
struct uds_timer_s uds_s3_server_timer = {0, 0, 0}; // max_value parameter is described on @page 17, ISO 14229-2, 2013

void start_uds_s_3_server_time_measurement(void)
{
	uds_s3_server_timer.enable = 1;
	uds_s3_server_timer.first_measurement = get_current_time();
}


//TODO It depends on when this function is called (Will occur an error if this function is called before calling the start_uds_time_measurement() function)
void track_uds_s_3_server_time(void)
{
	uint16 current_uds_time = get_current_time();
	uint16 elapsed_time = current_uds_time - uds_s3_server_timer.first_measurement;

	if ( elapsed_time < uds_s3_server_timer.value ) {
		//all ok//
	} else {
		uds_default_session_configuration();
		uds_s3_server_timer.enable = 0;
	}
}

