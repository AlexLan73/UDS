#ifndef REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_PRIVATE_H
#define REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_PRIVATE_H

#define FALSE	0
#define TRUE	1

#define PID_00	0x00
#define PID_20	0x20
#define PID_40	0x40
#define PID_60	0x60
#define PID_80	0x80
#define PID_A0	0xA0
#define PID_C0	0xC0
#define PID_E0	0xE0


#include "request_current_powertrain_diagnostic_data.h"
static boolean check_type_condition(struct iso15765_tp_s* request_message, uint8 number_of_parameter_id);
static uint8 pid_support_in_obd_service(uint8 parameter_id);
static uint16 add_pid_info_to_response_message(struct iso15765_tp_s* request_message, uint16  temp_index, uint16 parameter_id);
#endif /* REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA_PRIVATE_H */
