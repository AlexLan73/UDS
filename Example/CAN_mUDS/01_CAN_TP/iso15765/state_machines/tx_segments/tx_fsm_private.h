#ifndef TX_FSM_PRIVATE_H
#define TX_FSM_PRIVATE_H

#include "tx_fsm.h"

//enum network_tx_states current_tx_state = DEFAULT_TX_STATE;
//enum network_tx_signals current_tx_signal = tx_default_signal;
//enum network_tx_signals new_tx_signal = tx_default_signal;

static uint16 fsm_tx_table[/*current_state*/][/*current_signal*/tx_success_signal+1] = {
																										            																																														/* current_state    |||  */
/* current_signal -> */ /*  		    |ff_request_signal|ff_wait_confirm__signal|ff_confirm_signal|fc_indication_signal|fc_ind_wait_signal|	 cf_req_without_fc_signal| cf_wait_conf_without_fc_signal|cf_req_with_fc_signal   | cf_wait_conf_with_fc_signal  |	  error_signal|     timeout_signal|   default_signal|sf_request_signal|sf_wait_conf_signal|tx_success_signal   */	/*     				vvv  */
/*DEFAULT_TX_STATE*/					{ FF_REQUEST_STATE,		         TX_IGNORE,	       TX_IGNORE,		    TX_IGNORE,	       TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			 TX_IGNORE, DEFAULT_TX_STATE, SF_REQUEST_STATE,		     TX_IGNORE, 		TX_IGNORE}, 		/*DEFAULT_STATE*/
/*SF_REQUEST_STATE*/					{	 TX_IGNORE,		             TX_IGNORE,	   	   TX_IGNORE,		    TX_IGNORE,	       TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE, SF_WAIT_CONF_STATE,		   TX_SUCCESS}, 		/*SF_REQUEST_STATE*/
/*SF_WAIT_CONF_STATE*/					{ FF_REQUEST_STATE,		         TX_IGNORE,	       TX_IGNORE,		    TX_IGNORE,	       TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE, SF_REQUEST_STATE,			 TX_IGNORE,		   TX_SUCCESS},		/*SF_WAIT_CONF_STATE*/
/*FF_REQUEST_STATE*/					{	 TX_IGNORE,     FF_WAIT_CONFIRM__STATE,	       TX_IGNORE,		    TX_IGNORE,	       TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*FF_REQUEST_STATE*/
/*FF_WAIT_CONFIRM__STATE*/				{	 TX_IGNORE,		             TX_IGNORE,    FC_WAIT_STATE, FC_INDICATION_STATE,	   	   TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*FF_WAIT_CONFIRM__STATE*/
/*FC_WAIT_STATE*/			    		{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,     FC_INDICATION_STATE,	   	   TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*FC_WAIT_STATE*/
/*FC_INDICATION_STATE*/			    	{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,             FC_WAIT_STATE, CF_REQUEST_WITHOUT_FC_STATE,						TX_IGNORE,CF_REQUEST_WITH_FC_STATE,			TX_IGNORE,     			TX_ERROR_STATE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE,		   TX_SUCCESS}, 		/*FC_INDICATION_STATE*/
/*CF_REQUEST_WITH_FC_STATE*/			{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,	               TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE, CF_WAIT_CONFIRM_WITH_FC_STATE,	     TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*CF_REQUEST_WITH_FC_STATE*/
/*CF_WAIT_CONFIRM_WITH_FC_STATE*/		{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,     FC_INDICATION_STATE,     FC_WAIT_STATE,					TX_IGNORE,						TX_IGNORE,CF_REQUEST_WITH_FC_STATE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE,	       TX_SUCCESS}, 		/*CF_WAIT_CONFIRM_WITH_FC_STATE*/
/*CF_REQUEST_WITHOUT_FC_STATE*/			{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,	   			   TX_IGNORE,					TX_IGNORE,  CF_WAIT_CONF_WITHOUT_FC_STATE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*CF_REQUEST_WITHOUT_FC_STATE*/
/*CF_WAIT_CONFIRM_WITHOUT_FC_STATE*/    {	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,	   			   TX_IGNORE, CF_REQUEST_WITHOUT_FC_STATE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE,		   TX_SUCCESS}, 		/*CF_WAIT_CONF_WITHOUT_FC_STATE*/
/*ERROR_STATE*/							{ DEFAULT_TX_STATE,	      DEFAULT_TX_STATE,	   TX_IGNORE,		TX_IGNORE,	   			   TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}, 		/*ERROR_STATE*/
/*TX_SUCCESS*/							{ FF_REQUEST_STATE,			     TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,	   			   TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			TX_TIMEOUT, DEFAULT_TX_STATE, SF_REQUEST_STATE,			 TX_IGNORE, 		TX_IGNORE},		/*TX_SUCCESS*/
/*TX_TIMEOUT*/							{	 TX_IGNORE,		             TX_IGNORE,	   TX_IGNORE,		TX_IGNORE,	   			   TX_IGNORE,					TX_IGNORE,						TX_IGNORE,		 		 TX_IGNORE,			TX_IGNORE,	    			 TX_IGNORE,			 TX_IGNORE, DEFAULT_TX_STATE,	     TX_IGNORE,			 TX_IGNORE, 		TX_IGNORE}		/*TX_TIMEOUT*/
};

static enum network_tx_state get_tx_state(struct iso15765_tp_s* instance);
static void set_tx_signal(struct iso15765_tp_s* instance, enum network_tx_signal signal);

#endif /* TX_FSM_PRIVATE_H */
