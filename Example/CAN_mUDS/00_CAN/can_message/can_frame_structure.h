

#ifndef CAN_MESSAGE_STRUCTURE_H
#define CAN_MESSAGE_STRUCTURE_H


struct can_message_s {
    uint32		id;
    uint8		length;

    union d_u {
	    uint32	word[2];
	    uint8	byte[8];
    } data;
};


#endif /* CAN_MESSAGE_STRUCTURE_H */

