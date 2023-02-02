#ifndef CAN_READ_CYCLIC_FRAME_PRIVATE_H
#define CAN_READ_CYCLIC_FRAME_PRIVATE_H
#include "can_read_cyclic_frame.h"
#include "can_read_frame.h"
#include "can_initialization.h"
#include "can_frame_status.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_rx_handlers.h"
#include "can_hv_rx_id.h"
#include "can_hv_rx_handlers.h"
#include "err_flags.h"
#include "global_high_vars.h"
#include "global_low_vars.h"





static uint16 time_out_counter[256];
static struct can_message_s rx_msg;

static void read_data(struct can_message_s* rx_msg, uint32 can_cfgnum);
static void set_no_message_flag(uint32 canId);
static void check_timeout(uint32 canId, uint16 counter_value);
#endif
