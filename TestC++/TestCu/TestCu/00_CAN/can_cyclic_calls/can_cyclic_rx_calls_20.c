#include "can_cyclic_rx_calls_20.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
#include "../hv/can_hv_rx_id.h"
void can_cyclic_rx_calls_20(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_03_ID, FRAME_Hyb_Sys_BMS_03_MO);
}
