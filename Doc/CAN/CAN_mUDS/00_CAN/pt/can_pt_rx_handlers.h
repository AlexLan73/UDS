#ifndef pt_RX_HANDLERS_H
#define pt_RX_HANDLERS_H

#include "Platform_Types.h"
#include "can_initialization.h"
#include "can_frame_structure.h"

extern void TCU_R932_5_handler(struct can_message_s* rx_msg);
extern void TCU_R932_4_handler(struct can_message_s* rx_msg);
extern void TCU_R932_3_handler(struct can_message_s* rx_msg);
extern void TCU_R932_2_handler(struct can_message_s* rx_msg);
extern void HVC_HV_Status_Msg_handler(struct can_message_s* rx_msg);
extern void Diag_To_ECU_handler(struct can_message_s* rx_msg);
extern void CDA_11_handler(struct can_message_s* rx_msg);
extern void VAU_EMS_Hash_Immo_RESP_handler(struct can_message_s* rx_msg);
extern void TCU_R932_1_handler(struct can_message_s* rx_msg);
extern void SAS_Standard_handler(struct can_message_s* rx_msg);
extern void EPB_Status_handler(struct can_message_s* rx_msg);
extern void Diag_Functional_FromPT_handler(struct can_message_s* rx_msg);
extern void DMS_01_handler(struct can_message_s* rx_msg);
extern void CCU_MSG3_handler(struct can_message_s* rx_msg);
extern void CCU_HVC_Req_Msg_handler(struct can_message_s* rx_msg);
extern void BCM_VEH_STATE_handler(struct can_message_s* rx_msg);
extern void BCM_Powertrain_handler(struct can_message_s* rx_msg);
extern void BCM_EEM_handler(struct can_message_s* rx_msg);
extern void ACU_01_handler(struct can_message_s* rx_msg);
#endif
