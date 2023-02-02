#include "diagnostic_session_control_private.h"

uint8 diagnostic_session_control(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	response_message->pdu.iso15765_service_data.buffer_idx = 0;
	//session types described on @14229-1 2013 page 39-40
	enum uds_session_type_e session_type = determine_session_type(request_message->pdu.iso15765_service_data.data[1] & 0x7F);

	//TODO if requested session is already running:
	// The server shall reset all activated/initiated/changed
	// settings/controls during the activated session
	// @14229-1 2013 page 36
	switch (session_type) {
	case LEV_DS_DS:
		if (request_message->pdu.iso15765_protocol_data.length == DIAGNOSTIC_SESSION_CONTROL_LENGTH) {
			// TODO can server start session now? (add condition! maybe we are programing ECU now; ID doesn't match allowed id's)

			/* @14229-1 2013 page 37
				TODO When the server transitions from any diagnostic session other than the default session to the
				defaultSession then the server shall stop each event that has been configured in the server via the
				ResponseOnEvent (0x86) service and security shall be enabled. Any other active diagnostic functionality that is not
				supported in the defaultSession shall be terminated.
			*/

			//TODO The server shall reset all activated/initiated/changed settings/controls during the activated session
			// Security shall be relocked
			uds_default_session_configuration();

			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = DSCPR;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = uds_active_session;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_ds.p2_server_default>>8)     		&0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_ds.p2_server_default         		&0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_ds.p2_server_default_enhanced>>8)	&0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_ds.p2_server_default_enhanced    	&0xFF);
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			return NRC_PR;
		} else {
			return NRC_IMLOIF;
		}
	case LEV_DS_PRGS:
		if (request_message->pdu.iso15765_protocol_data.length == DIAGNOSTIC_SESSION_CONTROL_LENGTH) {
			// TODO can server start session now? (add condition! maybe we are programing ECU now; ID doesn't match allowed id's,
			// vehicle shall not be moving or engine shall not be running

			/*@14229-1 2013 page 37
				TODO When the server transitions from the defaultSession to any other session than the defaultSession then
				the server shall only stop the events (similar to stopResponseOnEvent) that have been configured in the server via
				the ResponseOnEvent (0x86) service during the defaultSession
			  */

			/*@14229-1 2013 page 37
				TODO When the server transitions from any diagnostic session other than the defaultSession to
				another session other than the defaultSession (including the currently active diagnostic session) then the server shall
				(re-) initialize the diagnostic session
			 */

//			if (VEHICLE_SPEED == 0 || NO_MESSAGE) { //TODO need to check sources of signals
				//TODO The server shall reset all activated/initiated/changed settings/controls during the activated session
				uds_programming_session_configuration();

				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = DSCPR;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = uds_active_session;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_prgs.p2_server_default>>8)     &0xFF);
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_prgs.p2_server_default         &0xFF);
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_prgs.p2_server_default_enhanced>>8)&0xFF);
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_prgs.p2_server_default_enhanced    &0xFF);
				response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
				return NRC_PR;
//			} else {
//				return NRC_CNC;
//			}
		} else {
			return NRC_IMLOIF;
		}
		break;
	case LEV_DS_EXTDS:
		if (request_message->pdu.iso15765_protocol_data.length == DIAGNOSTIC_SESSION_CONTROL_LENGTH) {
			// TODO can server start session now? (add condition! maybe we are programing ECU now; ID doesn't match allowed id's)

			/*@14229-1 2013 page 37
				TODO When the server transitions from the defaultSession to any other session than the defaultSession then
				the server shall only stop the events (similar to stopResponseOnEvent) that have been configured in the server via
				the ResponseOnEvent (0x86) service during the defaultSession
			  */

			/*@14229-1 2013 page 37
				TODO When the server transitions from any diagnostic session other than the defaultSession to
				another session other than the defaultSession (including the currently active diagnostic session) then the server shall
				(re-) initialize the diagnostic session
			 */

			//TODO The server shall reset all activated/initiated/changed settings/controls during the activated session
			uds_extended_session_configuration();
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = DSCPR;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = uds_active_session;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_extds.p2_server_default>>8)     &0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_extds.p2_server_default         &0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)((uds_timeout_value.into_extds.p2_server_default_enhanced>>8)&0xFF);
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = (uint8)( uds_timeout_value.into_extds.p2_server_default_enhanced    &0xFF);
			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			return NRC_PR;
		} else {
			return NRC_IMLOIF;
		}
		break;
	case LEV_DS_SSDS:
	case LEV_DS_UNKNWN:
	default:
		return NRC_SFNS;
		break;
	}
}

static enum uds_session_type_e determine_session_type(uint8 request_message_byte)
{
	switch (request_message_byte) {
	case 1:
		return LEV_DS_DS;
	case 2:
		return LEV_DS_PRGS;
	case 3:
		return LEV_DS_EXTDS;
	case 4:
		return LEV_DS_SSDS;
	default:
		return LEV_DS_UNKNWN;
	}
}

