#include "uds_initialization.h"
//#include "upload_download_parameters.h"
#include "read_data_by_periodic_id.h"
#include "uds_timers.h"

void uds_initialization(void)
{
	//----------------------------------------------------------------------------
	// DIAGNOSTIC AND COMMUNICATION MANAGEMENT FUNTIONAL UNIT PARAMETERS @page 35, ISO 14229-1 2013
	//----------------------------------------------------------------------------
	set_uds_parameter(ACTIVE_SESSION, 					LEV_DS_DS);
	set_uds_parameter(ACTIVE_SECURITY_LEVEL, 			access_level_00);

	set_uds_parameter(P2_TIMEOUT_VALUE_FOR_DS, 			P2_SERVER_MAX_DIAGNOSTIC_DEFAULT_VALUE);	//< table 7 15031-5 2015
	set_uds_parameter(P2_STAR_TIMEOUT_VALUE_FOR_DS, 	P2_SERVER_MAX_S_DIAGNOSTIC_DEFAULT_VALUE);
	set_uds_parameter(P2_TIMEOUT_VALUE_FOR_PRGS, 		P2_SERVER_MAX_PROGRAMMING_DEFAULT_VALUE);
	set_uds_parameter(P2_STAR_TIMEOUT_VALUE_FOR_PRGS,	P2_SERVER_MAX_S_PROGRAMMING_DEFAULT_VALUE);
	set_uds_parameter(P2_TIMEOUT_VALUE_FOR_EXTDS, 		P2_SERVER_MAX_EXTENDED_DEFAULT_VALUE);
	set_uds_parameter(P2_STAR_TIMEOUT_VALUE_FOR_EXTDS,	P2_SERVER_MAX_S_EXTENDED_DEFAULT_VALUE);
	//TODO P4_SERVER_TIMER with enhanced timing @page 16, ISO 14229- 2010
	set_uds_parameter(S3_TIMEOUT_VALUE_FOR_DS,			S3_SERVER_MAX_DIAGNOSTIC_DEFAULT_VALUE);
	set_uds_parameter(S3_TIMEOUT_VALUE_FOR_PRGS,		S3_SERVER_MAX_PROGRAMMING_DEFAULT_VALUE);
	set_uds_parameter(S3_TIMEOUT_VALUE_FOR_EXTDS,		S3_SERVER_MAX_EXTENDED_DEFAULT_VALUE);
	//---------------------------------------------------------------------------

	//----------------------------------------------------------------------------
	// UPLOAD DOWNLOAD FUNTIONAL UNIT PARAMETERS @page 106, ISO 14229-1 2013
	//----------------------------------------------------------------------------

	set_uds_parameter(MAX_NUMBER_OF_BLOCK_LENGTH, 	134); // how many data bytes are included in each TransferData request message from the client
	set_uds_parameter(BLOCK_SEQUENCE_COUNTER, 		0);

	//----------------------------------------------------------------------------
	// DATA TRANSMISSION FUNCTIONAL UNIT PARAMETERS @page 270, ISO 14229-1 2013
	//----------------------------------------------------------------------------
	read_data_by_periodic_id_service_initialization(10);
	//----------------------------------------------------------------------------
}

enum uds_result set_uds_parameter(enum uds_parameter parameter_name, uint16 value)
{
	switch (parameter_name) {
	case ACTIVE_SESSION:
		if(1/* */ ) { //TODO
			uds_active_session = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case ACTIVE_SECURITY_LEVEL:
		if(1/* */ ) { //TODO
			uds_active_security_level = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_TIMEOUT_VALUE_FOR_DS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_ds.p2_server_default = value;
			uds_p2_server_timer.value = uds_timeout_value.into_ds.p2_server_default;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_STAR_TIMEOUT_VALUE_FOR_DS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_ds.p2_server_default_enhanced = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_TIMEOUT_VALUE_FOR_PRGS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_prgs.p2_server_default = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_STAR_TIMEOUT_VALUE_FOR_PRGS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_prgs.p2_server_default_enhanced = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_TIMEOUT_VALUE_FOR_EXTDS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_extds.p2_server_default = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case P2_STAR_TIMEOUT_VALUE_FOR_EXTDS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_extds.p2_server_default_enhanced = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case S3_TIMEOUT_VALUE_FOR_DS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_ds.s3_server = value;
			uds_s3_server_timer.value = uds_timeout_value.into_ds.s3_server;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case S3_TIMEOUT_VALUE_FOR_PRGS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_prgs.s3_server = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
	case S3_TIMEOUT_VALUE_FOR_EXTDS:
		if(1/* */ ) { //TODO
			uds_timeout_value.into_extds.s3_server = value;
			return UDS_OK;
		} else {
			return UDS_ERROR;
		}
//	case MAX_NUMBER_OF_BLOCK_LENGTH:
//		if(1/* */ ) { //TODO
//			max_number_of_block_length = value;
//			return UDS_OK;
//		} else {
//			return UDS_ERROR;
//		}
//	case BLOCK_SEQUENCE_COUNTER:
//		if (1/* */ ) { //TODO
//			block_sequence_counter = value;
//			return UDS_OK;
//		} else {
//			return UDS_ERROR;
//		}
	default:
		return UDS_ERROR;
	}
}
