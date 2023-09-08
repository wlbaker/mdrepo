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

ntar_plugin_data ntar_plugins[] =
{
	{
		BLOCK_ID_IDB, 
		idb_init,
		idb_destroy,
		idb_write_data, 
		idb_write_option,
		idb_validate_option,
		idb_read_data,
		idb_read_option
	},
	
	{
		BLOCK_ID_PKTB, 
		pkt_init,
		pkt_destroy,
		pkt_write_data, 
		pkt_write_option,
		pkt_validate_option,
		pkt_read_data,
		pkt_read_option
	},
	
	{
		BLOCK_ID_SPB, 
		spb_init,
		spb_destroy,
		spb_write_data, 
		spb_write_option,
		spb_validate_option,
		spb_read_data,
		spb_read_option
	},
	
	/****************************************************
	* other plugin registrations go here, in this form  *
	*													*
	*	{												*
	*		identifier,									*
	*		fcn to init plugin,							*
	*		fcn to destroy plugin,						*
	*		fcn to write block data,					*
	*		fcn to write option,						*
	*		fcn to read block data,						*
	*		fcn to read options							*
	*	};												*
	*****************************************************/
};


ntar_plugin_data* get_plugin_data(u_int32 block_type)
{
	size_t num_plugins;
	size_t i;
	ntar_plugin_data *ret_value = NULL;

	num_plugins = sizeof(ntar_plugins)/sizeof(ntar_plugins[0]);

	for( i = 0; i < num_plugins ; i++)
	{
		if (ntar_plugins[i].block_type == block_type)
			ret_value = ntar_plugins + i;
	}

	return ret_value;
}

