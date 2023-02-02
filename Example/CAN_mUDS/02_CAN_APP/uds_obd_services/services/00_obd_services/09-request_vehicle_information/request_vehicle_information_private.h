#ifndef REQUEST_VEHICLE_INFORMATION_PRIVATE_H
#define REQUEST_VEHICLE_INFORMATION_PRIVATE_H

#include "request_vehicle_information.h"
//SAE J1979-DA 2011, info_type, page 131
#define	INFOTYPE_VIN		0x02 //Vehicle Identification Number: 17 ASCII characters
#define INFOTYPE_CALID		0x04 //Calibration Identifications
#define INFOTYPE_CALCVN		0x06 //Calibration Verification Numbers
#define INFOTYPE_IPT		0x08 //In-use performanse tracking
#define INFOTYPE_ECU_NAME	0x0A //ECUNAME
#define INFOTYPE_ESN		0x0D //Engine serial number
#define INFOTYPE_EROTAN		0x0F //Exhaust regulation or type approval number


#define INFOTYPE_00	0x00
#define INFOTYPE_20	0x20
#define INFOTYPE_40	0x40
#define INFOTYPE_60	0x60
#define INFOTYPE_80	0x80
#define INFOTYPE_A0	0xA0
#define INFOTYPE_C0	0xC0
#define INFOTYPE_E0	0xE0

static boolean check_type_condition(struct iso15765_tp_s* request_message, uint8 number_of_infotypes);
static uint8 infotype_support_in_obd_service(uint8 infotype);
static uint16 add_infotype_info_to_response_message(struct iso15765_tp_s* response_message, uint16  temp_index, uint16 infotype);

#endif /* REQUEST_VEHICLE_INFORMATION_PRIVATE_H */
