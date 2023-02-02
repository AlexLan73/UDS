#include "read_data_by_periodic_id_private.h"

//---------------------------------------------------------------------------------------------------------------
// GLOBAL
//---------------------------------------------------------------------------------------------------------------

boolean sending_periodic_data_enable;
struct rate_list slow_rate_list, medium_rate_list, fast_rate_list;
struct scheduler_config slow_rate_scheduler, medium_rate_scheduler, fast_rate_scheduler;

// server service restrictions is on page 7 ISO 14229-3 2013
void read_data_by_periodic_id(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	if (rdbpi_length_is_valid(request_message)) {
		enum transmission_mode mode = get_transmission_mode(request_message);

		switch (mode) {
		case SEND_AT_SLOW_RATE:
		case SEND_AT_MEDIUM_RATE:
		case SEND_AT_FAST_RATE:
			if (scheduler_free_at_all()) {
				uint8 idx;
				uint8 pdid;
				uint8 number_of_supported_pdids = 0;

				for (idx = FIRST_PDID_IDX; idx < request_message->pdu.iso15765_protocol_data.length; idx++) {
					pdid = request_message->pdu.iso15765_service_data.data[idx];

					//NRC_ROOR if !none of the requested periodicDataIdentifier values! are supported by the device(page 129, 14229-1 2013, table 179)
					if (pdid > MAX_PDID_NUM /*&& (number_of_supported_pdids == 0)*/) {
						response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
						continue;
					}

					if (support_by_active_session(pdid)) {
						if (security_access_granted(pdid)) {
							if (added_to_list(pdid, mode)) {
								number_of_supported_pdids++;
							} else {
								response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
							}
						} else {
							//This NRC shall be sent if at least one of the periodicDataIdentifier is secured
							//and the server is not in an unlocked state(page 129, 14229-1 2013, table 179)
							response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SAD;
							number_of_supported_pdids = 0;
							break;
						}
					} else {
						response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
					}
				}

				if (there_is_at_least_one_pdid_in_the_active_session(number_of_supported_pdids)) {
					sending_periodic_data_enable = TRUE;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDBPIPR;
					response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
					response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				}
			} else {
				response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
			}
			break;
		case STOP_SENDING:
			//Upon receiving a ReadDataByPeriodicIdentifier request
			//including the transmissionMode stopSending the server
			//shall either stop the periodic transmission of the
			//periodicDataIdentifier(s) contained in the request message
			//or stop the transmission of all periodicDataIdentifier
			//if no specific one is specified in the request message.
			//The response message to this transmissionMode only contains the service identifier
			//@on page 127
			if (request_message->pdu.iso15765_protocol_data.length > MIN_RDBPI_LENGTH) {
				uint8 idx;
				uint8 pdid;

				for (idx = FIRST_PDID_IDX; idx < request_message->pdu.iso15765_protocol_data.length; idx++) {
					pdid = request_message->pdu.iso15765_service_data.data[idx];
					stop_sending_data(pdid);
				}
			} else if (request_message->pdu.iso15765_protocol_data.length == MIN_RDBPI_LENGTH) {
				stop_sending_of_all_pdids();
			} else {
				//developer error(length is checked first)
			}

			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDBPIPR;
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
			break;
		case UNKNOWN_TRANSMISSION_MODE:
		default :
			response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
			break;
		}
	} else {
		response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
	}
}

void read_data_by_periodic_id_scheduler(void)
{
	/*
	 * The scheduler in the server processes the periodic transmission
	 * as a single CAN frame response message in a bypass (i.e. writes
	 * the message directly to the CAN-controller/data link layer driver
	 * without using the networklayer).(page 7 ISO 14229-3 2013)
	 */
//----------------------------------------------------------------------------
	/*
	 * There is neither a protocol control information (PCI) nor a service
	 * identifier (SId) included in the response message. Only the periodic
	 * identifier and corresponding data are included(page 7 ISO 14229-3 2013)
	 */

	/*
	 *  Response message type #2 (including the periodicDataIdentifier and the data of the
	 * periodicDataIdentifier): This type of response message is mapped onto a UUDT4) message, using a
	 * different CAN identifier as used for the USDT response message. The UUDT message for a single
	 * periodicDataIdentifier shall not exceed the size of a single CAN frame. (page 48-49 ISO 15765-3 2004)
	 */
//------------------------------------------------------------------------------------------------------------
	/*  Due to the fact, that the periodic response message neither supports
	 *  protocol control information nor the service identifier information
	 *  (transport layer by-pass), the following service primitives need
	 *  to be taken into account. The service primitives as defined below
	 *  make use of the individual parameters as specified in ISO 15765-2
	 *  (page 7 ISO 14229-3 2013)
	 */

	//TODO 6.4.2.
	if (sending_periodic_data_enable) {
		send_periodic_parameter_from_slow_rate_list();
		send_periodic_parameter_from_medium_rate_list();
		send_periodic_parameter_from_fast_rate_list();
	}
}



void read_data_by_periodic_id_service_initialization(uint8 raster)
{
	rate_lists_initialization();
	schedulers_initialization(raster);
}
