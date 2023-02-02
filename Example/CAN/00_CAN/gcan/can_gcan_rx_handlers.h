#ifndef gcan_RX_HANDLERS_H
#define gcan_RX_HANDLERS_H

#include "Platform_Types.h"
#include "can_initialization.h"
#include "can_frame_structure.h"

extern void VCU_EMS_05_handler(struct can_message_s* rx_msg);
extern void VCU_EMS_04_handler(struct can_message_s* rx_msg);
extern void VCU_EMS_03_handler(struct can_message_s* rx_msg);
extern void VCU_EMS_02_handler(struct can_message_s* rx_msg);
extern void VCU_EMS_01_handler(struct can_message_s* rx_msg);
#endif
