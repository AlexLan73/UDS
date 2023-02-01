#include "extract_data_from_buffer.h"
#pragma GCC optimize "O0"

uint16 extract_data_from_buffer(enum iso_15765_frame_type frame_type, uint8* from, uint8* to, uint8 size, uint16 position)
{
	uint16 current_index;
	uint8 pdu_offset;
	uint8 padding_byte_index;

	switch (frame_type) {
	case single_frame_type:
		//to[0] = 0x00;
		pdu_offset = 1;
		padding_byte_index = 0;

		if (size <= SINGLE_FRAME_MAX_LENGTH) {
			for ( current_index = 0; current_index < size; current_index++ ) {
				to[ ( pdu_offset + current_index ) ] = from[ position + current_index ];
			}

			if (size < SINGLE_FRAME_MAX_LENGTH) {
				padding_byte_index = pdu_offset + current_index;
				//unsigned char padding_size = CONSECUTIVE_FRAME_MAX_LENGTH - size + pdu_offset;//size + ((CONSECUTIVE_FRAME_MAX_LENGTH - size)) + 1;

				for( current_index = padding_byte_index; current_index < 8 ; current_index++ ) {
					to[ ( current_index ) ] = server_parameter[0].padding_value;//from[ position ];
				}
			}
		}
		break;
	case first_frame_type:
		pdu_offset = 2;

		if (size <= FIRST_FRAME_LENGTH) {
			for ( current_index = 0; current_index < size; current_index++ ) {
				to[ ( pdu_offset + current_index ) ] = from[ position + current_index ];
			}
		}
		break;
	case consecutive_frame_type:
		pdu_offset = 1;
		padding_byte_index = 0;

		if (size == CONSECUTIVE_FRAME_MAX_LENGTH) {
			for ( current_index = 0; current_index < size; current_index++ ) {
				to[ ( pdu_offset + current_index ) ] = from[ position + current_index ];
			}
		}

		if (size < CONSECUTIVE_FRAME_MAX_LENGTH) {
			for( current_index = 0; current_index < size; current_index++ ) {
				to[ ( pdu_offset + current_index ) ] = from[ position + current_index ];
			}

			padding_byte_index = pdu_offset + current_index;
			//unsigned char padding_size = CONSECUTIVE_FRAME_MAX_LENGTH - size + pdu_offset;//size + ((CONSECUTIVE_FRAME_MAX_LENGTH - size)) + 1;

			for( current_index = padding_byte_index; current_index < 8 ; current_index++ ) {
				to[ ( current_index ) ] = server_parameter[0].padding_value;//from[ position ];
			}
		}
		break;
	case flow_control_frame_type:
		pdu_offset = 1;

		for ( current_index = 0; current_index < size; current_index++ ) {
			to[ ( pdu_offset + current_index ) ] = from[ position + current_index ];
		}
		break;
	case unknown_type:
	default:
		break;
	}

	return 0;// (remain_data_counter - size);
}
