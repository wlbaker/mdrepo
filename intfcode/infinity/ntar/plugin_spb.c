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

#include "ntar.h"
#include "option.h"
#include "plugin_spb_int.h"
#include "plugins_int.h"

#include "memory.h"

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(disable: 4100)
#endif /* _MSC_VER */


int spb_write_data(void *plugin_state, void* data, void* buffer, size_t *buffer_size)
{
	spb_block *block_data;
	ntar_data_chunk *data_chunk;
	size_t requested_size;

	/* the memory requested to the library is two chunks of memory,
	 * one for the spb header, one for the packet itself
	*/
	requested_size = 2* sizeof(ntar_data_chunk);

	if (*buffer_size < requested_size)
	{
		*buffer_size = requested_size;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_size;

	block_data = (spb_block*) data;

    data_chunk = (ntar_data_chunk*)buffer;

	data_chunk[0].data = block_data;
	data_chunk[0].size = SIZEOF_SIMPLE_PACKET_BLOCK;
	data_chunk[0].next = &(data_chunk[1]);
	data_chunk[1].data = block_data->packet_data;
	data_chunk[1].size = block_data->captured_len;
	data_chunk[1].next = NULL;

	return NTAR_SUCCESS;
}

int spb_validate_option(void* plugin_state, ntar_option *option)
{
	return NTAR_FAILURE_INVALID_ID;
}

int spb_write_option(void* plugin_state, ntar_option *option, void* buffer,size_t *buffer_size)
{
	return NTAR_FAILURE_INVALID_ID;
}

int spb_init(void **plugin_state)
{
		return NTAR_SUCCESS;
}

int spb_destroy(void *plugin_state)
{
	return NTAR_SUCCESS;
}

int spb_read_data(void *plugin_state, int byte_order, void *raw_data, size_t raw_data_size, void** data_buffer, size_t *pbuffer_size, size_t *poption_start)
{
	spb_block *spb;

	if(raw_data_size < SIZEOF_SIMPLE_PACKET_BLOCK)
		return NTAR_FAILURE_MALFORMED_BLOCK;

	if (*pbuffer_size < sizeof(spb_block))
	{
        *pbuffer_size = sizeof(spb_block);
		return NTAR_FAILURE_SMALLBUFFER;
	}

	memcpy(*data_buffer, raw_data, SIZEOF_SIMPLE_PACKET_BLOCK);

    spb = (spb_block*) *data_buffer;
	if (byte_order != HOST_BYTE_ORDER)
	{
		spb->packet_len = NTAR_SWAP_32BITS(spb->packet_len);
	}
	spb->captured_len = (u_int32)(raw_data_size - SIZEOF_SIMPLE_PACKET_BLOCK);
	spb->packet_data = (char*)raw_data + SIZEOF_SIMPLE_PACKET_BLOCK;

	*poption_start = raw_data_size;

	return NTAR_SUCCESS;
}

int spb_read_option(void *plugin_state, option_header* oh, int byte_order, void* opt_buffer, size_t *pbuffer_size)
{
	return NTAR_FAILURE_INVALID_ID;
}

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(default: 4100)
#endif /* _MSC_VER */
