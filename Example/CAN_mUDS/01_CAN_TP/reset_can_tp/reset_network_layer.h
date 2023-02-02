#ifndef RESET_NETWORK_LAYER_H
#define RESET_NETWORK_LAYER_H

#include "can_tp_iso15765_parameters.h"

//extern void default_network_layer(struct iso15765_tp_s* instance_p);

extern void set_can_tp_rx_default_network_layer(struct iso15765_tp_s* rx_instance_p);
extern void set_can_tp_tx_default_network_layer(struct iso15765_tp_s* tx_instance_p);


#endif /* RESET_NETWORK_LAYER_H */
