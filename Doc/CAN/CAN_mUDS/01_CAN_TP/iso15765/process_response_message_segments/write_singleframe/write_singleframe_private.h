#ifndef WRITE_SINGLEFRAME_PRIVATE_H
#define WRITE_SINGLEFRAME_PRIVATE_H

#include "write_singleframe.h"

#include "can_initialization.h"
#include "tp_timers.h"
#include "tx_fsm.h"
#include "extract_data_from_buffer.h"
#include "can_write_frame.h"

static void add_sf_pdu(struct iso15765_tp_s* instance);

#endif /* WRITE_SINGLEFRAME_PRIVATE_H */
