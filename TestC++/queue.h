#ifndef _SELF_QUEUE_
#define _SELF_QUEUE_

/* = CAN message size */
#define PT_PAR_QUEUE_ELEMENT_SIZE (8u)

#define PT_PAR_QUEUE_SIZE (20u)

typedef struct{
    uint8 bytes[PT_PAR_QUEUE_ELEMENT_SIZE];
    uint8 id;
}PtPacket;

typedef struct {
    PtPacket data[PT_PAR_QUEUE_SIZE];
    uint8 size;
    uint8 first;
    uint8 last;
} PtQueueType;

extern PtQueueType ptQueueRx;
extern PtQueueType ptQueueTx;

#endif /* _SELF_QUEUE_ */