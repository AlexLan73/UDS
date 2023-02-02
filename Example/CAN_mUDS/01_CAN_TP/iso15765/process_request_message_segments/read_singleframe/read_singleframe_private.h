#ifndef READ_SINGLEFRAME_PRIVATE
#define READ_SINGLEFRAME_PRIVATE

#include "read_singleframe.h"

#include "rx_fsm.h"
#include "add_data_to_buffer.h"
#include "reset_network_layer.h"

static uint8 determine_uds_unsegmented_frame_length(uint8 first_byte_in_frame);

#endif /* READ_SINGLEFRAME_PRIVATE */
