#include "can_cyclic_tx_calls_20.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_tx_calls_20(void)
{
	can_write_cyclic_frame(FRAME_ECU_16_ID);
	can_write_cyclic_frame(FRAME_ECU_Veh_02_ID);
}
