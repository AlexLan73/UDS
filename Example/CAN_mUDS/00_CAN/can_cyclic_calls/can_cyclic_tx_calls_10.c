#include "can_cyclic_tx_calls_10.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_tx_calls_10(void)
{
	can_write_cyclic_frame(FRAME_NAMI_EMS_03_ID);
	can_write_cyclic_frame(FRAME_EMS_8_ID);
	can_write_cyclic_frame(FRAME_EMS_4_ID);
	can_write_cyclic_frame(FRAME_EMS_3_ID);
	can_write_cyclic_frame(FRAME_EMS_2_ID);
	can_write_cyclic_frame(FRAME_ECU_14_ID);
	can_write_cyclic_frame(FRAME_ECU_15_ID);
}
