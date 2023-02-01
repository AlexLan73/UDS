#include "can_cyclic_rx_calls_0.h"
#include <Multican/Can/IfxMultican_Can.h>
#include "IfxMultican_PinMap.h"
#include "can_hv_tx_id.h"
#include "can_hv_rx_id.h"
#include "can_pt_tx_id.h"
#include "can_pt_rx_id.h"
#include "can_esp_tx_id.h"
#include "can_esp_rx_id.h"
void can_cyclic_rx_calls_0(void)
{
	can_read_cyclic_frame(FRAME_Diag_From_INC_ID);
	can_read_cyclic_frame(FRAME_Diag_From_BMS_ID);
	can_read_cyclic_frame(FRAME_Diag_To_ECU_ID);
	can_read_cyclic_frame(FRAME_VAU_EMS_Hash_Immo_RESP_ID);
	can_read_cyclic_frame(FRAME_Diag_Functional_FromPT_ID);
}
