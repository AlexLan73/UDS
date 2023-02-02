#ifndef READ_UDS_MESSAGE_H
#define READ_UDS_MESSAGE_H

#include "Platform_Types.h"
#include "uds_parameters.h"
#include "write_response_message.h"
//--
#include "diagnostic_session_control.h"
#include "ecu_reset.h"
#include "tester_present.h"
#include "security_access.h"
//#include "request_transfer_exit.h"
//-
#include "read_data_by_identifier.h"
//--
#include "read_dtc_information.h"
#include "clear_dtc_information.h"
//--
//#include "request_download.h"
//#include "transfer_data.h"

extern void read_uds_message(struct iso15765_tp_s* request_message);


#endif /* READ_UDS_MESSAGE_H */
