#ifndef gcan_TX_HANDLERS_H
#define gcan_TX_HANDLERS_H

#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "IfxMultican.h"

extern void data_collect_EMS_VCU_03(struct can_message_s* tx_mess);
extern void data_collect_EMS_VCU_02(struct can_message_s* tx_mess);
extern void data_collect_EMS_VCU_01(struct can_message_s* tx_mess);
#endif
