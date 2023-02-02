#ifndef WRITE_FIRSTFRAME_PRIVATE_H
#define WRITE_FIRSTFRAME_PRIVATE_H

#include "write_firstframe.h"

#include "tp_timers.h"
#include "tx_fsm.h"
#include "extract_data_from_buffer.h"
#include "can_write_frame.h"

//extern IfxMultican_Can_MsgObj canMsgObj[3];
static void add_ff_pdu(struct iso15765_tp_s* instance);

#endif /* WRITE_FIRSTFRAME_PRIVATE_H */
