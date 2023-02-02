#include "j1939_tx_fsm_private.h"

static enum j1939_tx_state get_tx_j1939_state(struct j1939_tp_s* instance)
{
	if (instance->tx_fsm.current_signal != default_j1939_signal) {
		return j1939_tx_fsm_table[instance->tx_fsm.current_state][instance->tx_fsm.current_signal];
	} else {
		return TX_DEFAULT_J1939;
	}
}

static void set_tx_j1939_signal(struct j1939_tp_s* instance, enum j1939_tx_signal signal)
{
	instance->tx_fsm.new_signal = signal;
}

enum j1939_tx_state get_next_j1939_tx_step(struct j1939_tp_s* instance)
{
	return get_tx_j1939_state(instance);
}

void set_next_j1939_tx_signal(struct j1939_tp_s* instance, enum j1939_tx_signal signal)
{
	set_tx_j1939_signal(instance, signal);
}




