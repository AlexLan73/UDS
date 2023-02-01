#include "can_cyclic_tx_calls_10.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
void can_cyclic_tx_calls_10(void)
{
	can_write_cyclic_frame(FRAME_EMS_VCU_03_ID, FRAME_EMS_VCU_03_MO);
	can_write_cyclic_frame(FRAME_EMS_VCU_02_ID, FRAME_EMS_VCU_02_MO);
	can_write_cyclic_frame(FRAME_EMS_VCU_01_ID, FRAME_EMS_VCU_01_MO);
	can_write_cyclic_frame(FRAME_NAMI_EMS_03_ID, FRAME_NAMI_EMS_03_MO);
}
