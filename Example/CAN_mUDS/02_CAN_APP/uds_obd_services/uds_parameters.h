#ifndef UDS_PARAMETERS_H
#define UDS_PARAMETERS_H

#include "can_tp_iso15765_parameters.h"

//----------------------------------------------------------------------------
// OBD services
//----------------------------------------------------------------------------

#define RCPDD 			0x01 //Request current powertrain diagnostic data
#define RPFFD 			0x02 //Request powertrain freeze frame data
#define RERDTC 			0x03 //Request emission-related diagnostic trouble codes
#define CRERDI 			0x04 //Clear/Reset emission-related diagnostic information
#define ROSMTR 			0x05 //Request oxygen sensor monitoring test results
#define ROBMTRSMS		0x06 //Request on-board monitoring test results for specific monitored systems
#define RERDTCDDCLCDC	0x07 //Request emission-related diagnostic trouble codes detected during current or last completed driving cycle
#define RCOBSTC			0x08 //Request control of on-board system, test, or component
#define RVI 			0x09 //Request vehicle information

//----------------------------------------------------------------------------
// UDS services
//----------------------------------------------------------------------------
#define DIAGSC 		0x10 //DiagnosticSessionControl 		//sub+
#define ER 			0x11 //ECUReset 						//sub+
#define SA 			0x27 //SecurityAccess 					//sub+
#define CC 			0x28 //CommunicationControl 			//sub+
#define	TPRES 		0x3E //TesterPresent 					//sub+
#define ATP 		0x83 //AccessTimingParameter 			//sub+
#define SDATAT 		0x84 //SecuredDataTransmission			//		sub-
#define CDTCS		0x85 //ControlDTCSetting				//sub+
#define ROE			0x86 //ResponseOnEvent					//sub+
#define LC			0x87 //LinkControl						//sub+
#define RDBI		0x22 //ReadDataByIdentifier				//		sub-
#define RMBA		0x23 //ReadMemoryByAddress				//		sub-
#define RSDBI		0x24 //ReadScalingDataByIdentifier		//		sub-
#define RDBPI		0x2A //ReadDataByPeriodicIdentifier		//		sub-
#define DDDI		0x2C //DynamicallyDefineDataIdentifier 	//sub+
#define WDBI		0x2E //WriteDataByIdentifier			//		sub-
#define WMBA		0x3D //WriteMemoryByAddress				//		sub-
#define CDTCI		0x14 //ClearDiagnosticInformation		//		sub-
#define RDTCI		0x19 //ReadDTCInformation				//sub+
#define IOCBI		0x2F //InputOutputControlByIdentifier	//		sub-
#define RC			0x31 //RoutineControl					//sub+
#define RD			0x34 //RequestDownload					//		sub-
#define RU			0x35 //RequestUpload					//		sub-
#define TD			0x36 //TransferData						//		sub-
#define RTE			0x37 //RequestTransferExit				//		sub-
#define RFT			0x38 //RequestFileTransfer				//		sub-

//----------------------------------------------------------------------------
// UDS negative response codes @ref p.333
//----------------------------------------------------------------------------

#define NRC_PR		 	0x00 //positive response message
#define NRC_SNS 		0x11 //serviceNotSupported
#define NRC_SFNS 		0x12 //subFunctionNotSupported
#define NRC_IMLOIF 		0x13 //incorrectMessageLengthOrInvalidFormat
#define NRC_RTL			0x14 //responseTooLong
#define NRC_BRR			0x21 //busyRepeateRequest
#define NRC_CNC 		0x22 //conditionsNotCorrect
#define NRC_RSE 		0x24 //requestSequenceError
#define NRC_ROOR 		0x31 //requestOutOfRange
#define NRC_SAD 		0x33 //securityAccessDenied
#define NRC_IK 			0x35 //invalidKey
#define NRC_ENOA 		0x36 //exceededNumberOfAttempts
#define NRC_RTDNE 		0x37 //requiredTimeDelayNotExpired
#define NRC_UDNA 		0x70 //uploadDownloadNotAccepted
#define NRC_TDS 		0x71 //transferDataSuspended
#define NRC_GPF 		0x72 //generalProgrammingFailure
#define NRC_WBSC 		0x73 //wrongBlockSequenceCounter
#define NRC_RCRRP 		0x78 //requestCorrectlyReceivedResponsePending
#define NRC_SFNSIAS 	0x7E //subFunctionNotSupportedInActiveSession
#define NRC_SNSIAS 		0x7F //Service not supported in active session

#define NRC_VTH			0x92 //voltageTooHigh
#define NRC_VTL			0x93 //voltageTooLow


//----------------------------------------------------------------------------
// UDS positive response codes (buffer_for_transmit[0])
//----------------------------------------------------------------------------

