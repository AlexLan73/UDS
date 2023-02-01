#ifndef TX_FSM_ENUMS_H
#define TX_FSM_ENUMS_H

enum network_tx_state
{
	DEFAULT_TX_STATE = 0,
	SF_REQUEST_STATE,
	SF_WAIT_CONF_STATE,
	FF_REQUEST_STATE,
	FF_WAIT_CONFIRM__STATE,
	FC_WAIT_STATE,
	FC_INDICATION_STATE,
	CF_REQUEST_WITH_FC_STATE,
	CF_WAIT_CONFIRM_WITH_FC_STATE,
	CF_REQUEST_WITHOUT_FC_STATE,
	CF_WAIT_CONF_WITHOUT_FC_STATE,
	TX_ERROR_STATE,
	TX_SUCCESS,
	TX_TIMEOUT,
	TX_IGNORE
};


enum network_tx_signal
{
	ff_request_signal = 0,
	ff_wait_confirm__signal,
	ff_confirm_signal,
	fc_indication_signal,
	fc_ind_wait_signal,
	/*fc_ind_overflow_signal,*/
	cf_req_without_fc_signal,
	cf_wait_conf_without_fc_signal,

	cf_req_with_fc_signal,
	cf_wait_conf_with_fc_signal,

	tx_error_signal,
	tx_timeout_signal,
	tx_default_signal,
	sf_request_signal,
	sf_wait_conf_signal,
	tx_success_signal
};



#endif /* TX_FSM_ENUMS_H */
