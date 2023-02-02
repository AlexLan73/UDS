#include "tx_fsm_private.h"

static enum network_tx_state get_tx_state(struct iso15765_tp_s* instance)
{
	if (instance->tx_fsm.current_tx_signal != tx_default_signal) {
		return fsm_tx_table[instance->tx_fsm.current_tx_state][instance->tx_fsm.current_tx_signal];
	} else {
		return DEFAULT_TX_STATE;
	}
}

static void set_tx_signal(struct iso15765_tp_s* instance, enum network_tx_signal signal)
{
	instance->tx_fsm.new_tx_signal = signal;
}


enum network_tx_state get_next_tx_step(struct iso15765_tp_s* instance)
{
	return get_tx_state(instance);
}

void set_next_tx_signal(struct iso15765_tp_s* instance,enum network_tx_signal signal)
{
	set_tx_signal(instance, signal);
}

