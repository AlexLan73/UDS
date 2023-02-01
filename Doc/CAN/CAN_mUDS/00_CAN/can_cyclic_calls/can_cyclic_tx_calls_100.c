#include "can_cyclic_tx_calls_100.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_tx_calls_100(void)
{
	can_write_cyclic_frame(FRAME_NAMI_EMS_04_ID);
	can_write_cyclic_frame(FRAME_NAMI_EMS_02_ID);
	can_write_cyclic_frame(FRAME_NAMI_EMS_01_ID);
	can_write_cyclic_frame(FRAME_BSC6LIM_ID);
	can_write_cyclic_frame(FRAME_BSC6COM_ID);
	can_write_cyclic_frame(FRAME_ECU_Indicators_ID);
	can_write_cyclic_frame(FRAME_EMS_EEM_02_ID);
	can_write_cyclic_frame(FRAME_EMS_EEM_01_ID);
	can_write_cyclic_frame(FRAME_ECU_Veh_ID);
}
