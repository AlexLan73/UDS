#ifndef CAN_WRITE_FRAME_H
#define CAN_WRITE_FRAME_H
#include "Platform_Types.h"
#include "can_frame_structure.h"
#include "can_frame_status.h"



extern enum can_status_e can_write_frame(struct can_message_s msg);

#endif /* CAN_WRITE_FRAME_H */
