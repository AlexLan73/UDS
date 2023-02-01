#include "can_cyclic_rx_calls_500.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_500(void)
{
	can_read_cyclic_frame(FRAME_Hyb_Sys_INV_04_ID);
	can_read_cyclic_frame(FRAME_Hyb_Sys_BMS_04_ID);
	can_read_cyclic_frame(FRAME_CCU_MSG3_ID);
}
