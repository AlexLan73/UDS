#ifndef CAN_READ_FRAME_H
#define CAN_READ_FRAME_H
#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "can_frame_status.h"
extern enum can_status_e can_read_frame(uint32 can_id, uint32 can_numofcfg, struct can_message_s* rx_msg);
# endif
