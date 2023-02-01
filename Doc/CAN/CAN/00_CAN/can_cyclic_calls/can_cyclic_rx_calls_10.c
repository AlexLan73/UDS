#include "can_cyclic_rx_calls_10.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
void can_cyclic_rx_calls_10(void)
{
	can_read_cyclic_frame(FRAME_VCU_EMS_05_ID, FRAME_VCU_EMS_05_MO);
	can_read_cyclic_frame(FRAME_VCU_EMS_04_ID, FRAME_VCU_EMS_04_MO);
	can_read_cyclic_frame(FRAME_VCU_EMS_03_ID, FRAME_VCU_EMS_03_MO);
	can_read_cyclic_frame(FRAME_VCU_EMS_02_ID, FRAME_VCU_EMS_02_MO);
	can_read_cyclic_frame(FRAME_VCU_EMS_01_ID, FRAME_VCU_EMS_01_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_05_ID, FRAME_Hyb_Sys_INV_05_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_01_ID, FRAME_Hyb_Sys_INV_01_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_DC_01_ID, FRAME_Hyb_Sys_DC_01_MO);
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_01_ID, FRAME_Hyb_Sys_BMS_01_MO);
}
