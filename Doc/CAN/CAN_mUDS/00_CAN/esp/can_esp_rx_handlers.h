#ifndef esp_RX_HANDLERS_H
#define esp_RX_HANDLERS_H

#include "Platform_Types.h"
#include "can_initialization.h"
#include "can_frame_structure.h"

extern void ESP_YRS_03_handler(struct can_message_s* rx_msg);
extern void ESP_01_handler(struct can_message_s* rx_msg);
extern void ESP_03_handler(struct can_message_s* rx_msg);
extern void ESP_02_handler(struct can_message_s* rx_msg);
extern void ESP_04_handler(struct can_message_s* rx_msg);
#endif
