#ifndef READ_DATA_BY_PERIODIC_ID_PRIVATE_H
#define READ_DATA_BY_PERIODIC_ID_PRIVATE_HREAD_DATA_BY_PERIODIC_ID_PRIVATE_H

#include "read_data_by_periodic_id.h"
#include "can_initialization.h"
#include "IfxMultican_Can.h"
#include "bitwise_array.h"

#define MIN_RDBPI_LENGTH	2 	//(service id) + (tx_mode=stopSending)
#define MAX_RDBPI_LENGTH	10	//(service id) + (tx_mode) + 8 DID
#define MAX_PDID_NUM		2
#define FIRST_PDID_IDX		2

enum transmission_mode {
	UNKNOWN_TRANSMISSION_MODE = 0,
	SEND_AT_SLOW_RATE = 1000,
	SEND_AT_MEDIUM_RATE = 300,
	SEND_AT_FAST_RATE = 100,
	STOP_SENDING = 4,
};

static void rate_lists_initialization(void);
static void schedulers_initialization(uint16 raster);

static boolean rdbpi_length_is_valid(struct iso15765_tp_s* response_message);
static enum transmission_mode get_transmission_mode(struct iso15765_tp_s* response_message);

static boolean scheduler_free_at_all(void);
static boolean support_by_active_session(uint8 pdid);
static boolean security_access_granted(uint8 pdid);
static boolean added_to_list(uint8 pdid, enum transmission_mode tm);
static boolean there_is_at_least_one_pdid_in_the_active_session(uint8 supported_pdid);

static void stop_sending_data(uint8 pdid);
static void stop_sending_of_all_pdids(void);

static boolean used_in_slow_rate_list(uint8 pdid);
static boolean used_in_medium_rate_list(uint8 pdid);
static boolean used_in_fast_rate_list(uint8 pdid);

static boolean remove_from_rate_list(uint8 pdid, enum transmission_mode tm);

static void send_periodic_parameter_from_slow_rate_list(void);
static void send_periodic_parameter_from_medium_rate_list(void);
static void send_periodic_parameter_from_fast_rate_list(void);

static void send_periodic_parameter_from_rate_list(struct rate_list *p, struct scheduler_config *sp);

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
uint8 test_parameter_1 = 1;
uint8 test_parameter_2 = 2;
uint8 test_parameter_3 = 3;
uint8 test_parameter_4 = 4;
uint8 test_parameter_5 = 5;
uint8 test_parameter_6 = 6;
uint8 test_parameter_7 = 7;

uint8 test_parameter_8 = 8;
uint8 test_parameter_9 = 9;
uint8 test_parameter_10 = 10;
uint8 test_parameter_11 = 11;
uint8 test_parameter_12 = 12;
uint8 test_parameter_13 = 13;
uint8 test_parameter_14 = 14;

//	The periodicDataIdentifier represents the low byte of a dataIdentifier out of
//	the dataIdentifier range reserved for this service (0xF2XX, see page 337 for allowed periodicDataIdentifier values),
//	e.g. the periodicDataIdentifier 0xE3 used in this service is the dataIdentifier 0xF2E3
//  therefore, we can determine numbers of pdid in the range 0-255

//	array index == periodicDataIdentifier
const struct periodic_data_id_descriptor periodic_did[MAX_PDID_NUM] = {
						//session mode,						  security mod,			DataPointers
/* pdid 0xF200 */		{   DS_MASK		   					 , SEC_LEV_0_MASK, {&test_parameter_1, &test_parameter_2, &test_parameter_3, &test_parameter_4, &test_parameter_5, &test_parameter_6} },
/* pdid 0xF201 */		{(DS_MASK||PS_MASK)					 , SEC_LEV_0_MASK, {&test_parameter_8, &test_parameter_9, &test_parameter_10, &test_parameter_11, &test_parameter_12, &test_parameter_13} }
};

