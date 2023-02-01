#include "can_cyclic_rx_calls_100.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
void can_cyclic_rx_calls_100(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_03_ID, FRAME_Hyb_Sys_INV_03_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_02_ID, FRAME_Hyb_Sys_INV_02_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_DC_02_ID, FRAME_Hyb_Sys_DC_02_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_02_ID, FRAME_Hyb_Sys_BMS_02_MO);
	can_read_cyclic_frame(FRAME_BSC6VAL2_ID, FRAME_BSC6VAL2_MO);
	can_read_cyclic_frame(FRAME_BSC6VAL1_ID, FRAME_BSC6VAL1_MO);
}
