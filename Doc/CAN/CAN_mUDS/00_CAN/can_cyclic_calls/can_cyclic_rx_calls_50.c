#include "can_cyclic_rx_calls_50.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_50(void)
{
	can_read_cyclic_frame(FRAME_HVC_HV_Status_Msg_ID);
	can_read_cyclic_frame(FRAME_BCM_VEH_STATE_ID);
}
