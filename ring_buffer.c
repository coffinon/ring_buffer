/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init (RingBuffer * ringBuffer, char *dataBuffer, size_t dataBufferSize)
{
  if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0))
    {
      // Initialize base buffer pointer
      ringBuffer->bufBaseAddr = dataBuffer;
      // Initialize buffer head and tail values
      ringBuffer->bufHead = 0;
      ringBuffer->bufTail = 0;
      // Initialize buffer length and capacity values
      ringBuffer->bufCount = 0;
      ringBuffer->bufCapacity = dataBufferSize;

      return true;
    }

  return false;
}

bool RingBuffer_Clear (RingBuffer * ringBuffer)
{
  if (ringBuffer)
    {
      // Clear buffer head and tail values
      ringBuffer->bufHead = 0;
      ringBuffer->bufTail = 0;
      // Clear buffer length
      ringBuffer->bufCount = 0;

      return true;
    }
  return false;
}

bool RingBuffer_IsEmpty (const RingBuffer * ringBuffer)
{
  // Check if buffer is empty
  if (ringBuffer->bufCount)
    return false;

  return true;
}

size_t RingBuffer_GetLen (const RingBuffer * ringBuffer)
{
  if (ringBuffer)
    {
      // Return buffer length
      return (ringBuffer->bufCount);
    }

  return 0;
}

size_t RingBuffer_GetCapacity (const RingBuffer * ringBuffer)
{
  if (ringBuffer)
    {
      // Return buffer capacity 
      return (ringBuffer->bufCapacity);
    }
  return 0;
}


bool RingBuffer_PutChar (RingBuffer * ringBuffer, char c)
{
  if (ringBuffer)
  {
    // Create temporary variables storing head address and end of buffer address
    char *ptemp1 = &ringBuffer->bufBaseAddr[ringBuffer->bufHead];
    char *ptemp2 = &ringBuffer->bufBaseAddr[ringBuffer->bufCapacity];
    // Check if buffer head does not exceed end of buffer
    if (ptemp1 < ptemp2)
	{
	  // Put char in the buffer and increment buffer head address
	  *(ringBuffer->bufBaseAddr + ringBuffer->bufHead++) = c;
	  // Increment buffer length
	  ringBuffer->bufCount++;

	  return true;
	}
	// If it exceeds start storing values from starting address
	else if(ringBuffer->bufCount < ringBuffer->bufCapacity)
	{
	  // Clear buffer head value
	  ringBuffer->bufHead = 0;
	  // Put char in the buffer
	  *(ringBuffer->bufBaseAddr + ringBuffer->bufHead) = c;
	  // Increment buffer length
	  ringBuffer->bufCount++;
	  
	  return true;
	}
  }
  return false;
}

bool RingBuffer_GetChar (RingBuffer * ringBuffer, char *c)
{
  if ((ringBuffer) && (c))
    {
      // Create temporary variables storing head address and end of buffer address
      char *ptemp1 = &ringBuffer->bufBaseAddr[ringBuffer->bufTail];
      char *ptemp2 = &ringBuffer->bufBaseAddr[ringBuffer->bufCapacity];
      // Check if buffer tail does not exceed end of buffer
      if (ptemp1 < ptemp2)
	  {
	    // Pull char from the buffer and increment buffer tail address
	    *c = *(ringBuffer->bufBaseAddr + ringBuffer->bufTail++);
	    // Decrement buffer length
	    ringBuffer->bufCount--;

	    return true;
	  }
	  // If it exceeds start extracting values from starting address
	  else if(ringBuffer->bufCount > 0)
	  {
	    // Clear buffer tail value
	    ringBuffer->bufTail = 0;
	    // Pull char from the buffer
	    *c = *(ringBuffer->bufBaseAddr + ringBuffer->bufTail);
	    // Decrement buffer length
	    ringBuffer->bufCount--;
	  
	    return true;
	  }
    }
  return false;
}
