#ifndef hv_RX_HANDLERS_H
#define hv_RX_HANDLERS_H

#include "Platform_Types.h"
#include "can_initialization.h"
#include "can_frame_structure.h"

extern void Hyb_Sys_INV_05_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_INV_04_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_INV_03_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_INV_02_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_INV_01_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_DC_02_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_DC_01_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_BMS_04_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_BMS_03_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_BMS_02_handler(struct can_message_s* rx_msg);
extern void Hyb_Sys_BMS_01_handler(struct can_message_s* rx_msg);
extern void Diag_From_INC_handler(struct can_message_s* rx_msg);
extern void Diag_From_BMS_handler(struct can_message_s* rx_msg);
extern void BSC6VAL2_handler(struct can_message_s* rx_msg);
extern void BSC6VAL1_handler(struct can_message_s* rx_msg);
#endif
