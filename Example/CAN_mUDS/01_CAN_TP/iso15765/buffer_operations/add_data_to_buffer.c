#include "add_data_to_buffer.h"

uint16 add_data_to_buffer(enum iso_15765_frame_type frame_type, uint8* from, uint8* to, uint8 size, uint16 position)
{
	uint16 current_index;
	uint8 pdu_offset;

	switch (frame_type) {
	case single_frame_type:
		/*			single frame pdu:
		 *			high nibble - frame type, low nibble - data length
		 */
		pdu_offset = 1;

		for( current_index = 0; current_index < size; current_index++ ) {
			to[ position + current_index ] = from[ ( current_index + pdu_offset ) ];
		}
		break;
	case first_frame_type:
		/*		first frame pdu:
		 * 			 first byte:
		 *					    high nibble - frame type, low nibble - data length
		 *			 second byte:
		 *			 			data length
		 */
		pdu_offset = 2;
		for( current_index = 0; current_index < size; current_index++ ) {
			to[ position + current_index ] = from[ ( current_index + pdu_offset ) ];
		}
		break;
	case consecutive_frame_type:
		pdu_offset = 1;
		for( current_index = 0; current_index < size; current_index++ ) {
			to[ position + current_index ] = from[ ( current_index + pdu_offset ) ];
		}
		break;
	case flow_control_frame_type:
		pdu_offset = 1;
		for( current_index = 0; current_index < size; current_index++ ) {
			to[ position + current_index ] = from[ ( current_index + pdu_offset ) ];
		}
		break;
	case unknown_type:
	default:
		break;
	}
	return 0;//(remain_data_counter - size); //TODO
}
