#include "calculate_key_for_scu.h"

enum direction_e {
	left = 0,
	right = 1,
};

enum inversion_operation_e {
	no_inversion = 0b00,
	a_inversion = 0b01,
	b_inversion = 0b10,
	c_inversion = 0b11,
};

enum bitwise_operation_code_e {
	no_operation = 0b00,
	and_operation = 0b01,
	xor_operation = 0b10,
	or_operation = 0b11
};

static uint32 word_circular_shift(uint32 var, enum direction_e shift_direction, uint32 number_of_overlapping_bit_shifts);

static void reset_bit(uint32* word, uint8 bit_position);
static void set_bit(uint32* word, uint8 bit_position);
static uint8 get_bit(uint32* word, uint8 bit_position);
static void invert_bit(uint32* word, uint8 bit_position);

static uint32 word_circular_shift(uint32 var, enum direction_e shift_direction, uint32 number_of_overlapping_bit_shifts);
static enum inversion_operation_e get_inversion_operation(uint32 seed);
static uint8 get_number_of_overlapping_bit_shifts_for_scu(uint32 seed);
static enum direction_e get_shift_direction(uint32 seed);
static uint32 do_required_bitwise_operation_for_scu(uint32 seed, uint32 key);
static void reset_required_bits_in_scu_key(uint32* key, enum inversion_operation_e inversion_operation);


uint32 calculate_scu_key(uint32 seed)
{
	uint32 key = seed;

	key = word_circular_shift(key, get_shift_direction(seed), get_number_of_overlapping_bit_shifts_for_scu(seed));

	reset_required_bits_in_scu_key(&key, get_inversion_operation(seed));

	return do_required_bitwise_operation_for_scu(seed ,key);
}


static void reset_bit(uint32* word, uint8 bit_position)
{
	*word &= ~(1 << bit_position);
}

static void set_bit(uint32* word, uint8 bit_position)
{
	*word |= (1 << bit_position);
}

static uint8 get_bit(uint32* word, uint8 bit_position)
{
	return (*word & (1 << bit_position)) ? 1 : 0;
}
//static void invert_bit(uint32_t* word, uint8_t bit_position)
//{
//	if (get_bit(word, bit_position)) {
//		reset_bit(word, bit_position);
//	}
//	else {
//		set_bit(word, bit_position);
//	}
//}

static void invert_bit(uint32* word, uint8 bit_position)
{
	uint32 a = *word;
	*word = a & ~(1 << bit_position) | (~a) & (1 << bit_position);
}

static uint32 word_circular_shift(uint32 var, enum direction_e shift_direction, uint32 number_of_overlapping_bit_shifts)
{
	if (shift_direction == right) {
		return (var >> number_of_overlapping_bit_shifts) | (var << ((sizeof(uint32) * 8) - number_of_overlapping_bit_shifts));
	}
	else if (shift_direction == left) {
		return (var << number_of_overlapping_bit_shifts) | (var >> ((sizeof(uint32) * 8) - number_of_overlapping_bit_shifts));
	}
}

static enum inversion_operation_e get_inversion_operation(uint32 seed)
{
	switch ((uint8)(((seed << 1) & 0b10) | ((seed >> 10) & 0b1))) {
	case 0b01:
		return a_inversion;
	case 0b10:
		return b_inversion;
	case 0b11:
		return c_inversion;
	case 0b00:
	default:
		return no_inversion;
	}
}

static void reset_required_bits_in_scu_key(uint32* key, enum inversion_operation_e inversion_operation)
{
	switch (inversion_operation) {
	case a_inversion:
		invert_bit(key, 24);
		invert_bit(key, 2);
		invert_bit(key, 31);
		return;
	case b_inversion:
		invert_bit(key, 27);
		invert_bit(key, 30);
		invert_bit(key, 21);
		return;
	case c_inversion:
		invert_bit(key, 26);
		invert_bit(key, 9);
		invert_bit(key, 12);
		return;
	case no_inversion:
	default:
		return;
	}
}

static uint8 get_number_of_overlapping_bit_shifts_for_scu(uint32 seed)
{
	return (uint8)(((seed >> 23) & 0b1000) | ((seed >> 1) & 0b100) | ((seed >> 27) & 0b10) | ((seed >> 14) & 0b1));
}

static enum direction_e get_shift_direction(uint32 seed)
{
	return ((seed & (1 << 4)) ? right : left);
}

static uint32 do_required_bitwise_operation_for_scu(uint32 seed,uint32 key)
{
	uint8 bitwise_operation_code = ((seed >> 18) & 0b10) | ((seed >> 30) & 0b1);
	switch (bitwise_operation_code) {
	case no_operation:
		return key;
	case and_operation:
		return (seed & key);
	case xor_operation:
		return (seed ^ key);
	case or_operation:
		return (seed | key);
	}
}
