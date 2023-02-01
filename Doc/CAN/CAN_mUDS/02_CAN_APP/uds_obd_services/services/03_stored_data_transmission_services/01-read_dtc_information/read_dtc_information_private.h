#ifndef READ_DTC_INFORMATION_PRIVAT_H_
#define READ_DTC_INFORMATION_PRIVAT_H_

#include "read_dtc_information.h"
#include "global_low_vars.h"
#include "global_high_vars.h"


#define RDTCI 			0x19 // service id
#define RDTCIPR 		0x59 // positive response code

#define RNODTCBSM_LEN   3
#define RDTCBSM_LEN		3
#define RDTCSSI_LEN		2
#define RDTCSSBDTC_LEN	6
#define _LEN
#define _LEN
#define _LEN
#define _LEN
#define _LEN
#define _LEN
#define _LEN


//sub-function = report type
#define LEV_RNODTCBSM		0x01 // reportNumberOfDTCByStatusMask
#define LEV_RDTCBSM			0x02 // reportDTCByStatusMask
#define LEV_RDTCSSI			0x03 // reportDTCSnapshotIdentification
#define LEV_RDTCSSBDTC		0x04 // reportDTCSnapshotRecordByDTCNumber
#define LEV_RDTCSDBRN		0x05 // reportDTCStoredDataByRecordNumber
#define LEV_RDTCEDRBDN		0x06 // reportDTCExtDataRecordByDTCNumber
#define LEV_RNODTCBSMR		0x07 // reportNumberOfDTCBySeverityMaskRecord
#define LEV_RDTCBSMR		0x08 // reportDTCBySeverityMaskRecord
#define LEV_RSIODTC			0x09 // reportSeverityInformationOfDTC
#define LEV_RSUPDTC			0x0A // reportSupportedDTC
#define LEV_RFTFDTC			0x0B // reportFirstTestFailedDTC
#define LEV_RFCDTC			0x0C // reportFirstConfirmedDTC
#define LEV_RMRTFDTC		0x0D // reportMostRecentTestFailedDTC
#define LEV_RMRCDTC			0x0E // reportMostRecentConfirmedDTC
#define LEV_RMMDTCBSM		0x0F // reportMirrorMemoryDTCByStatusMask
#define LEV_RMMDEDRBDN		0x10 // reportMirrorMemoryDTCExtDataRecordByDTCNumber
#define LEV_RNOMMDTCBSM		0x11 // reportNumberOfMirrorMemoryDTCByStatusMask
#define LEV_RNOOEOBDDTCBSM	0x12 // reportNumberOfEmissionsOBDDTCByStatusMask
#define LEV_ROBDDTCBSM		0x13 // reportEmissionsOBDDTCByStatusMask
#define LEV_RDTCFDC			0x14 // reportDTCFaultDetectionCounter
#define LEV_RDTCWPS			0x15 // reportDTCWithPermanentStatus
#define LEV_RDTCEDBR		0x16 // reportDTCExtDataRecordByRecordNumber
#define LEV_RUDMDTCBSM		0x17 // reportUserDefMemoryDTCByStatusMask
#define LEV_RUDMDTCSSBDTC	0x18 // reportUserDefMemoryDTCSnapshotRecordByDTCNumber
#define LEV_RUDMDTCEDRBDN	0x19 // reportUserDefMemoryDTCExtDataRecordByDTCNumber
#define LEV_RWWHOBDDTCBMR	0x42 // reportWWHOBDDTCByMaskRecord
#define LEV_RWWHOBDDTCWPS	0x55 // reportWWHOBDDTCWithPermanentStatus

//--------------------------------------------------
//FunctionalGroupIdentifier definition @ref page 378
//--------------------------------------------------

#define FGID_EMSYSGRP 		0x33 		// Emissions-system group
#define FGID_SAFESYSGRP 	0xD0		// Safety-system group
#define FGID_LEGSYSGRP 		0xD1 - 0xDF	// Legislative system group (range of value)
#define FGID_VOBDSYSGRP 	0xFE		// VOBD system
#define FGID_ALLFCTSYSGRP 	0xFF  	// All functional system groups

//--------------------------------------------------

union diagnostic_trouble_code_t {
	uint32 u;
	struct diagnostic_trouble_code {
		uint8 low;
		uint8 middle;
		uint8 high;
		uint8 reserved;
	} b;
};

