#include "write_to_uds_buffer_from_matlab.h"

void write_fixdt_8_1_to_uds_buffer_from_matlab(unsigned char data)
{
 	write_1byte_to_uds_buffer_from_matlab(data);
}
void write_fixdt_8_b40_to_uds_buffer_from_matlab(unsigned char data)
{
 	write_1byte_to_uds_buffer_from_matlab(data);
}
void write_fixdt_8_4_to_uds_buffer_from_matlab(unsigned char data)
{
 	write_1byte_to_uds_buffer_from_matlab(data);
}
void write_fixdt_16_01_to_uds_buffer_from_matlab(unsigned short data)
{
 	write_short_to_uds_buffer_from_matlab(data);
}


void write_short_to_uds_buffer_from_matlab(unsigned short data)
{
	//motorola order!!!
	uint8 nextbyte;
	nextbyte = (uint8)(data>>8);
	write_1byte_to_uds_buffer_from_matlab(nextbyte);
	nextbyte = (uint8)(data & 0xFF);
	write_1byte_to_uds_buffer_from_matlab(nextbyte);
	
}

void write_3bytes_to_uds_buffer_from_matlab(unsigned char data,unsigned char data1,unsigned char data2)
{
	write_1byte_to_uds_buffer_from_matlab(data);
	write_1byte_to_uds_buffer_from_matlab(data1);
	write_1byte_to_uds_buffer_from_matlab(data2);
}



