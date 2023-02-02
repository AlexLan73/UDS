#ifndef RX_FSM_ENUMS_H
#define RX_FSM_ENUMS_H


enum network_rx_state
{
	RX_DEFAULT_STATE 			= 0,
	SF_IND_STATE				= 1,
	FF_IND_STATE 				= 2,
	FC_WRITE_OVRFLW_STATE 		= 3,
	FC_WRITE_CTS_STATE 			= 4,
	FC_WAIT_CONF_OVRFLW_STATE 	= 5,
	FC_WAIT_CONF_CTS_STATE 		= 6,
	CF_WAIT_IND_STATE 			= 7,
	CF_IND_STATE 				= 8,
	UNEXP_SF_IND_STATE			= 9,
	UNEXP_FF_IND_STATE			= 10,
	RX_ERROR_STATE				= 11,
	RX_TIMEOUT_STATE			= 12,
	RX_SUCCESS_STATE			= 13,
	RX_IGNORE					= 14
};

enum network_rx_signal
{
	sf_ind_signal = 0,
	ff_ind_signal,
	fc_write_cts_signal,
	fc_write_ovrflw_signal,
	fc_wait_conf_signal,
	fc_conf_signal,
	cf_ind_signal,
	cf_wait_ind_signal,
	rx_error_signal,
	rx_timeout_signal,
	rx_default_signal,
	rx_success_signal
};


#endif /* RX_FSM_ENUMS_H */
