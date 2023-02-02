#ifndef CAN_INITIALIZATION_H
#define CAN_INITIALIZATION_H
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"

#define CAN_MAX_CONTROLLERS (4)
#define CANIF_NUMBER_OF_CANRX_IDS (39)
#define CANIF_NUMBER_OF_CANTX_IDS (25)



enum {
	PT,
	ESP,
	CCPCAN,
	HV
};

typedef struct {
    uint8   controllerID;
    uint8   isEnabled;
    uint16  tSeg1;
    uint16  tSeg2;
    uint16  sjw;//(re)synchronization jump width
    uint32  baudrate;
    IfxMultican_Txd_Out *setTxPin;
    IfxMultican_Rxd_In  *setRxPin;
} Can_ControllerSettingsType;

struct can_message_config_s {
    uint32	      						id;             //Identifier
    IfxMultican_DataLengthCode 			dlc;               //Data Length
	uint8         						node_number;        //external standalone hardware device. Node
	uint8         						message_object_id;       //CAN hardware transmit handle
	uint16								cycle_time;
}/*can_message_config*/;

extern IfxMultican_Can_MsgObj canMsgObj[256];

extern const struct can_message_config_s can_message_tx_config[];
extern const struct can_message_config_s  can_message_rx_config[];

extern void can_initialize(void);
#endif
