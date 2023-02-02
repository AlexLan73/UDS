#include "reset_network_layer.h"

#include "tx_fsm.h"
#include "rx_fsm.h"
#include "tp_timers.h"
#include "process_request_message_segments.h"

void set_can_tp_rx_default_network_layer(struct iso15765_tp_s* rx_instance_p)
{
	stop_tp_timer(rx_instance_p);
	set_next_rx_signal(rx_instance_p, rx_default_signal);
	if (rx_instance_p->rx_fsm.new_rx_signal != rx_instance_p->rx_fsm.current_rx_signal) {
		enum network_rx_state new_rx_state_temp = rx_instance_p->rx_fsm.current_rx_state;
		enum network_rx_signal new_rx_signal_temp = rx_instance_p->rx_fsm.current_rx_signal;

		rx_instance_p->rx_fsm.current_rx_signal = rx_instance_p->rx_fsm.new_rx_signal;
		rx_instance_p->rx_fsm.current_rx_state = get_next_rx_step(rx_instance_p);
		if (rx_instance_p->rx_fsm.current_rx_state == RX_IGNORE) {
			rx_instance_p->rx_fsm.current_rx_state = new_rx_state_temp;
			rx_instance_p->rx_fsm.current_rx_signal = rx_instance_p->rx_fsm.new_rx_signal = new_rx_signal_temp;
		}
	}
}

void set_can_tp_tx_default_network_layer(struct iso15765_tp_s* tx_instance_p)
{
	stop_tp_timer(tx_instance_p);
	set_next_tx_signal(tx_instance_p, tx_default_signal);
	if(tx_instance_p->tx_fsm.new_tx_signal != tx_instance_p->tx_fsm.current_tx_signal) {
		enum network_tx_state new_tx_state_temp = tx_instance_p->tx_fsm.current_tx_state;
		tx_instance_p->tx_fsm.current_tx_signal = tx_instance_p->tx_fsm.new_tx_signal;
		tx_instance_p->tx_fsm.current_tx_state = get_next_tx_step(tx_instance_p);
		if(tx_instance_p->tx_fsm.current_tx_state == TX_IGNORE) {
			tx_instance_p->tx_fsm.current_tx_state = new_tx_state_temp;
		}
	}
}



