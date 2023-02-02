#include "write_to_uds_buffer_from_c.h"

uint16 write_1byte_to_uds_buffer_from_c(uint8 data, uint8* to,uint16 size, uint16* current_position)
{
	uint16 idx = 0;
	if (size > 4095) {return (*current_position);}

//	for(; idx < size;) {
		to[ (*current_position)++ ] = data;
//	}

	return (*current_position);
}
