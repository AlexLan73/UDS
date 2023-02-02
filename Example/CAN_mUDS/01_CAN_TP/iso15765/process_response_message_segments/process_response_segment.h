#ifndef PROCESS_CAN_TP_RESPONSE_H
#define PROCESS_CAN_TP_RESPONSE_H

#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"

/*!
\brief short discr

full discr

\param[in]
\param[in]
\return
*/

extern void can_tp_iso15765_send_message_segments(void);

/*
\brief prepares data for segmentation (if one is needed) and transfer by CAN

full discr

\param[in]
\return
*/
extern void can_tp_write(struct iso15765_tp_s* responce_instance);

/*!
\brief short discr

full discr

\param[in]
\param[in]
\return
 */
extern struct iso15765_tp_s* get_iso15765_tp_response_instance_for(uint32 can_id);

/*!
\brief short discr

full discr

\param[in]
\param[in]
\return
 */
extern boolean release_iso15765_tp_response_instance(struct iso15765_tp_s* can_tp_response_instance_p);

#endif /* PROCESS_CAN_TP_RESPONSE_H */
