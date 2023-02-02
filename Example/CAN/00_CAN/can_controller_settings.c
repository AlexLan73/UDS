
//EXAMPLE:

#include "can_initialization.h"
#include "can_controller_settings.h"

const Can_ControllerSettingsType Can_ControllerSettings[CAN_MAX_CONTROLLERS] =
{
	/*controllerID;    isEnabled;      tSeg1;         tSeg2;         sjw;      baudrate;*/
	{    PT  ,          1,          7000,          2000,          2000,     500000,    &IfxMultican_TXD0_P02_5_OUT, &IfxMultican_RXD0A_P02_1_IN }, // CAN0 equ CAN1 in sch
	{    ESP,          1,          7000,          2000,          2000,     500000,     &IfxMultican_TXD1_P00_0_OUT, &IfxMultican_RXD1D_P00_1_IN},  // CAN1 equ CAN2 in sch
	{    CCPCAN,          1,          7000,          2000,          2000,     500000,     &IfxMultican_TXD2_P02_2_OUT, &IfxMultican_RXD2D_P14_8_IN},  // CAN2 equ CAN3 in sch
	{    HV,          1,          7000,          2000,          2000,     500000,   &IfxMultican_TXD3_P00_2_OUT, &IfxMultican_RXD3A_P00_3_IN  }
};
