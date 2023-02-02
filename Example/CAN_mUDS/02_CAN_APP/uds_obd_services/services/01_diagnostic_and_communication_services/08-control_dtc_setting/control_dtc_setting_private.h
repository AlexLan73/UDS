#ifndef CONTROL_DTC_SETTING_PRIVATE_H
#define CONTROL_DTC_SETTING_PRIVATE_H

#include "control_dtc_setting.h"
#include "uds_parameters.h"

#define RDTCSPR			0xC5
#define CDTCS_LEN		0x03
#define LEV_DTCSTP_ON 		0x01
#define LEV_DTCSTP_OFF 		0x02

static uint8 switch_on_the_dtc_status_bit_updating(void);
static uint8 switch_off_the_dtc_status_bit_updating(void);

#endif /* CONTROL_DTC_SETTING_PRIVATE_H */
