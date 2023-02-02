#ifndef J1939_RX_FSM_H
#define J1939_RX_FSM_H

#include "Platform_Types.h"
#include "j1939_rx_fsm_enums.h"
#include "can_tp_j1939_parameters.h"
//comment
/*!
\brief short description

full description

\param[in]
*/
enum j1939_rx_state get_next_j1939_rx_step(struct j1939_tp_s* instance);

/*!
\brief short description

full description

\param[in]
*/
void set_next_j1939_rx_signal(struct j1939_tp_s* instance, enum j1939_rx_signal signal);

#endif /*J1939_RX_FSM_H*/
