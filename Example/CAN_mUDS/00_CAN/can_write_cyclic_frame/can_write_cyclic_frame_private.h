#ifndef CAN_WRITE_CYCLIC_FRAME_PRIVATE_H
#define CAN_WRITE_CYCLIC_FRAME_PRIVATE_H
#include "can_write_cyclic_frame.h"
#include "can_frame_structure.h"
#include "can_write_frame.h"
#include "can_initialization.h"
#include <Models/Global_pars_vars/global_high_vars.h>
#include <Models/Global_pars_vars/global_low_vars.h>
#include "can_hv_tx_id.h"
#include "can_pt_tx_id.h"
#include "can_esp_tx_id.h"
#include "err_flags.h"


static struct can_message_s tx_cyclic_msg;
static void collect_info(struct can_message_s* tx_cyclic_msg);

#endif 
