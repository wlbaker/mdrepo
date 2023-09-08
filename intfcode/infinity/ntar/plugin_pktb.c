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
#include "plugin_pktb_int.h"
#include "plugins_int.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(disable: 4100)
#endif /* _MSC_VER */

int pkt_write_data(void *plugin_status, void* data, void* buffer, size_t *buffer_size)
{
	pkt_block *block_data;
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

	block_data = (pkt_block*) data;

    data_chunk = (ntar_data_chunk*)buffer;

	data_chunk[0].data = block_data;
	data_chunk[0].size = SIZEOF_PACKET_BLOCK;
	data_chunk[0].next = &(data_chunk[1]);
	data_chunk[1].data = block_data->packet_data;
	data_chunk[1].size = block_data->captured_len;
	data_chunk[1].next = NULL;

	return NTAR_SUCCESS;
}

int pkt_init(void **plugin_handle)
{
	return NTAR_SUCCESS;
}

int pkt_destroy(void *plugin_handle)
{
	return NTAR_SUCCESS;
}

int pkt_validate_option(void *plugin_handle, ntar_option *option)
{
	switch(option->code)
	{
	case PKTB_OPTION_FLAGS:
		return NTAR_SUCCESS;

	case PKTB_OPTION_HASH:
	default:
		/* TODO */
		return NTAR_FAILURE_INVALID_ID;
	}
}

int pkt_write_option(void *plugin_handle, ntar_option *option, void* buffer, size_t *buffer_size)
{
	
	switch(option->code)
	{
	case PKTB_OPTION_FLAGS:
		return write_option_uint32(option, buffer, buffer_size);
	
	case PKTB_OPTION_HASH:
		/* TODO */
		return NTAR_FAILURE_INVALID_ID;

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

int pkt_read_data(void *state, int byte_order, void *raw_data, size_t raw_data_size, void** data_buffer, size_t *pbuffer_size, size_t *poptions_start)
{
	pkt_block *block_data;
	pkt_block *user_block_data;
	u_int32 captured_len;

	if (raw_data_size < SIZEOF_PACKET_BLOCK)
		return NTAR_FAILURE_MALFORMED_BLOCK;

	block_data = (pkt_block*)raw_data;

	if (byte_order != HOST_BYTE_ORDER)
	{
		captured_len = NTAR_SWAP_32BITS(block_data->captured_len);
	}
	else
		captured_len = block_data->captured_len;

	if (captured_len + SIZEOF_PACKET_BLOCK > raw_data_size)
		return NTAR_FAILURE_MALFORMED_BLOCK;

	if (*pbuffer_size < sizeof(pkt_block))
	{
		*pbuffer_size = sizeof(pkt_block);
		return NTAR_FAILURE_SMALLBUFFER;
	}

	if (byte_order != HOST_BYTE_ORDER)
	{
		block_data->captured_len = NTAR_SWAP_32BITS(block_data->captured_len);
		block_data->drops_count = NTAR_SWAP_16BITS(block_data->drops_count);
		block_data->interface_id = NTAR_SWAP_16BITS(block_data->interface_id);
		block_data->packet_len = NTAR_SWAP_32BITS(block_data->packet_len);
		block_data->timestamp_high = NTAR_SWAP_32BITS(block_data->timestamp_high);
		block_data->timestamp_low = NTAR_SWAP_32BITS(block_data->timestamp_low);
	}
	
	user_block_data = (pkt_block*)*data_buffer;

	*user_block_data = *block_data;
	user_block_data->packet_data = (char*)raw_data + SIZEOF_PACKET_BLOCK;

	*pbuffer_size = sizeof(pkt_block);
	
	*poptions_start = NTAR_ALIGN_32BITS(SIZEOF_PACKET_BLOCK + block_data->captured_len);

	return NTAR_SUCCESS;
}


int pkt_read_option(void *plugin_data, option_header *option, int byte_order, void *opt_buffer, size_t *pbuffer_size)
{
	
	switch(option->option_code)
	{
	case PKTB_OPTION_FLAGS:
		return read_option_uint32(
			option, 
			byte_order,
			opt_buffer, 
			pbuffer_size);

	case PKTB_OPTION_HASH:
		/* TODO */
		return NTAR_FAILURE_INVALID_ID;

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(default: 4100)
#endif /* _MSC_VER */

