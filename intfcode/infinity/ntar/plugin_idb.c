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
#include "ntar_debug.h"
#include "option.h"
#include "plugin_idb_int.h"
#include "plugins_int.h"
#include "memory.h"

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(disable: 4100)
#endif /* _MSC_VER */

int idb_write_option(void *status, ntar_option *option, void* buffer,size_t *buffer_size)
{
	switch(option->code)
	{
	case IDB_OPTION_IF_FILTER:
	case IDB_OPTION_IF_NAME:		
	case IDB_OPTION_IF_DESCRIPTION:
	case IDB_OPTION_IF_OS:
		return write_option_string(option, buffer, buffer_size);
		
	case IDB_OPTION_IF_SPEED:
		return write_option_uint64(option, buffer, buffer_size);

	case IDB_OPTION_IF_IPV4ADDR:
			return write_option_raw(option, buffer, buffer_size, option->data, sizeof(idb_ipv4_addr));

	case IDB_OPTION_IF_IPV6ADDR:
			return write_option_raw(option, buffer, buffer_size, option->data, sizeof(idb_ipv6_addr));

	case IDB_OPTION_IF_MACADDR:
		return write_option_raw(option, buffer, buffer_size, option->data, sizeof(char[6]));

	case IDB_OPTION_IF_EUIADDR:
		return write_option_raw(option, buffer, buffer_size, option->data, sizeof(char[8]));

	case IDB_OPTION_IF_FCSLEN:
	case IDB_OPTION_IF_TSACCUR:
		return write_option_raw(option, buffer, buffer_size, option->data, sizeof(char));

	case IDB_OPTION_IF_TZONE:
		return write_option_uint32(option, buffer, buffer_size);

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

int idb_validate_option(void *status, ntar_option *option)
{
	switch(option->code)
	{
	case IDB_OPTION_IF_NAME:		
	case IDB_OPTION_IF_DESCRIPTION:
	case IDB_OPTION_IF_OS:
	case IDB_OPTION_IF_SPEED:
	case IDB_OPTION_IF_IPV4ADDR:
	case IDB_OPTION_IF_IPV6ADDR:
	case IDB_OPTION_IF_MACADDR:
	case IDB_OPTION_IF_EUIADDR:
	case IDB_OPTION_IF_TSACCUR:
	case IDB_OPTION_IF_TZONE:
	case IDB_OPTION_IF_FILTER:
	case IDB_OPTION_IF_FCSLEN:
		return NTAR_SUCCESS;

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

int idb_init(void **status)
{
	return NTAR_SUCCESS;
}

int idb_destroy(void *status)
{
	return NTAR_SUCCESS;
}


int idb_read_data(void *state, int byte_order, void *raw_data, size_t raw_data_size, void** data_buffer, size_t *pbuffer_size, size_t *poption_start)
{
	interface_description_block *idb;

	if(raw_data_size < sizeof(interface_description_block))
		return NTAR_FAILURE_MALFORMED_BLOCK;

	*pbuffer_size = 0;

	idb = (interface_description_block*) raw_data;
	if (byte_order != HOST_BYTE_ORDER)
	{
		idb->link_type = NTAR_SWAP_16BITS(idb->link_type);
		idb->snaplen = NTAR_SWAP_32BITS(idb->snaplen);
	}
	
	*data_buffer = (char*)idb;
	*poption_start = sizeof(interface_description_block);

	return NTAR_SUCCESS;
}

int idb_read_option(void *plugin_state, option_header* oh, int byte_order, void* opt_buffer, size_t *pbuffer_size)
{
	switch(oh->option_code)
	{
	case IDB_OPTION_IF_FILTER:
	case IDB_OPTION_IF_DESCRIPTION:
	case IDB_OPTION_IF_NAME:
	case IDB_OPTION_IF_OS:
		return read_option_string(
			oh, 
			byte_order,
			opt_buffer, 
			pbuffer_size);

	case IDB_OPTION_IF_SPEED:
		return read_option_uint64(
			oh, 
			byte_order,
			opt_buffer, 
			pbuffer_size);

	case IDB_OPTION_IF_IPV4ADDR:
		{
			int return_code;

			NTAR_ASSERT(oh->option_length == sizeof(idb_ipv4_addr), __FUNCTION__ " the size of IDB_OPTION_IF_IPV4ADDR option is invalid");
			return_code = read_option_raw(
				oh,
				byte_order,
				opt_buffer,
				pbuffer_size);

			if (return_code == NTAR_SUCCESS)
			{
				if (byte_order == SWAPPED_HOST_BYTE_ORDER)
				{
					idb_ipv4_addr *addr;
					
					addr = (idb_ipv4_addr*)opt_buffer;
					addr->ipv4_addr = NTAR_SWAP_32BITS(addr->ipv4_addr);
					addr->ipv4_netmask = NTAR_SWAP_32BITS(addr->ipv4_netmask);
				}
			}
			return return_code;
		}

	case IDB_OPTION_IF_IPV6ADDR:
		NTAR_ASSERT(oh->option_length == sizeof(idb_ipv6_addr), __FUNCTION__ " the size of IDB_OPTION_IF_IPV6ADDR option is invalid");
		return read_option_raw(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);


	case IDB_OPTION_IF_MACADDR:
		NTAR_ASSERT(oh->option_length == sizeof(u_int8[6]), __FUNCTION__ " the size of IDB_OPTION_IF_MACADDR option is invalid");
		return read_option_raw(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);

	case IDB_OPTION_IF_EUIADDR:
		NTAR_ASSERT(oh->option_length == sizeof(u_int8[8]), __FUNCTION__ " the size of IDB_OPTION_IF_EUIADDR option is invalid");
		return read_option_raw(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);

	case IDB_OPTION_IF_TSACCUR:
		NTAR_ASSERT(oh->option_length == sizeof(u_int8), __FUNCTION__ " the size of IDB_OPTION_IF_TSACCUR option is invalid");
		return read_option_raw(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);

	case IDB_OPTION_IF_TZONE:
		return read_option_uint32(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);

	case IDB_OPTION_IF_FCSLEN:
		NTAR_ASSERT(oh->option_length == sizeof(u_int8), __FUNCTION__ " the size of IDB_OPTION_IF_FCSLEN option is invalid");
		return read_option_raw(
			oh,
			byte_order,
			opt_buffer,
			pbuffer_size);

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

int idb_write_data(void *plugin_status, void* data, void* buffer, size_t *buffer_size)
{
	interface_description_block *block_data;
	ntar_data_chunk *data_chunk;
	size_t requested_size;

	/* the memory requested to the library is only for a single chunk of memory */
	requested_size = sizeof(ntar_data_chunk);

	if (*buffer_size < requested_size)
	{
		*buffer_size = requested_size;
		return NTAR_FAILURE_SMALLBUFFER;
	}

	*buffer_size = requested_size;

	block_data = (interface_description_block*) data;

	data_chunk = (ntar_data_chunk*)buffer;

	data_chunk->data = data;
	data_chunk->size = sizeof(interface_description_block);
	data_chunk->next = NULL;

	return NTAR_SUCCESS;
}

#ifdef _MSC_VER
/* this is used to avoid a Visual C warning on /W4 about unused parameters */
#pragma warning(default: 4100)
#endif /* _MSC_VER */
