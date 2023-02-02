#ifndef hv_TX_HANDLERS_H
#define hv_TX_HANDLERS_H

#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "IfxMultican.h"

extern void data_collect_NAMI_EMS_04(struct can_message_s* tx_mess);
extern void data_collect_NAMI_EMS_03(struct can_message_s* tx_mess);
extern void data_collect_NAMI_EMS_02(struct can_message_s* tx_mess);
extern void data_collect_NAMI_EMS_01(struct can_message_s* tx_mess);
extern void data_collect_Diag_To_INC(struct can_message_s* tx_mess);
extern void data_collect_Diag_To_BMS(struct can_message_s* tx_mess);
extern void data_collect_Diag_Functional(struct can_message_s* tx_mess);
extern void data_collect_BSC6LIM(struct can_message_s* tx_mess);
extern void data_collect_BSC6COM(struct can_message_s* tx_mess);
#endif