//-------------------------------------------------------------------------------------------------------------
// static functions
//-------------------------------------------------------------------------------------------------------------
static void rate_lists_initialization(void)
{
	slow_rate_list.current_pdid_to_send = 0;
	medium_rate_list.current_pdid_to_send = 0;
	fast_rate_list.current_pdid_to_send = 0;

	uint8 idx = 0;
	for(idx =0; idx < NUMBER_OF_BYTES_IN_ARRAY; idx++) {
		slow_rate_list.row[idx] = 0;
		medium_rate_list.row[idx] = 0;
		fast_rate_list.row[idx] = 0;
	}
}

static void schedulers_initialization(uint16 raster)
{
	sending_periodic_data_enable = FALSE;

	slow_rate_scheduler.elapsed_time = 0;
	slow_rate_scheduler.parameter_counter = 0;
	slow_rate_scheduler.number_of_sent_parameters = 0;
	slow_rate_scheduler.number_of_requested_parameters = 0;
	slow_rate_scheduler.full_circle_time = 1000;
	slow_rate_scheduler.max_number_of_parameters_per_full_circle_time =
				slow_rate_scheduler.full_circle_time / raster;


	medium_rate_scheduler.elapsed_time = 0;
	medium_rate_scheduler.parameter_counter = 0;
	medium_rate_scheduler.number_of_sent_parameters = 0;
	medium_rate_scheduler.number_of_requested_parameters = 0;
	medium_rate_scheduler.full_circle_time = 300;
	medium_rate_scheduler.max_number_of_parameters_per_full_circle_time =
				medium_rate_scheduler.full_circle_time / raster;


	fast_rate_scheduler.elapsed_time = 0;
	fast_rate_scheduler.parameter_counter = 0;
	fast_rate_scheduler.number_of_sent_parameters = 0;
	fast_rate_scheduler.number_of_requested_parameters = 0;
	fast_rate_scheduler.full_circle_time = 100;
	fast_rate_scheduler.max_number_of_parameters_per_full_circle_time =
			fast_rate_scheduler.full_circle_time / raster;
}

static boolean rdbpi_length_is_valid(struct iso15765_tp_s *rm)
{
	return ((rm->pdu.iso15765_protocol_data.length >= MIN_RDBPI_LENGTH)&&
			(rm->pdu.iso15765_protocol_data.length <= MAX_RDBPI_LENGTH))?1:0;
}

static enum transmission_mode get_transmission_mode(struct iso15765_tp_s *request_message)
{
	switch (request_message->pdu.iso15765_service_data.data[1]) {
	case 1:
		return SEND_AT_SLOW_RATE;
	case 2:
		return SEND_AT_MEDIUM_RATE;
	case 3:
		return SEND_AT_FAST_RATE;
	case 4:
		return STOP_SENDING;
	default:
		return UNKNOWN_TRANSMISSION_MODE;
	}
}

static boolean scheduler_free_at_all(void)
{
	//TODO
	return TRUE;
}

static boolean support_by_active_session(uint8 pdid)
{
	uint8 session_mask = DS_MASK;

	switch (uds_active_session) {
	case LEV_DS_DS:
		session_mask = DS_MASK;
		break;
	case LEV_DS_PRGS:
		session_mask = PS_MASK;
		break;
	case LEV_DS_EXTDS:
		session_mask = ES_MASK;
		break;
	case LEV_DS_SSDS:
		session_mask = SS_MASK;
		break;
	default:
		return FALSE;
	}

	if (periodic_did[pdid].session_mode && session_mask) {
		return TRUE;
	}

	return FALSE;
}

static boolean security_access_granted(uint8 pdid)
{
	uint8 security_level_mask = SEC_LEV_0_MASK;

	switch (uds_active_security_level) {
	case access_level_00:
		security_level_mask = SEC_LEV_0_MASK;
		break;
	case access_level_01:
		security_level_mask = SEC_LEV_1_MASK;
		break;
	case access_level_02:
		security_level_mask = SEC_LEV_2_MASK;
		break;
	default:
		return FALSE;
	}

	if (periodic_did[pdid].security_mode && security_level_mask) {
		return TRUE;
	}
	return FALSE;
}

