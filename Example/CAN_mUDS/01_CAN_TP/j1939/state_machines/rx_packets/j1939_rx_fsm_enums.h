#ifndef J1939_RX_FSM_ENUMS_H
#define J1939_RX_FSM_ENUMS_H

enum j1939_rx_state {
	RX_DEFAULT_J1939,
	RECEIVE_RTS,
	TRANSMIT_CTS,
	WAIT_CONFIRM_TRANSMIT_CTS,
	WAIT_DT,
	RECEIVE_DT,
	TIMEOUT,
	RX_ERROR,
	TRANSMIT_END_OF_MSG_ACK,
	WAIT_CONFIRM_TX_END_OF_MSG_ACK,
	UNEXP_RECEIVE_RTS,
	TX_CONN_ABORT_TIMEOUT,
	WAIT_CONFIRM_TRANSMIT_CONN_ABORT_TIMEOUT,
	TX_CONN_ABORT_RESOURCES_END,
	WAIT_CONFIRM_TRANSMIT_CONN_ABORT_RESOURCES_END,
	TRANSMIT_CONN_ABORT_SESSION_SETUP_EARLY,
	WAIT_CONFIRM_TRANSMIT_CONN_ABORT_SESSION_SETUP_EARLY,
	RX_CONN_ABORT_TIMEOUT,
	RX_CONN_ABORT_RESOURCES_END,
	RECEIVE_FIRST_BAM,
	WAIT_DATA_BAM,
	RECEIVE_DATA_BAM,
	TIMEOUT_RECEIVE_BAM,
	RX_IGNORE_J1939
};

enum j1939_rx_signal {
	rx_rts_j1939_signal,
	tx_cts_j1939_signal,
	wait_confirm_tx_cts_j1939_signal,
	tx_confirm_j1939_signal,
	wait_dt_j1939_signal,
	rx_data_j1939_signal,
	tx_end_of_msg_ack_j1939_signal,
	wait_confirm_tx_end_of_msg_ack,
	transmit_conn_abort_timeout_j1939_signal,
	wait_transmite_conn_abort_timeout_j1939_signal,
	transmit_conn_abort_resources_end_j1939_signal,
	wait_transmit_conn_abort_resources_end_j1939_signal,
	default_rx_j1939_signal,
	rx_timeout_j1939_signal,
	tx_conn_abort_setup_early_j1939_signal,
	wait_tx_conn_abort_setup_early_j1939_signal,
	rx_conn_abort_timeout_j1939_signal,
	rx_conn_abort_resources_end_j1939_signal,
	receive_first_bam_j1939_signal,
	wait_data_bam_j1939_signal,
	receive_data_bam_j1939_signal,
	timeout_receive_bam_j1939_signal,
};



#endif /* J1939_RX_FSM_ENUMS_H */
