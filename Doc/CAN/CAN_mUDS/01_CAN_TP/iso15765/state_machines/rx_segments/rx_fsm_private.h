#ifndef RX_FSM_PRIVATE_H
#define RX_FSM_PRIVATE_H

#include "rx_fsm.h"

static enum network_rx_state fsm_rx_fm_table[/*current_state*/][/*current_signal*/rx_success_signal+1] = {
				                     /*sf_ind_signal      ff_ind_signal, fc_write_cts_signal, fc_write_ovrflw_signal,       fc_wait_conf_signal,    fc_conf_signal, cf_ind_signal, cf_wait_ind_signal, rx_error_signal, rx_timeout_signal, rx_default_signal, rx_success_signal*/
/* RX_DEFAULT_STATE */ {               SF_IND_STATE,       FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,         RX_IGNORE,        RX_IGNORE },
/* SF_IND_STATE */ {             UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,  RX_ERROR_STATE,         RX_IGNORE,         RX_IGNORE, RX_SUCCESS_STATE },
/* FF_IND_STATE */ {             UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,  FC_WRITE_CTS_STATE,  FC_WRITE_OVRFLW_STATE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,  RX_ERROR_STATE,         RX_IGNORE,         RX_IGNORE,        RX_IGNORE },
/* FC_WRITE_OVRFLW_STATE */ {    UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE, FC_WAIT_CONF_OVRFLW_STATE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,         RX_IGNORE,        RX_IGNORE },
/* FC_WRITE_CTS_STATE */ {       UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,    FC_WAIT_CONF_CTS_STATE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,         RX_IGNORE,        RX_IGNORE },
/* FC_WAIT_CONF_OVRFLW_STATE */ {UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,    RX_ERROR_STATE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,  RX_TIMEOUT_STATE,         RX_IGNORE,        RX_IGNORE },
/* FC_WAIT_CONF_CTS_STATE */ {   UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE, CF_WAIT_IND_STATE,  CF_IND_STATE,          RX_IGNORE,       RX_IGNORE,  RX_TIMEOUT_STATE,         RX_IGNORE, RX_SUCCESS_STATE },
/* CF_WAIT_IND_STATE */ {        UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,  CF_IND_STATE,          RX_IGNORE,       RX_IGNORE,  RX_TIMEOUT_STATE,         RX_IGNORE,        RX_IGNORE },
/* CF_IND_STATE */ {             UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,  FC_WRITE_CTS_STATE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,  CF_WAIT_IND_STATE,  RX_ERROR_STATE,         RX_IGNORE,         RX_IGNORE, RX_SUCCESS_STATE },
/* UNEXP_SF_IND_STATE */ {             SF_IND_STATE,       FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,         RX_IGNORE, RX_SUCCESS_STATE },
/* UNEXP_FF_IND_STATE */ {       UNEXP_SF_IND_STATE, UNEXP_FF_IND_STATE,  FC_WRITE_CTS_STATE,  FC_WRITE_OVRFLW_STATE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,         RX_IGNORE,        RX_IGNORE },
/* RX_ERROR_STATE */ {                 SF_IND_STATE,       FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,  RX_DEFAULT_STATE,        RX_IGNORE },
/* RX_TIMEOUT_STATE */ {               SF_IND_STATE,       FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,         RX_IGNORE,  RX_DEFAULT_STATE,        RX_IGNORE },
/* RX_SUCCESS_STATE */ {               SF_IND_STATE,       FF_IND_STATE,           RX_IGNORE,              RX_IGNORE,                 RX_IGNORE,         RX_IGNORE,     RX_IGNORE,          RX_IGNORE,       RX_IGNORE,  		RX_IGNORE,  RX_DEFAULT_STATE,        RX_IGNORE }
};

//enum network_rx_state current_rx_state = RX_DEFAULT_STATE;
//enum network_rx_signal current_rx_signal = rx_default_signal;
//enum network_rx_signal new_rx_signal = rx_default_signal;

static enum network_rx_state get_rx_mf_state(struct iso15765_tp_s* instance);/*mf - multiframe*/
static void set_rx_signal(struct iso15765_tp_s* instance, enum network_rx_signal signal);

#endif /* RX_FSM_PRIVATE_H */
