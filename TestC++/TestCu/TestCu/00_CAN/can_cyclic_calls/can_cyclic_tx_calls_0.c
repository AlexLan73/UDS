#include "can_cyclic_tx_calls_0.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_gcan_tx_id.h"
#include "can_gcan_rx_id.h"
#include "can_gcan_tx_handlers_private.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_hv_tx_handlers_private.h"
#include "msg2id.h"
void can_cyclic_tx_calls_0(void)
{
	can_write_cyclic_frame(FRAME_Diag_To_INC_ID, FRAME_Diag_To_INC_MO);
	can_write_cyclic_frame(FRAME_Diag_To_BMS_ID, FRAME_Diag_To_BMS_MO);
	can_write_cyclic_frame(FRAME_Diag_Functional_ID, FRAME_Diag_Functional_MO);
}
