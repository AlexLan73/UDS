#ifndef TIMERS_PRIVATE_H
#define TIMERS_PRIVATE_H

#include "tp_timers.h"
#include "tx_fsm.h"
#include "rx_fsm.h"

uint16 current_tp_time = 0;

//enum tp_timer_state current_tp_timer_state = DEFAULT_STATE;
//enum tp_timer_state new_tp_timer_state;
//
//enum tp_timer_signal current_tp_timer_signal = DEFAULT_TP_TIMER_SIGNAL;
//enum tp_timer_signal new_tp_timer_signal;

static uint16 fsm_tp_timer_table[/*current_state*/][/*current_signal*/(DEFAULT_TP_TIMER_SIGNAL+1)] = {
																																				/* current_state    |||  */
/* current_signal -> *//*|	As	|	Ar	|	Bs	|	Br	|	Cs	|	Cr	|	Def    */	/*     				vvv  */
/*DEFAULT_STATE*/	{ AS_TIMER_STATE,TP_TIMER_IGNORE,TP_TIMER_IGNORE, BR_TIMER_STATE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,  DEFAULT_STATE   }, 		//DEFAULT_STATE
/*AS_TIMER_STATE*/	{TP_TIMER_IGNORE,TP_TIMER_IGNORE, BS_TIMER_STATE,TP_TIMER_IGNORE, CS_TIMER_STATE,TP_TIMER_IGNORE,  DEFAULT_STATE   }, 		// AS_TIMER_STATE - работает таймер A sender
/*AR_TIMER_STATE*/	{TP_TIMER_IGNORE,TP_TIMER_IGNORE,TP_TIMER_IGNORE, BR_TIMER_STATE,TP_TIMER_IGNORE, CR_TIMER_STATE,  DEFAULT_STATE   }, 		// AR_TIMER_STATE - работает таймер A receiver
/*BS_TIMER_STATE*/	{TP_TIMER_IGNORE,TP_TIMER_IGNORE, BS_TIMER_STATE,TP_TIMER_IGNORE, CS_TIMER_STATE,TP_TIMER_IGNORE,  DEFAULT_STATE   }, 		// BS_TIMER_STATE - работает таймер B sender
/*BR_TIMER_STATE*/	{TP_TIMER_IGNORE, AR_TIMER_STATE,TP_TIMER_IGNORE, BR_TIMER_STATE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,  DEFAULT_STATE   }, 		// BR_TIMER_STATE - работает таймер B receiver
/*CS_TIMER_STATE*/	{ AS_TIMER_STATE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,TP_TIMER_IGNORE,  DEFAULT_STATE   }, 		// CS_TIMER_STATE - работает таймер C sender
/*CR_TIMER_STATE*/	{TP_TIMER_IGNORE,TP_TIMER_IGNORE,TP_TIMER_IGNORE, BR_TIMER_STATE,TP_TIMER_IGNORE, CR_TIMER_STATE,  DEFAULT_STATE   }, 		// CR_TIMER_STATE - работает таймер C receiver
};

static void start_tp_time_measurement(struct iso15765_tp_s* instance_p);
static void check_tp_time_measurement(struct iso15765_tp_s* instance_p);
static void reset_tp_time_measurement(struct iso15765_tp_s* instance_p);
static void stop_tp_time_measurement(struct iso15765_tp_s* instance_p);

static void set_tp_timer_signal(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer_signal);
static enum tp_timer_state get_tp_timer_state(struct iso15765_tp_s* instance_p);

extern uint16 get_current_time(void);

#endif
