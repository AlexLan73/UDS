#include "queue.h"

PtQueueType ptQueueRx;
PtQueueType ptQueueTx;

void ptQueueInit(PtQueueType* queue){
    queue->size = 0;
    queue->first = 0;
    queue->last = PT_PAR_QUEUE_SIZE - 1;
}

uint8 ptQueuePut(PtQueueType* queue, uint8* data, uint8 id){
    uint8 retVal  = 1; //full
    if (queue->size < PT_PAR_QUEUE_SIZE){
        queue->last = (queue->last+1)% PT_PAR_QUEUE_SIZE;
        memcpy(queue->data[queue->last].bytes, data, PT_PAR_QUEUE_ELEMENT_SIZE); //dst src len
        queue->data[queue->last].id = id;
        queue->size++;
        retVal = 0;
    }
    return retVal;
}

uint8 ptQueueGet(PtQueueType* queue, uint8* data, uint8* id){
    uint8 retVal  = 1; //empty
    if (queue->size > 0){
        memcpy(data, queue->data[queue->first].bytes, PT_PAR_QUEUE_ELEMENT_SIZE); //dst src len
        *id = queue->data[queue->first].id;
        queue->first = (queue->first+1)% PT_PAR_QUEUE_SIZE;
        queue->size--;
        retVal = 0;
    }
    return retVal;
}

void ptQueueClear(PtQueueType* queue){
    ptQueueInit(queue);
}