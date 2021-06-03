/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize) 
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);
	
	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)){
	    ringBuffer->buffer_start=0;
	    ringBuffer->buffer_length=0;
	    ringBuffer->buffer_size=dataBufferSize;
	    ringBuffer->data_buffer=dataBuffer;
	    return true;
	}
	else
	    return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) 
	{
		ringBuffer->buffer_start=0;
		ringBuffer->buffer_length=0;
		for(uint16_t i=0 ; i<ringBuffer->buffer_size; i++)
		    ringBuffer->data_buffer[i]=0;
		return true;    
	}
	else
	    return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
  assert(ringBuffer);
    if(ringBuffer->buffer_length!=0)
        return false;
	else
	    return true;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) 
	{
		return ringBuffer->buffer_length;
	}
	else
	    return 0;
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) 
	{
		return ringBuffer->buffer_size;
	}
	else
	    return 0;	
}


bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);
	
	if (ringBuffer) 
	{   
	    if(ringBuffer->buffer_length==ringBuffer->buffer_size)
	        return false;
	    else{
            ringBuffer->data_buffer[(ringBuffer->buffer_start + ringBuffer->buffer_length)%ringBuffer->buffer_size]=c;
            ringBuffer->buffer_length++;
            return true;
	    }
	}
	
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);
	
  if ((ringBuffer) && (c)) 
    {
	    if(ringBuffer->buffer_length==0)
	        return false;
	    else{
		    *c = ringBuffer->data_buffer[ringBuffer->buffer_start];
		    ringBuffer->buffer_length--;
		    ringBuffer->buffer_start++;
		    if(ringBuffer->buffer_start>=ringBuffer->buffer_size)
		        ringBuffer->buffer_start=0;
		    return true;
	    }
	}
	else
	    return false;
}