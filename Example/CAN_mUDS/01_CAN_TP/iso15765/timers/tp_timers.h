#ifndef TIMERS_H
#define TIMERS_H

#include "tp_timers_enums.h"
#include "can_tp_iso15765_parameters.h"

#define TIME_T unsigned short
#define TIMER_STATE_T int
#define TIMER_SIGNAL_T unsigned char
/*
#define MAX_TIME_A_SENDER	1000	//As
#define MAX_TIME_B_SENDER	1000	//Bs
#define MAX_TIME_C_SENDER	1000

#define MAX_TIME_A_RECEIVER	1000	//Ar
#define MAX_TIME_B_RECEIVER	1000
#define MAX_TIME_C_RECEIVER	1000

#define MIN_TIME_ST		5

#define N_0X78_MAX 		5000

*/
//extern enum tp_timer_state current_tp_timer_state;
//extern enum tp_timer_state new_tp_timer_state;
//
//extern enum tp_timer_signal current_tp_timer_signal;
//extern enum tp_timer_signal new_tp_timer_signal;

void track_tp_time(struct iso15765_tp_s* instance_p);

void start_rx_timer_segmented(struct iso15765_tp_s* instance_p);
void start_rx_timer_unsegmented( void );
void stop_rx_timer_segmented(struct iso15765_tp_s* instance_p);
void stop_rx_timer_unsegmented(struct iso15765_tp_s* instance_p);

void start_tx_timer_segmented(struct iso15765_tp_s* instance_p);
void start_tx_timer_unsegmented(struct iso15765_tp_s* instance_p);
void stop_tx_timer_segmented(struct iso15765_tp_s* instance_p);
void stop_tx_timer_unsegmented(struct iso15765_tp_s* instance_p);

TIME_T get_tp_current_time(void);

void start_tp_timer(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer);
void change_tp_timer_to(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer);
void reset_tp_timer(struct iso15765_tp_s* instance_p);
void stop_tp_timer(struct iso15765_tp_s* instance_p);

#endif
