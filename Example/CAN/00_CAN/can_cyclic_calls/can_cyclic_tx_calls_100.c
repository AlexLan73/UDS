#include "can_cyclic_tx_calls_100.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
void can_cyclic_tx_calls_100(void)
{
	can_write_cyclic_frame(FRAME_NAMI_EMS_04_ID, FRAME_NAMI_EMS_04_MO);
	can_write_cyclic_frame(FRAME_NAMI_EMS_02_ID, FRAME_NAMI_EMS_02_MO);
	can_write_cyclic_frame(FRAME_NAMI_EMS_01_ID, FRAME_NAMI_EMS_01_MO);
	can_write_cyclic_frame(FRAME_BSC6LIM_ID, FRAME_BSC6LIM_MO);
	can_write_cyclic_frame(FRAME_BSC6COM_ID, FRAME_BSC6COM_MO);
}
