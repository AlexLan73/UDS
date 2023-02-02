#ifndef READ_FIRSTFRAME_PRIVATE_H
#define READ_FIRSTFRAME_PRIVATE_H

#include "read_firstframe.h"
#include "rx_fsm.h"
#include "add_data_to_buffer.h"
#include "process_request_message_segments.h"
#include "reset_network_layer.h"

static uint16 determine_uds_segmented_frame_length(uint8* first_two_bytes_in_frame);

#endif /* READ_FIRSTFRAME_PRIVATE_H */
