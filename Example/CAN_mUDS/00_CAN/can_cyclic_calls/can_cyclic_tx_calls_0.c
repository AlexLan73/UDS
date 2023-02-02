#include "can_cyclic_tx_calls_0.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_tx_calls_0(void)
{
	can_write_cyclic_frame(FRAME_Diag_To_INC_ID);
	can_write_cyclic_frame(FRAME_Diag_To_BMS_ID);
	can_write_cyclic_frame(FRAME_Diag_Functional_ID);
	can_write_cyclic_frame(FRAME_Diag_From_ECU_ID);
}
