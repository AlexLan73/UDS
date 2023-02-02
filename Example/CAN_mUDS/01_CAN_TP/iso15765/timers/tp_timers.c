#include "tp_timers_private.h"
#pragma GCC optimize "O0"
/*
 * checks the current state of the selected timer
 */
void track_tp_time(struct iso15765_tp_s* instance_p)
{
	check_tp_time_measurement(instance_p);
}

void start_rx_timer_segmented(struct iso15765_tp_s* instance_p)
{
	change_tp_timer_to(instance_p, BR_TIMER);
}

void stop_rx_timer_segmented(struct iso15765_tp_s* instance_p)
{
	stop_tp_time_measurement(instance_p);
}

void start_rx_timer_unsegmented( void )
{
}
void stop_rx_timer_unsegmented(struct iso15765_tp_s* instance_p)
{
	stop_tp_time_measurement(instance_p);
}

void start_tx_timer_segmented(struct iso15765_tp_s* instance_p)
{
	change_tp_timer_to(instance_p, AS_TIMER);
}

void stop_tx_timer_segmented(struct iso15765_tp_s* instance_p)
{
	stop_tp_time_measurement(instance_p);
}

void start_tx_timer_unsegmented(struct iso15765_tp_s* instance_p)
{
	change_tp_timer_to(instance_p, AS_TIMER);
}

void stop_tx_timer_unsegmented(struct iso15765_tp_s* instance_p)
{
	stop_tp_time_measurement(instance_p);
}

TIME_T get_tp_current_time(void)
{
	return get_current_time();
}

/*--------------------------------------------------------*/
static void start_tp_time_measurement(struct iso15765_tp_s* instance_p)
{
	instance_p->timer.first_tp_time_measurement = get_tp_current_time();
}

static void check_tp_time_measurement(struct iso15765_tp_s* instance_p)
{
	current_tp_time = get_tp_current_time();
	uint16 elapsed_time = current_tp_time - instance_p->timer.first_tp_time_measurement;

	unsigned short timeout_value;
	enum iso15765_result result;

	switch (instance_p->timer.current_state) {
	case AS_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.a_sender;
		result = N_TIMEOUT_A;
		break;
	case AR_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.a_receiver;
		result = N_TIMEOUT_A;
		break;
	case BS_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.b_sender;
		result = N_TIMEOUT_Bs;
		break;
	case BR_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.b_receiver;
		result = N_TIMEOUT_Br;
		break;
	case CS_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.c_sender;
		result = N_TIMEOUT_Cs;
		break;
	case CR_TIMER_STATE:
		timeout_value = server_parameter[0].max_time_value.c_receiver;
		result = N_TIMEOUT_Cr;
		break;
	case TP_TIMER_IGNORE:
	case DEFAULT_STATE:
	default:
		instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
		return;
	}

	if ( elapsed_time < timeout_value ) {
		//all ok//
		instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
	} else {
		switch (instance_p->timer.current_state) {
		case AS_TIMER_STATE:
		case BS_TIMER_STATE:
		case CS_TIMER_STATE:
			set_next_tx_signal(instance_p, tx_timeout_signal); //!!!!!!!!!!TX
			instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = result;
			break;
		case AR_TIMER_STATE:
		case BR_TIMER_STATE:
		case CR_TIMER_STATE:
			set_next_rx_signal(instance_p, rx_timeout_signal); //!!!!!!!!!!!RX
			instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = result;
			break;
		case TP_TIMER_IGNORE:
		case DEFAULT_STATE:
		default:
			instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_ERROR;
			return;
		}
		//stop_tp_time_measurement();
	}
}

static void reset_tp_time_measurement(struct iso15765_tp_s* instance_p)
{
	instance_p->timer.first_tp_time_measurement = get_tp_current_time();
}

static void stop_tp_time_measurement(struct iso15765_tp_s* instance_p)
{
	change_tp_timer_to(instance_p, DEFAULT_TP_TIMER_SIGNAL);
}

//--------------------------------

void start_tp_timer(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer)
{
	set_tp_timer_signal(instance_p, tp_timer);

	if (instance_p->timer.new_signal != instance_p->timer.current_signal) {
		enum tp_timer_state old_state = instance_p->timer.current_state;
		instance_p->timer.current_signal = instance_p->timer.new_signal;
		instance_p->timer.current_state = get_tp_timer_state(instance_p);
		if (instance_p->timer.current_state == TP_TIMER_IGNORE) {
			instance_p->timer.current_state = old_state;
		}
	}
}

void change_tp_timer_to(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer)
{
	set_tp_timer_signal(instance_p, tp_timer);

	if (instance_p->timer.new_signal != instance_p->timer.current_signal) {
		enum tp_timer_state old_state = instance_p->timer.current_state;
		instance_p->timer.current_signal = instance_p->timer.new_signal;
		instance_p->timer.current_state = get_tp_timer_state(instance_p);
		if (instance_p->timer.current_state == TP_TIMER_IGNORE) {
			instance_p->timer.current_state = old_state;
		}
	}

	start_tp_time_measurement(instance_p);
}

void reset_tp_timer(struct iso15765_tp_s* instance_p)
{
	reset_tp_time_measurement(instance_p);
}

void stop_tp_timer(struct iso15765_tp_s* instance_p)
{
	set_tp_timer_signal(instance_p, DEFAULT_TP_TIMER_SIGNAL);
	instance_p->timer.current_state = get_tp_timer_state(instance_p);
}

static void set_tp_timer_signal(struct iso15765_tp_s* instance_p, enum tp_timer_signal tp_timer_signal)
{
	instance_p->timer.new_signal = tp_timer_signal;
}
/*
static TIMER_SIGNAL_T get_timer_signal( void )
{
	return current_timer_signal;
}

static void set_timer_state( int state )
{
	current_timer_state = state;
}
*/
static enum tp_timer_state get_tp_timer_state(struct iso15765_tp_s* instance_p)
{
	if (instance_p->timer.current_signal != DEFAULT_TP_TIMER_SIGNAL) {
		return fsm_tp_timer_table[instance_p->timer.current_state][instance_p->timer.current_signal];
	} else {
		return DEFAULT_STATE;
	}
}
