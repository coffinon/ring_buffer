/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init (RingBuffer * ringBuffer, char *dataBuffer, size_t dataBufferSize)
{
    assert(ringBuffer);
    
    if (ringBuffer && dataBuffer && dataBufferSize > 0)
    {
        ringBuffer->buffer = dataBuffer;
        
        ringBuffer->capacity = dataBufferSize;
        
        RingBuffer_Clear(ringBuffer);
        
        return true;
    }
    return false;
}

bool RingBuffer_Clear (RingBuffer * ringBuffer)
{
    assert (ringBuffer);

    ringBuffer->head = 0;
    ringBuffer->tail = 0;
    
    ringBuffer->length = 0;
    
    ringBuffer->is_full = false;

    return true;
}

bool RingBuffer_IsEmpty (const RingBuffer * ringBuffer)
{
    assert (ringBuffer);
    
    return ((ringBuffer->head == ringBuffer->tail && !ringBuffer->is_full) ? true : false);
}

size_t RingBuffer_GetLen (const RingBuffer * ringBuffer)
{
    assert (ringBuffer);

    return ringBuffer->length;
}

size_t RingBuffer_GetCapacity (const RingBuffer * ringBuffer)
{
    assert(ringBuffer);
    
    return ringBuffer->capacity;
}


bool RingBuffer_PutChar (RingBuffer * ringBuffer, char c)
{
    assert(ringBuffer);
    
    if(!ringBuffer->is_full)
    {
        ringBuffer->buffer[ringBuffer->head] = c;
        
        ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->capacity;
        ringBuffer->is_full = ringBuffer->head == ringBuffer->tail;
        ringBuffer->length++;
        
        return true;
    }
    
    return false;
}

bool RingBuffer_GetChar (RingBuffer * ringBuffer, char *c)
{
    assert(ringBuffer);
    assert(c);
    
    if(!RingBuffer_IsEmpty(ringBuffer))
    {
        *c = ringBuffer->buffer[ringBuffer->tail];
        ringBuffer->tail++;
        ringBuffer->length--;
        
        if(ringBuffer->tail == ringBuffer->capacity)
            ringBuffer->tail = 0;
        
        ringBuffer->is_full = false;
        return true;
    }
    
    return false;
}
