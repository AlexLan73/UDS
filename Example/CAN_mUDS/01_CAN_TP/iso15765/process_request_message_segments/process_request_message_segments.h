#ifndef PROCESS_CAN_TP_REQUEST_H
#define PROCESS_CAN_TP_REQUEST_H

#include "Platform_Types.h"
#include "can_tp_iso15765_parameters.h"

/*!
\brief short description

full description

\param[in] cm can message -
\param[in] req_m request message -
\return
 */
extern void can_tp_read_segment(uint32 can_id);

/*!
\brief short description

full description

*/
extern struct iso15765_tp_s* get_iso15765_tp_request_instance(uint32 can_id);

/*!
\brief short description

full description

*/
extern boolean release_iso15765_tp_request_instance(struct iso15765_tp_s* can_tp_request_instance_p);

#endif /* PROCESS_CAN_TP_REQUEST_H */
