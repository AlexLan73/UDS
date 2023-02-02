#ifndef ADD_DATA_TO_BUFFER_H
#define ADD_DATA_TO_BUFFER_H

#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"

uint16 add_data_to_buffer(enum iso_15765_frame_type frame_type, uint8* from, uint8* to, uint8 size, uint16 position);

#endif
