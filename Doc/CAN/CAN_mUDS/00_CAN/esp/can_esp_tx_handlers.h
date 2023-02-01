#ifndef esp_TX_HANDLERS_H
#define esp_TX_HANDLERS_H

#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "IfxMultican.h"

extern void data_collect_ECU_15(struct can_message_s* tx_mess);
#endif
