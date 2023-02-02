#include "bitwise_array.h"

bool_t GetBit(type_of_bits_array *bitwise_array, bitpos_t position)
{
	return bitwise_array[ position / BITS_PER_BITS_ARRAY_TYPE ] & ( 1 << ( position % BITS_PER_BITS_ARRAY_TYPE ) ) ? 1 : 0;
}

void SetBit(type_of_bits_array *bitwise_array, bitpos_t position)
{
	bitwise_array[ position / BITS_PER_BITS_ARRAY_TYPE ] |= ( 1 << ( position % BITS_PER_BITS_ARRAY_TYPE ) );
}

void ResetBit(type_of_bits_array *bitwise_array, bitpos_t position)
{
	bitwise_array[ position / BITS_PER_BITS_ARRAY_TYPE ] &= ~( 1 << ( position % BITS_PER_BITS_ARRAY_TYPE ) );
}

/*
 saved_bit_position - pointer to global var. Stores the last requested bit position plus one(last_requested_position + 1).

*/
bool_t ToSend(type_of_bits_array *bitwise_array, bitpos_t *saved_bit_position, bitpos_t *returned_bit_position)
{
	bitpos_t	bit_position = *saved_bit_position;

	// ищем ненулевой, начиная с saved_bit_position
#ifdef DUMB
	//
	// dumb edition
	while ( 0 == GetBit(bit_position) ) {
		// передвигаем bit_position на bit_position+1, чтобы на зациклиться не одном
		bit_position = ( bit_position + 1 ) % NUMBER_OF_BITS_IN_ARRAY;
		if ( bit_position == saved_bit_position ) {
			*saved_bit_position = 0;
			return FALSE;
		}
	}
	// передвигаем saved_bit_position на saved_bit_position+1, чтобы не зациклиться на одном
	saved_bit_position = ( bit_position + 1 ) % NUMBER_OF_BITS_IN_ARRAY;
	return TRUE;
#else
	//
	// optimized edition
	unsigned	index  = bit_position / BITS_PER_BITS_ARRAY_TYPE;
	unsigned	index0 = index;
	unsigned	bitn   = bit_position % BITS_PER_BITS_ARRAY_TYPE;
	type_of_bits_array		bit_value   = 1 << bitn;

	if ( 0 == (bitwise_array[ index ] & bit_value) ) {
		// ищем ненулевой бит дальше
		// 1. есть ли такой бит в старших битах этого слова?
		//	0001000		bit_value
		//	0000111		bit_value-1
		//	1111000		~(bit_value-1)
		if ( 0 != (bitwise_array[ index ] & (~( bit_value - 1 ))) ) {
			// ненулевой бит есть
			bitn++;				// искать с bitn+1 до максимального номера sizeof(type_of_bits_array)*8
			bit_value = 1 << bitn;
		} else {
			// в этом слове остались только нули -- ищем в других словах
			bool_t	found = FALSE;
			for ( index = (index+1) % NUMBER_OF_BYTES_IN_ARRAY; index != index0; index = (index+1) % NUMBER_OF_BYTES_IN_ARRAY ) {
				if ( 0 != bitwise_array[ index ] ) {
					// есть слово с ненулевыми битами -- найти первый
					bitn = 0;	// искать с 0 до максимального номера sizeof(type_of_bits_array)*8
					bit_value = 1;
					found = TRUE;
					break;
				}
			}
			if ( !found ) {
				// ничего в других словах нет, надо проверить младшие биты index0
				if ( 0 != (bitwise_array[ index0 ] & (bit_value-1)) ) {
					// есть в младших битах, ищем первый
					bitn = 0;	// искать с 0 до максимального номера sizeof(type_of_bits_array)*8
					bit_value = 1;
				} else {
					// ничего и нигде
					*saved_bit_position = 0;
					return FALSE;
				}
			}
		}
		// искать от bitn до BITS_PER_BITS_ARRAY_TYPE -- где-то там точно есть ненулевой (или был :))
		// в итоге должны вычислить новый 'bit_position' - позиция ненулевого бита
		//	00001000	bit_value
		//	00000111	bit_value-1
		//	11111000	~(bit_value-1)
		bit_value = ~( bit_value - 1 ) & bitwise_array[ index ];
		// ранее bit_value было значением проверяемого бита -- bit_value = 1 << bitn;
		// сейчас это биты слова bitwise_array[ index ] с номерами, большими или равными bitn; младшая часть обнулена
		//	?????000	bit_value	где-то, среди знаков вопроса, есть 1; пусть вторая справа ?????000 -> ???10000
		//
		//	???10000	bit_value
		//	???01111	bit_value - 1	? - любой бит
		//	!!!10000	~(bit_value - 1)	! - обратный к ? бит; считаем, что ! & ? равно 0
		//	00010000	(~(bit_value - 1)) & bit_value
		bit_value = ( ~( bit_value - 1 ) ) & bit_value;	// значение младшего ненулевого бита
		// теперь bit_value снова значение наименьшего ненулевого бита с номером, не меньшим чем bitn
		// осталось пересчитать index и bit_value в bit_position
		// т.е.: bit_position = index * BITS_PER_BITS_ARRAY_TYPE + bitn
		// но мы знаем bit_value, а не bitn...   bitn (между нами) равен числу нулей справа от 1 в bit_value
		bit_value = bit_value - 1;	//	00010000 -> 00001111	теперь bitn равен числу единиц в bit_value
		// складываем все биты  (гугли popcnt)
		bit_value = (bit_value & 0x55555555) + ((bit_value>>1) & 0x55555555);	// 0x55555555 = 01010101 01010101 01010101 01010101
		bit_value = (bit_value & 0x33333333) + ((bit_value>>2) & 0x33333333);	// 0x33333333 = 00110011 00110011 00110011 00110011
		bit_value = (bit_value & 0x0F0F0F0F) + ((bit_value>>4) & 0x0F0F0F0F);	// 0x0F0F0F0F = 00001111 00001111 00001111 00001111

//		////
//		bit_value *= 0x01010101;
//		bit_value >>= 24;
//		bit_value &= 0x0FF;
//		////

		bit_value = (bit_value & 0x00FF00FF) + ((bit_value>>8) & 0x00FF00FF);	// 0x00FF00FF = 00000000 11111111 00000000 11111111
		bitn = (bit_value & 0x0000FFFF) + ((bit_value>>16) & 0x0000FFFF);		// 0x0000FFFF = 00000000 00000000 11111111 11111111
		bit_position = index * BITS_PER_BITS_ARRAY_TYPE + bitn;
	} else {
		// этот бит взведён, возвращаем его
		// bit_position = bit_position;
	}
	*returned_bit_position = bit_position;
	// передвигаем saved_bit_position на saved_bit_position+1, чтобы на зациклиться на одном
	*saved_bit_position = ( bit_position + 1 )  % NUMBER_OF_BITS_IN_ARRAY;
	return TRUE;
	
#endif
}



// --------------------------------

//void Raster_1s(void)
//{
//	bitpos_t	x = 0;
//	if ( ToSend(x) ) {
//		// к отправке номер 'x'
//	}
//	
//}


//void Raster_1s(void)
//{
//	может не 'x', а saved_bit_position???
//	bitpos_t	x = 0;
//	if ( ToSend(x) ) {
//		// к отправке номер 'x'
//	}
//
//}
