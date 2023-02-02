#include "j1939_rx_fsm_private.h"

static enum j1939_rx_state get_rx_j1939_state(struct j1939_tp_s* instance)
{
	if (instance->rx_fsm.current_signal != default_rx_j1939_signal) {
		return j1939_rx_fsm_table[instance->rx_fsm.current_state][instance->rx_fsm.current_signal];
	} else {
		return RX_DEFAULT_J1939;
	}
}

static void set_rx_j1939_signal(struct j1939_tp_s* instance, enum j1939_rx_signal signal)
{
	instance->rx_fsm.new_signal = signal;
}

enum j1939_rx_state get_next_j1939_rx_step(struct j1939_tp_s* instance)
{
	return get_rx_j1939_state(instance);
}

void set_next_j1939_rx_signal(struct j1939_tp_s* instance, enum j1939_rx_signal signal)
{
	set_rx_j1939_signal(instance, signal);
}

