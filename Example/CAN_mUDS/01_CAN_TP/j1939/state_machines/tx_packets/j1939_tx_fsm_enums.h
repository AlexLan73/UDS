#ifndef J1939_TX_FSM_ENUMS_H
#define J1939_TX_FSM_ENUMS_H


enum j1939_tx_state {
	TX_DEFAULT_J1939,
	TRANSMIT_RTS_J1939,
	WAIT_RTS_TRANSMIT_CONFIRM_J1939,
	WAIT_CTS_J1939,
	RECEIVE_CTS_J1939,
	TRANSMIT_DT,
	WAIT_DT_TRANSMIT_CONFIRM_J1939,
	WAIT_RX_END_OF_MSG_ACK,
	RECEIVE_END_OF_MSG_ACK,
	RECEIVE_CONN_ABORT_TIMEOUT,
	RECEIVE_CONN_ABORT_RESOURCES_END,
	TRANSMIT_CONN_ABORT_TIMEOUT,
	WAIT_CONN_ABORT_TIMEOUT_TRANSMIT_CONFIRM_J1939,
	TRANSMIT_CONN_ABORT_RESOURCES_END,
	 WAIT_CONN_ABORT_RESOURCES_END_TRANSMIT_CONFIRM_J1939,
	TRANSMIT_FIRST_BAM,
	TRANSMIT_DATA_BAM,
	WAIT_FIRST_BAM_TRANSMIT_CONFIRM_J1939,
	WAIT_DATA_BAM_TRANSMIT_CONFIRM_J1939,
	TIMEOUT_TRANSMIT_BAM,
	TX_IGNORE_J1939
};

enum j1939_tx_signal {
	transmit_rts_j1939_signal,
	wait_rts_transmit_confirm_j1939_signal,
	wait_cts_j1939_signal,
	receive_cts_j1939_signal,
	transmit_dt_j1939_signal,
	wait_dt_transmit_confirm_j1939_signal,
	wait_end_of_msg_ack_j1939_signal,
	receive_end_of_msg_ack_j1939_signal,
	receive_conn_abort_timeout_j1939_signal,
	receive_conn_abort_resources_end_j1939_signal,
	tx_conn_abort_timeout_j1939_signal,
	wait_tx_conn_abort_timeout_j1939_signal,
	tx_conn_abort_resources_end_j1939_signal,
	wait_tx_conn_abort_resources_end_j1939_signal,
	default_j1939_signal,
	transmit_first_bam_j1939_signal,
	transmit_data_bam_j1939_signal,
	wait_first_bam_transmit_confirm_j1939_signal,
	wait_data_bam_transmit_confirm_j1939_signal,
	timeout_j1939_signal
,
};


#endif /* J1939_TX_FSM_ENUMS_H */
