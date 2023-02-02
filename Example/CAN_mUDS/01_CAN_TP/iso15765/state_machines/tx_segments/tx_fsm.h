#ifndef TX_FSM_H
#define TX_FSM_H

#include "Platform_Types.h"
#include "tx_fsm_enums.h"
#include "can_tp_iso15765_parameters.h"

enum network_tx_state get_next_tx_step(struct iso15765_tp_s* instance);
void set_next_tx_signal(struct iso15765_tp_s* instance, enum network_tx_signal signal);

#endif /* TX_FSM_H */
