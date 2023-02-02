#ifndef EXTRACT_DATA_FROM_BUFFER_H
#define EXTRACT_DATA_FROM_BUFFER_H

#include "can_tp_iso15765_parameters.h"
#include "Platform_Types.h"

uint16 extract_data_from_buffer(enum iso_15765_frame_type frame_type, uint8* from, uint8* to, uint8 size, uint16 position);

#endif
