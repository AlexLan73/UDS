

#ifndef CAN_MESSAGE_STATUS_H
#define CAN_MESSAGE_STATUS_H

enum can_status_e {
	success					= 0x00000000,
	not_initialised			= 0x00000001,
	wrong_param				= 0x00000002,
	pin						= 0x00000004,
	bus_heavy				= 0x00000008,
	bus_off					= 0x00000010,
	not_sent_busy			= 0x00000020,
	receive_empty			= 0x00000040,
	message_lost			= 0x00000080,
	new_data				= 0x00000100,
	new_data_but_one_lost	= message_lost | new_data
};

#endif /* CAN_MESSAGE_STATUS_H */


