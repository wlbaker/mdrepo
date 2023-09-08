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

#ifndef __PLUGIN_PKTB_INT_12348484
#define __PLUGIN_PKTB_INT_12348484

#include "plugin_pktb.h"

/*! this define is used to get rid of the trailing void at the end of the structure */
#define SIZEOF_PACKET_BLOCK			(sizeof(pkt_block) - sizeof(void*))

#define DEFAULT_PKTB_PACKET_SIZE	2048

typedef struct _pkt_data_int
{
	pkt_block	data;
	size_t		pkt_size;
}
	pkt_data_int;

int pkt_init(void **plugin_state);
int pkt_destroy(void *plugin_state);
int pkt_write_data(void *plugin_state, void* data, void* buffer, size_t *buffer_size);
int pkt_write_option(void *plugin_state, ntar_option *option, void* buffer, size_t *buffer_size);
int pkt_read_data(void *state, int byte_order, void *raw_data, size_t raw_data_size, void** data_buffer, size_t *pbuffer_size, size_t *poption_start);
int pkt_read_option(void *plugin_state, option_header*, int byte_order, void* opt_buffer, size_t *pbuffer_size);
int pkt_validate_option(void *plugin_handle, ntar_option *option);

#endif /* __PLUGIN_PKTB_12348484 */
