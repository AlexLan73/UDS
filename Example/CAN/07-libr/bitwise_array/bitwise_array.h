#ifndef BITWISE_ARRAY_H
#define BITWISE_ARRAY_H

#include "Platform_Types.h"

typedef volatile uint32				type_of_bits_array;
typedef uint8						bitpos_t;
typedef char						bool_t;

#define NUMBER_OF_BITS_IN_ARRAY			256//(sizeof(bitwise_array)*8) 							//BITSCOUNT TODO
#define NUMBER_OF_BYTES_IN_ARRAY		8//(sizeof(bitwise_array)/sizeof(bitwise_array[0])) 	//WORDSCOUNT TODO
#define BITS_PER_BITS_ARRAY_TYPE		32//(sizeof(type_of_bits_array)*8)						//BITSPERBITS_T TODO

//#define DUMB

bool_t  GetBit(type_of_bits_array *bitwise_array, bitpos_t position);
void    SetBit(type_of_bits_array *bitwise_array, bitpos_t position);
void    ResetBit(type_of_bits_array *bitwise_array, bitpos_t position);
bool_t  ToSend(type_of_bits_array *bitwise_array, bitpos_t *saved_bit_position, bitpos_t *returned_bit_position);


#endif /* BITWISE_ARRAY_H */
