#include "can_cyclic_rx_calls_100.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_100(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_03_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_02_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_DC_02_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_02_ID);
	can_read_cyclic_frame(FRAME_BSC6VAL2_ID);
	can_read_cyclic_frame(FRAME_BSC6VAL1_ID);
	can_read_cyclic_frame(FRAME_TCU_R932_5_ID);
	can_read_cyclic_frame(FRAME_DMS_01_ID);
	can_read_cyclic_frame(FRAME_BCM_EEM_ID);
	can_read_cyclic_frame(FRAME_ACU_01_ID);
}
