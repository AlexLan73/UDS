#include "can_cyclic_rx_calls_10.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_10(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_05_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_01_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_DC_01_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_01_ID);
	can_read_cyclic_frame(FRAME_TCU_R932_4_ID);
	can_read_cyclic_frame(FRAME_TCU_R932_3_ID);
	can_read_cyclic_frame(FRAME_TCU_R932_2_ID);
	can_read_cyclic_frame(FRAME_TCU_R932_1_ID);
	can_read_cyclic_frame(FRAME_SAS_Standard_ID);
	can_read_cyclic_frame(FRAME_BCM_Powertrain_ID);
	can_read_cyclic_frame(FRAME_ESP_YRS_03_ID);
	can_read_cyclic_frame(FRAME_ESP_01_ID);
	can_read_cyclic_frame(FRAME_ESP_03_ID);
	can_read_cyclic_frame(FRAME_ESP_02_ID);
}
