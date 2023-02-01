#ifndef WRITE_DATA_BY_ID_PRIVATE_H
#define WRITE_DATA_BY_ID_PRIVATE_H

#include "write_data_by_id.h"

#define WR_BY_ID_LENGTH 4
#define WR_BY_ID_MIN_MESSAGE_LENGTH	4

static uint8 total_length_is_correct(uint16 data_id, struct iso15765_tp_s* request_message);
static uint8 support_by_active_session(uint16 data_id);
static uint8 security_access_granted(uint16 data_id);
static uint8 check_conditions(void);
static uint8 data_is_valid(struct iso15765_tp_s* request_message);
static uint8 write_data_by_id_complete(uint16 data_id, struct iso15765_tp_s* request_message);

#endif /* WRITE_DATA_BY_ID_PRIVATE_H */
