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

#ifndef __PLUGIN_IDB_08344321238733474389747
#define __PLUGIN_IDB_08344321238733474389747

#include "bittypes.h"

#if defined _MSC_VER
/* this is used to have complete control over the alignment of the structures */
#pragma pack(push)
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

#define BLOCK_ID_IDB	0x00000001

typedef struct _interface_description_block
{
	u_int16	link_type;
	u_int16 reserved;
	u_int32 snaplen;
}
	interface_description_block;

typedef struct _idb_ipv4_addr
{
	u_int32 ipv4_addr;
	u_int32 ipv4_netmask;
}
	idb_ipv4_addr;

typedef struct _idb_ipv6_addr
{
	u_int8 ipv6_addr[16];
	u_int8 ipv6_prefix_len;
}
	idb_ipv6_addr;


enum 
{
	IDB_OPTION_IF_NAME			= 2,
	IDB_OPTION_IF_DESCRIPTION	= 3,
	IDB_OPTION_IF_IPV4ADDR		= 4,
	IDB_OPTION_IF_IPV6ADDR		= 5,
	IDB_OPTION_IF_MACADDR		= 6,
	IDB_OPTION_IF_EUIADDR		= 7,
	IDB_OPTION_IF_SPEED			= 8,
	IDB_OPTION_IF_TSACCUR		= 9,
	IDB_OPTION_IF_TZONE			= 10,
	IDB_OPTION_IF_FILTER		= 11,
	IDB_OPTION_IF_OS			= 12,
	IDB_OPTION_IF_FCSLEN		= 13
};

#if defined _MSC_VER || defined __MINGW32__ 
/* this is used to have complete control over the alignment of the structures */
#pragma pack(pop)
#else  /* defined _MSC_VER || defined __MINGW32__  */
#pragma pack(pop)
#endif /* defined _MSC_VER || defined __MINGW32__ */

#endif /* __PLUGIN_IDB_08344321238733474389747 */
