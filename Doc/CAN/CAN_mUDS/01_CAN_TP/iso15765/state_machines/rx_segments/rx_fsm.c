#include "rx_fsm_private.h"

/*--------------------------------------------------------------------------------------------------*/
/*------------------------RX FINIT-STATE MACHINE----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
static enum network_rx_state get_rx_mf_state(struct iso15765_tp_s* instance)
{
	if (instance->rx_fsm.current_rx_signal != rx_default_signal) {
		return fsm_rx_fm_table[instance->rx_fsm.current_rx_state][instance->rx_fsm.current_rx_signal];
	} else {
		return RX_DEFAULT_STATE;
	}
}

static void set_rx_signal(struct iso15765_tp_s* instance, enum network_rx_signal signal)
{
	instance->rx_fsm.new_rx_signal = signal;
}


/*--------------------------------------------------------------------------------------------------*/
enum network_rx_state get_next_rx_step(struct iso15765_tp_s* instance)
{
	return get_rx_mf_state(instance);
}

void set_next_rx_signal(struct iso15765_tp_s* instance, enum network_rx_signal signal)
{
	set_rx_signal(instance, signal);
}
