#include "uds_parameters.h"
#include "bitwise_array.h"
#include "can_tp_iso15765_parameters.h"
#include "uds_timers.h"
#include "service_permissions_for_default_session_table.h"
#include "service_permissions_for_extended_session_table.h"
#include "service_permissions_for_programming_session_table.h"

//----------------------------------------------------------------------------------------------------
// Static function prototypes
//----------------------------------------------------------------------------------------------------
static boolean access_is_granted(const enum uds_security_level_e active_security_level, const struct service_permission_s* service_number_p);
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
// DIAGNOSTIC AND COMMUNICATION MANAGEMENT FUNTIONAL UNIT PARAMETERS @page 35
//----------------------------------------------------------------------------------------------------
enum uds_session_type_e uds_active_session;
enum uds_security_level_e uds_active_security_level;
uint8 suppress_uds_response;									// suppressPosRspMsgIndicationBit parameter is described on @page 26, ISO 14229-1, 2013
struct uds_timeout_value_s uds_timeout_value;
uint32 ID_of_the_client_who_established_the_connection = 0x00;	// need for multiple connection(if doesnt support multiple connection) @page 393, ISO 14229-1, 2013, Annex J
//struct request_info_struct req_dwnld_info;					// need to add to the uds struct in the future
//struct request_info_struct resp_dwnld_info;					// need to add to the uds struct in the future
extern struct uds_timer_s uds_p2_server_timer;
extern struct uds_timer_s uds_s3_server_timer;
//----------------------------------------------------------------------------------------------------

//!!!!!!!!!!!!!!!!
//all extern parameters are needed to combine all uds parameters into struct.
//TODO In the future I will make more than one uds instance
//!!!!!!!!!!!!!!!!
//----------------------------------------------------------------------------------------------------
// UPLOAD DOWNLOAD FUNTIONAL UNIT PARAMETERS @page 270
//----------------------------------------------------------------------------------------------------

extern uint8 block_sequence_counter;			// this param is described on @page 281, ISO 14229-1, 2013, table 404
extern uint16 max_number_of_block_length; 		/* how many data bytes to include in each TransferData request message from the client
										 	 	 * serviceId + BlockSequenceCounter (1 byte) + 127 server data bytes = 129 data bytes  */
//struct upload_download_sequence_flag_t upload_download_sequence_flag;

//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// DATA TRANSMISSION FUNTIONAL UNIT PARAMETERS @page 106
//----------------------------------------------------------------------------------------------------
extern boolean sending_periodic_data_enable;
//extern const struct periodic_data_id_descriptor periodic_did[];
extern struct rate_list slow_rate_list, medium_rate_list, fast_rate_list;
extern struct scheduler_config slow_rate_scheduler, medium_rate_scheduler, fast_rate_scheduler;
//----------------------------------------------------------------------------------------------------

void uds_default_session_configuration(void)
{
	uds_active_session = LEV_DS_DS;
	uds_active_security_level = access_level_00;

	uds_p2_server_timer.enable = 0;
	uds_p2_server_timer.first_measurement = 0;
	uds_p2_server_timer.value = 0;// into default session timing params are not need

	uds_s3_server_timer.enable = 0;
	uds_s3_server_timer.first_measurement = 0;
	uds_s3_server_timer.value = 0;
}

void uds_extended_session_configuration(void)
{
	// enable services in something session
	// e.g.

	uds_active_session = LEV_DS_EXTDS;
	uds_active_security_level = access_level_00;//todo if this session is set, security level is not 00. Find info about this condition.

	uds_p2_server_timer.enable = 0;
	uds_p2_server_timer.first_measurement = 0;
	uds_p2_server_timer.value = uds_timeout_value.into_extds.p2_server_default;

	uds_s3_server_timer.enable = 0;
	uds_s3_server_timer.first_measurement = 0;
	uds_s3_server_timer.value = uds_timeout_value.into_extds.s3_server;
}

void uds_programming_session_configuration(void)
{
	uds_active_session = LEV_DS_PRGS;
	uds_active_security_level = access_level_00;//todo if this session is set, security level is not 00. Find info about this condition.

	uds_p2_server_timer.enable = 0;
	uds_p2_server_timer.first_measurement = 0;
	uds_p2_server_timer.value = uds_timeout_value.into_prgs.p2_server_default;

	uds_s3_server_timer.enable = 0;
	uds_s3_server_timer.first_measurement = 0;
	uds_s3_server_timer.value = uds_timeout_value.into_prgs.s3_server;
}


//the return value is a negative response code
uint8 check_uds_service_permissions(
		const uint8 service_number,
		const enum uds_session_type_e uds_active_session,
		const enum uds_security_level_e active_security_level,
		const enum address_type target_address_type
		)
{
	const struct service_permission_s* service_permissions;

	switch (uds_active_session) {
	case LEV_DS_DS:
		service_permissions = &service_in_default_session[service_number];
		break;
	case LEV_DS_EXTDS:
		service_permissions = &service_in_extended_session[service_number];
		break;
	case LEV_DS_PRGS:
		service_permissions = &service_in_programming_session[service_number];
		break;
	default:
		suppress_uds_response = 1;
		return NRC_SNSIAS;
	}

	if (service_permissions->is_supported) {
		if (access_is_granted(active_security_level, service_permissions)) {
			return NRC_PR;
		} else {
			return NRC_SAD;
		}
	} else {
		return NRC_SNSIAS;
	}

	suppress_uds_response = 1;
	return NRC_SNSIAS;
}

static boolean access_is_granted(const enum uds_security_level_e active_security_level, const struct service_permission_s* service_number_p)
{
	switch (active_security_level) {
	case access_level_00:
		if (service_number_p->security_level_0_is_granted) {
			return TRUE;
		}
		break;
	case access_level_01:
		if (service_number_p->security_level_1_is_granted) {
					return TRUE;
		}
		break;
	case access_level_02:
		if (service_number_p->security_level_2_is_granted) {
					return TRUE;
		}
		break;
	default:
		return FALSE;
	}
	return FALSE;
}
