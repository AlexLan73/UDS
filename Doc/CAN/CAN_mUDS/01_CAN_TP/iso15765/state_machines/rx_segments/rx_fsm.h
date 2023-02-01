#ifndef RX_FSM_H
#define RX_FSM_H

#include "Platform_Types.h"
#include "rx_fsm_enums.h"
#include "can_tp_iso15765_parameters.h"

enum network_rx_state get_next_rx_step(struct iso15765_tp_s* instance);
void set_next_rx_signal(struct iso15765_tp_s* instance, enum network_rx_signal signal);

#endif /* RX_FSM_H */
