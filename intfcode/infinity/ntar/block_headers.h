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

#ifndef __BLOCK_HEADERS_01917326494365654947346436347
#define __BLOCK_HEADERS_01917326494365654947346436347

#include "bittypes.h"

#if defined _MSC_VER
/* this is used to have complete control over the alignment of the structures */
#pragma pack(push)
#pragma pack(1)
#elif defined __MINGW32__
#pragma pack(push, 1)
#else
#pragma pack(push, 1)
#endif

/*!
	brief This structure is the header of a block, 
	as described in the draft.
*/
typedef struct _block_header
{
	/*! Block type
	*/
	u_int32 block_type;			
	/*! Block length, including this header and the trailing 32bits block length.
	*/
	u_int32 block_total_length;	
}
	block_header;

/*! Block type of the section header block
*/
#define SHB_BLOCK_TYPE	0x0A0D0D0A    /*\r\n\n\r*/
//#define SHB_BLOCK_TYPE	0x0A0A0D1A    /*\r\r\n\0x1a*/

/*! Magic of the section header block
	Used to recognize if a section is in host byte order or not.
*/
#define SHB_MAGIC		0x1A2B3C4D

/*!
	This macro tries tries to see if a trace file was wrongly
	downloaded with FTP in ASCII mode between different OSes.
	If a file is downloaded in ASCII mode, the carriage returns
	are converted to the native one of the dest OS:
		- "\\n" on *NIX
		- "\\r\\n" on Windows
		- "\\r" on MAC (what about MAC OS that uses BSD?)
	This macro tries to see if the SBH_BLOCK_TYPE was messed up,
	since its value is a particular combination or \\r and \\n
*/
#define MAYBE_IS_SHB_FTP_MESSED(a)	((((a)&(0xFFFFFF00)) == 0x0D0D0A00) || ((a) == 0x0A0A0D0A))

/*! Major version of the file format supported by this library.
*/
#define CURRENT_MAJOR_VERSION	1

/*! Minor version of the file format supported by this library.
*/
#define CURRENT_MINOR_VERSION	0


/*!
	brief This structure represents a section header block, 
	as described in the draft.
*/
typedef struct _section_header_block
{
	/*! Used to see if the section is in host byte order or not. 
	*/
	u_int32 byte_order_magic;		
	
	/*! Major version of the library used to save this section
	*/
	u_int16	major_version;

	/*! Minor version of the library used to save this section
	*/
	u_int16 minor_version;

	/*! Section length, excluding this section header block, 
		or -1, if the section length is unknown.
	*/
	u_int64 section_length;
}
	section_header_block;

/*!
	Options supported by the section header block
	\note 
	- This list does not include the general options \ref OPTION_ENDOFOPT 
		and \ref OPTION_COMMENT, that are always supported.
	- Further details on these options can be found in the draft.
	
*/
enum
{
	/*! Hardware used to save this capture. The format is a string.
	*/
	SHB_OPTION_HARDWARE		= 2,	

	/*! OS used to save this capture. The format is a string.
	*/
	SHB_OPTION_OS			= 3,

	/*! Application used to save this capture. The format is a string.
	*/
	SHB_OPTION_APPLICATION	= 4
};

/*!
	brief This structure represents a block option, 
	as described in the draft.
*/
typedef struct _option_header
{
	u_int16 option_code;	///< Code of the option.
	u_int16 option_length;	///< Length of the value of the option
}
	option_header;

/*!
	Options supported by all the blocks
	\note Further details on these options can be found in the draft.
	
*/
enum 
{
	/*! Option list terminator
		Both code and length are set to zero.
	*/
	OPTION_ENDOFOPT	= 0,
	
	/*! Generic comment. The format is a string.
	*/
	OPTION_COMMENT	= 1
};

extern const option_header END_OPTION;
/*!
	This macro returns TRUE if the option value passed as parameter
	is the NULL option.
*/
#define IS_END_OPTION(a) (((a).option_code == 0) && ((a).option_length == 0))

#if defined _MSC_VER || defined __MINGW32__ 
/* this is used to have complete control over the alignment of the structures */
#pragma pack(pop)
#else
#pragma pack(pop)
#endif

#endif /*__BLOCK_HEADERS_01917326494365654947346436347*/


