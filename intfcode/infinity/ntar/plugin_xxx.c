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
#include "option_writers.h"
#include "plugin_xxx_int.h"

int xxx_write_data(void *plugin_state, void* data, char* buffer, size_t *buffer_size)
{
/*
	xxx_block *block_data;
	ntar_data_chunk *data_chunk;
	size_t requested_size;

	/ * the memory requested to the library is two chunks of memory,
	/ * one for the spb header, one for the packet itself
	/ * 
	requested_size = 2* sizeof(ntar_data_chunk);

	if (*buffer_size < requested_size)
	{
		*buffer_size = requested_size;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_size;

	block_data = (xxx_block*) data;

    data_chunk = (ntar_data_chunk*)buffer;

	data_chunk[0].data = block_data;
	data_chunk[0].size = sizeof(xxx_block);
	data_chunk[0].next = &(data_chunk[1]);
	data_chunk[1].data = ??something else??;
	data_chunk[1].size = length_of(something else);
	data_chunk[1].next = NULL;

	return NTAR_SUCCESS;
*/
}

int xxx_validate_option(void* plugin_state, ntar_option *option)
{
/*
	switch(option->code)
	{
	case XXX_OPTION_FOO:
		return NTAR_SUCCESS;

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
*/
}

int xxx_write_option(void* plugin_state, ntar_option *option, void* buffer,size_t *buffer_size)
{
/*
	switch(option->code)
	{
	case XXX_OPTION_FOO:
		return write_option_uint32(option, buffer, buffer_size);
	
	default:
		return NTAR_FAILURE_INVALID_ID;
	}
*/
}

int xxx_init(void **plugin_state)
{
/*
	return NTAR_SUCCESS;
*/
}

int xxx_destroy(void **plugin_state)
{
/*
	return NTAR_SUCCESS;
*/
}

int xxx_read_data(void *plugin_state, void** data)
{
	//spb_data_int *bdata;
	//fpos_t current_position;
	//u_int32 supposed_packet_size;

	//bdata = (spb_data_int*)block_handle->plugin_status;

	//if (fgetpos(block_handle->file_pointer, &current_position) != 0)
	//	return NTAR_FAILURE_IOREAD;

	//if (fread(&(bdata->data), 1, SIZEOF_SIMPLE_PACKET_BLOCK, block_handle->file_pointer) == 0)
	//	return NTAR_FAILURE_IOREAD;

	//if (block_handle->section_handle->byte_order != HOST_BYTE_ORDER)
	//{
	//	bdata->data.packet_len = NTAR_SWAP_32BITS(bdata->data.packet_len);
	//}
	//
	///* TODO I don't know how to deal with this */
	//bdata->data.captured_len = 0;

	///* we suppose the size of the packet is block_size - sizeof(block_header)...*/
	//supposed_packet_size = block_handle->bh.block_total_length 
	//	- sizeof(block_header)
	//	- sizeof(u_int32);

	//if (supposed_packet_size > 0)
	//{
	//	if (bdata->pkt_size < supposed_packet_size)
	//	{
	//		spb_data_int* new_buffer;

	//		new_buffer = (spb_data_int*) malloc(sizeof(spb_data_int) + supposed_packet_size);
	//		if (new_buffer == NULL)
	//			return NTAR_FAILURE_NOMEM;

	//		new_buffer->data = bdata->data;
	//		new_buffer->pkt_size = supposed_packet_size;
	//		new_buffer->data.packet_data = ((char*)new_buffer) + sizeof(spb_data_int);
	//	}
	//	
	//	if (fread(bdata->data.packet_data, 1, supposed_packet_size, block_handle->file_pointer) != 0)
	//		return NTAR_FAILURE_IOREAD;
	//}

	//if (fsetpos(block_handle->file_pointer, &current_position) != 0)
	//	return NTAR_FAILURE_IOREAD;

	//*data = bdata;

	return NTAR_SUCCESS;
}

int xxx_read_option(void *plugin_state, option_header *oh, char* opt_buffer, size_t *pbuffer_size)
{
	/*
	return NTAR_FAILURE_INVALID_ID;
	*/
}