static boolean added_to_list(uint8 pdid, enum transmission_mode tm)
{
	//	A periodicDataIdentifier shall only be supported with
	//	a single transmissionMode at a given time.
	//	A change to the schedule of a periodicDataIdentifier shall be
	//	performed on reception of a request message with the transmissionMode
	//	parameter set to a new schedule for the same periodicDataIdentifier.
	//	@page 126 14229-1 2013
	switch (tm) {
	case SEND_AT_SLOW_RATE:
		if (used_in_slow_rate_list(pdid)) {
			return TRUE;
		}
		if (used_in_medium_rate_list(pdid)) {
			ResetBit(medium_rate_list.row, pdid);
		}
		if (used_in_fast_rate_list(pdid)) {
			ResetBit(fast_rate_list.row, pdid);
		}
		if (slow_rate_scheduler.number_of_requested_parameters != 255) {
			SetBit(slow_rate_list.row, pdid);
			slow_rate_scheduler.number_of_requested_parameters++;
			return TRUE;
		}
		break;
	case SEND_AT_MEDIUM_RATE:
		if (used_in_medium_rate_list(pdid)) {
			return TRUE;
		}
		if (used_in_slow_rate_list(pdid)) {
			ResetBit(slow_rate_list.row, pdid);
		}
		if (used_in_fast_rate_list(pdid)) {
			ResetBit(fast_rate_list.row, pdid);
		}
		if (medium_rate_scheduler.number_of_requested_parameters != 255) {
			SetBit(medium_rate_list.row, pdid);
			medium_rate_scheduler.number_of_requested_parameters++;
			return TRUE;
		}
		break;
	case SEND_AT_FAST_RATE:
		if (used_in_fast_rate_list(pdid)) {
			return TRUE;
		}
		if (used_in_slow_rate_list(pdid)) {
			ResetBit(slow_rate_list.row, pdid);
		}
		if (used_in_medium_rate_list(pdid)) {
			ResetBit(medium_rate_list.row, pdid);
		}
		if (fast_rate_scheduler.number_of_requested_parameters != 255) {
			SetBit(fast_rate_list.row, pdid);
			fast_rate_scheduler.number_of_requested_parameters++;
			return TRUE;
		}
		break;
	case STOP_SENDING:
	case UNKNOWN_TRANSMISSION_MODE:
	default:
		break;
	}
	return FALSE;
}

static boolean there_is_at_least_one_pdid_in_the_active_session(uint8 supported_pdid_number)
{
	return supported_pdid_number?1:0;
}

static void stop_sending_data(uint8 pdid)
{
	remove_from_rate_list(pdid, SEND_AT_SLOW_RATE);
	remove_from_rate_list(pdid, SEND_AT_MEDIUM_RATE);
	remove_from_rate_list(pdid, SEND_AT_FAST_RATE);

	if (slow_rate_scheduler.number_of_requested_parameters == 0 &&
		medium_rate_scheduler.number_of_requested_parameters == 0 &&
		fast_rate_scheduler.number_of_requested_parameters == 0
		) {
		sending_periodic_data_enable = FALSE;
	}
}

static void stop_sending_of_all_pdids(void)
{
	read_data_by_periodic_id_service_initialization(10); //TODO unknown var: raster
	sending_periodic_data_enable = FALSE;
}

static void send_periodic_parameter_from_slow_rate_list(void)
{
	send_periodic_parameter_from_rate_list(&slow_rate_list, &slow_rate_scheduler);
}

static void send_periodic_parameter_from_medium_rate_list(void)
{
	send_periodic_parameter_from_rate_list(&medium_rate_list, &medium_rate_scheduler);
}