#define DSCPR	 		0x50 //DiagnosticSessionControl 		//sub+
#define ERPR 			0x51 //ECUReset 						//sub+
#define SAPR 			0x67 //SecurityAccess 					//sub+
#define CCPR 			0x68 //CommunicationControl 			//sub+
#define	TPPR 			0x7E //TesterPresent 					//sub+
#define ATPPR	 		0x83 //AccessTimingParameter 			//sub+
#define SDTPR	 		0xC4 //SecuredDataTransmission			//sub-
#define CDTCSPR			0xC5 //ControlDTCSetting				//sub+
#define ROEPR			0xC6 //ResponseOnEvent					//sub+
#define LCPRPR			0xC7 //LinkControl						//sub+
#define RDBIPR			0x62 //ReadDataByIdentifier				//sub-
#define RMBAPR			0x63 //ReadMemoryByAddress				//sub-
#define RSDBIPR			0x64 //ReadScalingDataByIdentifier		//sub-
#define RDBPIPR			0x6A //ReadDataByPeriodicIdentifier		//sub-
#define DDDIPR			0x6C //DynamicallyDefineDataIdentifier 	//sub+
#define WDBIPR			0x6E //WriteDataByIdentifier			//sub-
#define WMBAPR			0x7D //WriteMemoryByAddress				//sub-
#define CDTCIPR			0x54 //ClearDiagnosticInformation		//sub-
#define RDTCIPR			0x59 //ReadDTCInformation				//sub+
#define IOCBIPR			0x6F //InputOutputControlByIdentifier	//sub-
#define RCPR			0x71 //RoutineControl					//sub+
#define RDPR			0x74 //RequestDownload					//sub-
#define RUPR			0x75 //RequestUpload					//sub-
#define TDPR			0x76 //TransferData						//sub-
#define RTEPR			0x77 //RequestTransferExit				//sub-
#define RFTPR			0x78 //RequestFileTransfer				//sub-


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#define P2_SERVER_MAX_DIAGNOSTIC_DEFAULT_VALUE 		50
#define P2_SERVER_MAX_S_DIAGNOSTIC_DEFAULT_VALUE	5000
#define P2_SERVER_MAX_PROGRAMMING_DEFAULT_VALUE		50
#define P2_SERVER_MAX_S_PROGRAMMING_DEFAULT_VALUE	5000
#define P2_SERVER_MAX_EXTENDED_DEFAULT_VALUE		50
#define P2_SERVER_MAX_S_EXTENDED_DEFAULT_VALUE		5000

#define S3_SERVER_MAX_DIAGNOSTIC_DEFAULT_VALUE		5000
#define S3_SERVER_MAX_PROGRAMMING_DEFAULT_VALUE		5000
#define S3_SERVER_MAX_EXTENDED_DEFAULT_VALUE		5000

#define MIN_MESSAGE_LENGTH_WITH_SUBFUNCTION 2

enum uds_parameter
{
	ACTIVE_SESSION = 0xF1,
	ACTIVE_SECURITY_LEVEL,
	P2_TIMEOUT_VALUE_FOR_DS,
	P2_STAR_TIMEOUT_VALUE_FOR_DS,
	P2_TIMEOUT_VALUE_FOR_PRGS,
	P2_STAR_TIMEOUT_VALUE_FOR_PRGS,
	P2_TIMEOUT_VALUE_FOR_EXTDS,
	P2_STAR_TIMEOUT_VALUE_FOR_EXTDS,
	S3_TIMEOUT_VALUE_FOR_DS,
	S3_TIMEOUT_VALUE_FOR_PRGS,
	S3_TIMEOUT_VALUE_FOR_EXTDS,

	MAX_NUMBER_OF_BLOCK_LENGTH,
	BLOCK_SEQUENCE_COUNTER
};

enum uds_session_type_e {
	LEV_DS_DS =  	0x01,
	LEV_DS_PRGS = 	0x02,
	LEV_DS_EXTDS =	0x03,
	LEV_DS_SSDS =	0x04,
	LEV_DS_UNKNWN = 255
};

enum uds_security_level_e {
	access_level_00 = 0,
	access_level_01,
	access_level_02
};

enum uds_result {
	UDS_OK = 0x00,
	UDS_TIMEOUT_P2 = 0x01,
	UDS_TIMEOUT_P2_STAR = 0x02,
	UDS_ERROR = 0x0C,
};

struct all_uds_server_timers_s
{
	uint16 p2_server_default;
	uint16 p2_server_default_enhanced;
	uint16 s3_server;
};

struct uds_timeout_value_s {
	struct all_uds_server_timers_s into_ds;
	struct all_uds_server_timers_s into_prgs;
	struct all_uds_server_timers_s into_extds;
};

struct service_permission_s {
	uint8 is_supported:1;
	uint8 support_phy_addressing_type:1;
	uint8 support_fun_addressing_type:1;
	uint8 security_level_0_is_granted:1;
	uint8 security_level_1_is_granted:1;
	uint8 security_level_2_is_granted:1;
};

extern uint8 suppress_uds_response;
extern enum uds_session_type_e uds_active_session;
extern enum uds_security_level_e uds_active_security_level;
extern uint16 uds_p_2_server_timer;									// parameter is described on @page 11, ISO 14229-2, 2013
extern uint16 uds_s_3_server_timer;									// parameter is described on @page 17, ISO 14229-2, 2013

extern struct uds_timeout_value_s uds_timeout_value;

extern uint8 block_sequence_counter;
extern uint16 max_number_of_block_length; // serviceId + BlockSequenceCounter (1 byte) + 127 server data bytes = 129 data bytes
					   	  	  	  	  	  // how many data bytes to include in each TransferData request message from the client
extern struct upload_download_sequence_flag_t upload_download_sequence_flag;
//extern struct request_service_struct req_dwnld_info, req_upld_info;

extern void uds_default_session_configuration(void);
extern void uds_extended_session_configuration(void);
extern void uds_programming_session_configuration(void);
extern uint8 check_uds_service_permissions(
		const uint8 service_number,
		const enum uds_session_type_e uds_active_session,
		const enum uds_security_level_e active_security_level,
		const enum address_type target_address_type
		);

#endif /* UDS_PARAMETERS_H */
