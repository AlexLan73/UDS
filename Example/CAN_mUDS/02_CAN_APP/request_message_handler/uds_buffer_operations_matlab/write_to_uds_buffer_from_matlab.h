#ifndef WRITE_TO_UDS_BUFFER_FROM_MATLAB_H
#define WRITE_TO_UDS_BUFFER_FROM_MATLAB_H

#include "Platform_types.h"
typedef unsigned char Fixpt_8_1;
typedef unsigned char Fixpt_8_4;
typedef unsigned char Fixpt_8_b40;
typedef unsigned short Fixpt_16_01;
        
extern void write_1byte_to_uds_buffer_from_matlab(unsigned char data);
extern void write_short_to_uds_buffer_from_matlab(unsigned short data);
extern void write_3bytes_to_uds_buffer_from_matlab(unsigned char data,unsigned char data1,unsigned char data2);

extern void write_fixdt_8_1_to_uds_buffer_from_matlab(unsigned char data);
extern void write_fixpt_8_4_to_uds_buffer_from_matlab(unsigned char data);
extern void write_fixpt_8_b40_to_uds_buffer_from_matlab(unsigned char data);
extern void write_fixdt_16_01_to_uds_buffer_from_matlab(unsigned short data);



#endif /* WRITE_TO_UDS_BUFFER_FROM_MATLAB_H */