static void send_periodic_parameter_from_fast_rate_list(void)
{
	send_periodic_parameter_from_rate_list(&fast_rate_list, &fast_rate_scheduler);
}

static void send_periodic_parameter_from_rate_list(struct rate_list *list, struct scheduler_config *rate_list_config)
{
	struct can_message_s can_msg;


	//			|data0| data1....data7 |
	//response:  pdid + linked data (without positive response id)

	/*	The documented periodic rate for a specific
	 *  transmissionMode is defined as the time between any two
	 *  consecutive response messages with the same periodicDataIdentifier*/

//	rate_list_config->elapsed_time += 10; //todo
//
//	if (rate_list_config->elapsed_time == rate_list_config->full_circle_time) {
//		rate_list_config->elapsed_time = 0; //todo
//		rate_list_config->number_of_sent_parameters = 0;
//	}

	if (rate_list_config->parameter_counter < rate_list_config->max_number_of_parameters_per_full_circle_time) {
		rate_list_config->parameter_counter++;
	} else {
		rate_list_config->parameter_counter = 1;
		rate_list_config->number_of_sent_parameters = 0;
	}

	if (rate_list_config->number_of_sent_parameters < rate_list_config->number_of_requested_parameters) {
		rate_list_config->number_of_sent_parameters++;

		bitpos_t	low_byte_of_a_data_identifier = list->current_pdid_to_send;
		if (ToSend(list->row, &(list->current_pdid_to_send), &low_byte_of_a_data_identifier)) {
			// к отправке номер 'temp_bit_position' TODO
			can_msg.data.byte[0] = RDBPIPR;
			can_msg.data.byte[1] = low_byte_of_a_data_identifier;
			can_msg.data.byte[2] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[0]);
			can_msg.data.byte[3] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[1]);
			can_msg.data.byte[4] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[2]);
			can_msg.data.byte[5] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[3]);
			can_msg.data.byte[6] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[4]);
			can_msg.data.byte[7] = *(periodic_did[low_byte_of_a_data_identifier].pointer_to_parameter[5]);

			can_write_frame(can_msg);
		}
	}
}

static boolean used_in_slow_rate_list(uint8 pdid)
{
	return (GetBit(slow_rate_list.row, pdid))?1:0;
}

static boolean used_in_medium_rate_list(uint8 pdid)
{
	return (GetBit(medium_rate_list.row, pdid))?1:0;
}

static boolean used_in_fast_rate_list(uint8 pdid)
{
	return (GetBit(fast_rate_list.row, pdid))?1:0;
}

static boolean remove_from_rate_list(uint8 pdid, enum transmission_mode tm)
{
	switch (tm) {
	case SEND_AT_SLOW_RATE:
		if (slow_rate_scheduler.number_of_requested_parameters != 0) {
			if (GetBit(slow_rate_list.row, pdid)) {
				ResetBit(slow_rate_list.row, pdid);
				slow_rate_scheduler.number_of_requested_parameters--;
				return TRUE;
			}
		}
		break;
	case SEND_AT_MEDIUM_RATE:
		if (medium_rate_scheduler.number_of_requested_parameters != 0) {
			if (GetBit(medium_rate_list.row, pdid)) {
				ResetBit(medium_rate_list.row, pdid);
				medium_rate_scheduler.number_of_requested_parameters--;
				return TRUE;
			}
		}
		break;
	case SEND_AT_FAST_RATE:
		if (fast_rate_scheduler.number_of_requested_parameters != 0) {
			if (GetBit(fast_rate_list.row, pdid)) {
				ResetBit(fast_rate_list.row, pdid);
				fast_rate_scheduler.number_of_requested_parameters--;
				return TRUE;
			}
		}
		break;
	case UNKNOWN_TRANSMISSION_MODE:
	case STOP_SENDING:
	default:
		break;

	}
	return FALSE;
}



//------------------------------------------------------------------------------------------------------------

#endif /* READ_DATA_BY_PERIODIC_ID_PRIVATE_H */
