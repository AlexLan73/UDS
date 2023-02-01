#ifndef pt_TX_HANDLERS_H
#define pt_TX_HANDLERS_H

#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "IfxMultican.h"

extern void data_collect_EMS_8(struct can_message_s* tx_mess);
extern void data_collect_EMS_7(struct can_message_s* tx_mess);
extern void data_collect_EMS_4(struct can_message_s* tx_mess);
extern void data_collect_EMS_3(struct can_message_s* tx_mess);
extern void data_collect_EMS_2(struct can_message_s* tx_mess);
extern void data_collect_EMS_1(struct can_message_s* tx_mess);
extern void data_collect_ECU_Indicators(struct can_message_s* tx_mess);
extern void data_collect_ECU_16(struct can_message_s* tx_mess);
extern void data_collect_ECU_14(struct can_message_s* tx_mess);
extern void data_collect_Diag_From_ECU(struct can_message_s* tx_mess);
extern void data_collect_EMS_HVC_Req_Msg(struct can_message_s* tx_mess);
extern void data_collect_EMS_EEM_02(struct can_message_s* tx_mess);
extern void data_collect_EMS_EEM_01(struct can_message_s* tx_mess);
extern void data_collect_ECU_Veh_02(struct can_message_s* tx_mess);
extern void data_collect_ECU_Veh(struct can_message_s* tx_mess);
#endif
