/*
 * Copyright (c) 2005, Condor Engineering, Inc. 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Company (Condor Engineering, Inc) nor the
 * names of its contributors may be used to endorse or promote products 
 * derived from this software without specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/*
 * Author: Gianluca Varenni <gianluca.varenni@gmail.com>
 */

#include "ntar_int.h"

#include "plugins_int.h"
#include "option.h"

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(disable: 4100)
#endif /* _MSC_VER */

int read_option_string(option_header *oh, int byte_order, void* buffer, size_t *buffer_length)
{
	/* ok, data is a NULL terminated string */
	if (oh->option_length > *buffer_length || buffer == NULL)
	{
		*buffer_length = oh->option_length;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	memcpy(buffer, (char*)oh + sizeof(option_header), oh->option_length);

	*buffer_length = oh->option_length;
	return NTAR_SUCCESS;
}

int read_option_uint64(option_header *oh, int byte_order, void* buffer, size_t *buffer_length)
{
	NTAR_ASSERT(oh->option_length == sizeof(u_int64), __FUNCTION__ " the size of the option is invalid");
	//TODO check for alignments??
	
	/* ok, data is a NULL terminated string */
	if (oh->option_length > *buffer_length)
	{
		*buffer_length = oh->option_length;
		return NTAR_FAILURE_SMALLBUFFER;
	}
	
	memcpy(buffer, (char*)oh + sizeof(option_header), sizeof(u_int64));

	if (byte_order != HOST_BYTE_ORDER)
	{
			*((u_int64*)buffer) = NTAR_SWAP_64BITS(*((u_int64*)buffer));
	}

	*buffer_length = oh->option_length;

	return NTAR_SUCCESS;
}

int read_option_uint32(option_header *oh, int byte_order, void* buffer, size_t *buffer_length)
{
	NTAR_ASSERT(oh->option_length == sizeof(u_int32), __FUNCTION__ " the size of the option is invalid");
	//TODO check for alignments??
	
	/* ok, data is a NULL terminated string */
	if (oh->option_length > *buffer_length)
	{
		*buffer_length = oh->option_length;
		return NTAR_FAILURE_SMALLBUFFER;
	}
	
	memcpy(buffer, (char*)oh + sizeof(option_header), sizeof(u_int64));

	if (byte_order != HOST_BYTE_ORDER)
	{
			*((u_int32*)buffer) = NTAR_SWAP_32BITS(*((u_int32*)buffer));
	}

	*buffer_length = oh->option_length;

	return NTAR_SUCCESS;
}

int read_option_raw(option_header *oh, int byte_order, void* buffer, size_t *buffer_length)
{
	//TODO check for alignments??
	
	if (oh->option_length > *buffer_length)
	{
		*buffer_length = oh->option_length;
		return NTAR_FAILURE_SMALLBUFFER;
	}
	
	//we do not swap anything!
	
	memcpy(buffer, (char*)oh + sizeof(option_header), oh->option_length);

	*buffer_length = oh->option_length;

	return NTAR_SUCCESS;
}





#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(disable: 4100)
#endif /* _MSC_VER */
