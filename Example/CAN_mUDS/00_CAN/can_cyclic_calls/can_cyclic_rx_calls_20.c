#include "can_cyclic_rx_calls_20.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_20(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_03_ID);
	can_read_cyclic_frame(FRAME_CDA_11_ID);
	can_read_cyclic_frame(FRAME_EPB_Status_ID);
	can_read_cyclic_frame(FRAME_ESP_04_ID);
}
