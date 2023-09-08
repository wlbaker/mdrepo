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
#include "option.h"

const option_header END_OPTION = {0,0};

int write_null_option(void *buffer, size_t *buffer_size)
{

	if (*buffer_size < sizeof(END_OPTION) || buffer == NULL)
	{
		*buffer_size = sizeof(END_OPTION);
		return NTAR_FAILURE_SMALLBUFFER;
	}

	memcpy(buffer, &END_OPTION, sizeof(END_OPTION));

	*buffer_size = sizeof(END_OPTION);
	return NTAR_SUCCESS;
}

int write_option_string(ntar_option *option, void* buffer,size_t *buffer_size)
{
	/* ok, data is a NULL terminated string */
	option_header opt;
	size_t requested_len;
	int align_bytes;
	size_t string_len;
	char *buffer_char;

	buffer_char = (char*)buffer;

	/* +1 is used for the trailing \0 */
	string_len = strlen(option->data) + 1;

	requested_len = sizeof(option_header) + NTAR_ALIGN_32BITS(string_len);

	if (requested_len > *buffer_size || buffer == NULL)
	{
		*buffer_size = requested_len;
		return NTAR_FAILURE_SMALLBUFFER;
	}
	
	*buffer_size = requested_len;

	opt.option_code = option->code;
	opt.option_length = (u_int16)(string_len); 
	align_bytes = NTAR_ALIGN_32BITS(opt.option_length) - opt.option_length;

	memcpy(buffer_char, &opt, sizeof(opt));
	buffer_char += sizeof(opt);
	
	memcpy(buffer_char, option->data, string_len);
	buffer_char += string_len;

	if (align_bytes > 0)
		memset(buffer_char, 0, align_bytes);

	return NTAR_SUCCESS;
}

int write_option_uint64(ntar_option *option, void* buffer,size_t *buffer_size)
{
	option_header opt;
	size_t requested_len;
	char* buffer_char;

	buffer_char = (char*) buffer;

	requested_len = sizeof(u_int64) + sizeof(option_header);
	if (*buffer_size < requested_len)
	{
		*buffer_size = requested_len;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_len;
	
	opt.option_code = option->code;
	opt.option_length = sizeof(u_int64);

	memcpy(buffer_char, &opt, sizeof(opt));
	buffer_char += sizeof(opt);

	memcpy(buffer_char, option->data, sizeof(u_int64));

	return NTAR_SUCCESS;
}

int write_option_uint32(ntar_option *option, void* buffer,size_t *buffer_size)
{
	option_header opt;
	size_t requested_len;
	char* buffer_char;

	buffer_char = (char*) buffer;

	requested_len = sizeof(u_int32) + sizeof(option_header);
	if (*buffer_size < requested_len)
	{
		*buffer_size = requested_len;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_len;
	
	opt.option_code = option->code;
	opt.option_length = sizeof(u_int32);

	memcpy(buffer_char, &opt, sizeof(opt));
	buffer_char += sizeof(opt);

	memcpy(buffer_char, option->data, sizeof(u_int32));

	return NTAR_SUCCESS;
}

int write_option_raw(ntar_option *option, void *buffer, size_t *buffer_size, void* raw_data, u_int16 raw_data_size)
{
	option_header opt;
	size_t requested_len;
	char* buffer_char;

	buffer_char = (char*) buffer;

	requested_len = sizeof(option_header) + NTAR_ALIGN_32BITS(raw_data_size);
	if (*buffer_size < requested_len)
	{
		*buffer_size = requested_len;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_len;
	
	opt.option_code = option->code;
	opt.option_length = raw_data_size;

	memcpy(buffer_char, &opt, sizeof(opt));
	buffer_char += sizeof(opt);

	memcpy(buffer_char, raw_data, raw_data_size);

	return NTAR_SUCCESS;
}
