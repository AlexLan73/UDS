#ifndef COMMUNICATION_CONTROL_PRIVATE_H
#define COMMUNICATION_CONTROL_PRIVATE_H

#include "communication_control.h"
//#include "IfxCan_regdef.h"

#define CCPR 0x68 //Communication control positive response

#define CC_LEN_WITHOUT_NIN   4
#define CC_LEN_WITH_NIN   6

//sub_function ID == control type
#define LEV_CTRLTP_ERXTX		0x00 //enableRxAndTx
#define LEV_CTRLTP_ERXDTX		0x01 //enableRxAndDisableTx
#define LEV_CTRLTP_DRXETX		0x02 //disableRxAndEnableTx
#define LEV_CTRLTP_DRXTX		0x03 //disableRxAndTx
#define LEV_CTRLTP_ERXDTXWEAI	0x04 //enableRxAndDisableTxWithEnhancedAddressInformation
#define LEV_CTRLTP_ERXTXWEAI	0x05 //enableRxAndTxWithEnhancedAddressInformation

//Communication type; @ref ISO 14229-1 2013 page 333
enum communication_messages_type_e {
	normal_cm 							= 0x1,
	network_management_cm 				= 0x2,
	normal_and_network_management_cm 	= 0x3,
};
//Node identification number
// node_id used only in sub_function 0x04 and 0x05
#define NIN_NODE_1		0x00
#define NIN_NODE_2		0x0A

static uint8 check_condition_for_communication_control(void);
//static uint8 IfxMultican_MsgObj_enable_tx_mo(void);
//static uint8 IfxMultican_MsgObj_disable_rx_mo(void);
//static uint8 IfxMultican_MsgObj_disable_tx_mo(void);
//static uint8 IfxMultican_MsgObj_disable_rx_tx_mo(void);

#endif /* COMMUNICATION_CONTROL_PRIVATE_H */
