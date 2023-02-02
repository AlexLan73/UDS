#include "can_esp_tx_handlers_private.h"

void data_collect_ECU_15(struct can_message_s* tx_mess)
{
		uint8 crc_start_bit_position = 56;

		ECU_15_frame.M_DriverRequest = (p_7_M_DriverRequestToCAN - -30000)/1;
		ECU_15_frame.MotPedPos_Driver = (p_7_MotPedPos_DriverToCAN - 0)/0.5;
		ECU_15_frame.nICEngineSpeed2 = (p_7_nICEngineSpeed2ToCAN - 0)/0.25;
		ECU_15_frame.ExtSpeedControlActive = (f_7_ExtSpeedControlActiveToCAN - 0)/1;
		ECU_15_frame.DrvUnitType = (p_7_DrvUnitTypeToCAN - 0)/1;
		ECU_15_frame.ECU_15_RC = count_ECU_15;
		ECU_15_frame.ECU_15_CS = calc_CRC8((uint8*)&ECU_15_frame, tx_mess->length, crc_start_bit_position);
asm volatile("");

		tx_mess->data.word[0] = *((uint32*)&ECU_15_frame);
		tx_mess->data.word[1] = *((((uint32*)&ECU_15_frame)+1));

		count_ECU_15++;
}