//--------------------------------------------------
//DTC status bit definitions @ref page 364
//--------------------------------------------------

union dtc_status_t{
	uint8 u;
	struct dtc_status_flag {
		uint8 tf:			1;// = 0; // testFailed							- DTC failed at the time of the request
		uint8 tftoc:		1;// = 0; // testFailedThisOperationCycle		- DTC failed on the current operation cycle
		uint8 pdtc:			1;// = 0; // pendingDTC							- DTC failed on the current or previous operation cycle
		uint8 cdtc:			1;// = 0; // confirmedDTC						- DTC is confirmed at the time of the request
		uint8 tncslc:		1;// = 1; // testNotCompletedSinceLastClear		- DTC test not completed since the last code clear
		uint8 tfslc:		1;// = 0; // testFailedSinceLastClear			- DTC test failed at least once since last code clear
		uint8 tnctoc:		1;// = 1; // testNotCompletedThisOperationCycle	- DTC test not completed this operation cycle
		uint8 wir:			1;// = 0; // warningIndicatorRequested			- Server is requesting warningIndicator to be active
	}bit;
};
//--------------------------------------------------

struct dtc_record_t {
	union diagnostic_trouble_code_t code;
	union dtc_status_t status;
};

//--------------------------------------------------
//DTC severity and class definition
//--------------------------------------------------
struct dtc_severity_bit { //@ref page 374
	uint8 maintenance_only:		1; // maintenanceOnly
	uint8 check_at_next_halt:	1; // checkAtNextHalt
	uint8 check_immediately:	1; // checkImmediately
};


struct dtc_class_t { // @ref page 375
	uint8 dtc_class_0:1;
	uint8 dtc_class_1:1;
	uint8 dtc_class_2:1;
	uint8 dtc_class_3:1;
	uint8 dtc_class_4:1;
	uint8 reserved:	 3;
};

//--------------------------------------------------

//--------------------------------------------------
//DTCFormatIdentifier definition @ref page 377
//--------------------------------------------------
enum dtc_format_identifier_t {
	dtcfid_j2012_dadtcf00	= 0x00,
	dtcfid_14229_1dtcf	= 0x01,
	dtcfid_j1939_73dtcf	= 0x02,
	dtcfid_11992_4dtc	= 0x03,
	dtcfid_j2012_dadtcf04	= 0x04,
};
//--------------------------------------------------


struct dtc_mask_record_s {
	union dtcmrec_u {
		struct dtcmrec_s {
			uint8 low;		//DTCMaskRecord - DTCLowByte
			uint8 middle;	//DTCMaskRecord - DTCMiddleByte
			uint8 high;	//DTCMaskRecord - DTCHighByte
			uint8 reserved;
		}B;
		uint32 U;
	}mask;
	uint8 snapshot_number;			//DTCSnapshotRecordNumber
	uint8 data_number;			//DTCExtDataRecordNumber
};

struct dtc_serevity_mask_record_t {
	uint8 dtcsvmrec_dtcsvm;
	uint8 dtcsvmrec_dtcsm;
};

union dtc_count_t {
	uint16 u;
	struct count {
		uint8 low;
		uint8 high;
	}b;
};

static uint8 dtc_status_availability_mask = 0xFF;//0b01010101;//DTCStatusAvailabilityMask - the mask, which is supported by the server
static union dtc_count_t dtc_count;
struct dtc_record_t dtc_record;


static uint16 counting_dtc(uint8 dtc_status_mask);
static uint16 get_dtc_code_and_status(struct iso15765_tp_s* response_message, uint16 response_message_data_index, uint8 dtc_status_mask);
static uint8 status_mask_is_supported(uint8 dtcsm);
static uint16 get_the_snapshot_number_to_the_dtc_number(struct iso15765_tp_s* response_message, uint16 response_message_data_index);
static uint8 get_status_by_dtc_number(uint32 dtc);
static boolean is_dtc_exists(uint32 dtc);
static uint16 get_snapshot_record_by_dtc_number(struct iso15765_tp_s* response_message, uint16 response_message_data_index, struct dtc_mask_record_s record);

#endif /* READ_DTC_INFORMATION_PRIVAT_H_ */
