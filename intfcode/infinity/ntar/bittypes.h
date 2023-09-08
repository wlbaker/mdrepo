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

#ifndef __BITTYPES_11263484553478329233663473
#define __BITTYPES_11263484553478329233663473

#include <stdio.h>

#ifndef TRUE
#define TRUE (1==1)
#define FALSE  (1==0)
#endif /* TRUE */

#define HOST_BYTE_ORDER			0
#define SWAPPED_HOST_BYTE_ORDER	1

#define NTAR_ALIGN_XBYTES(a, bytes) (((a) + (bytes-1)) & (~(bytes-1)))	///< Macro used to align an integer to x bytes in excess.

#define NTAR_ALIGN_32BITS(a) NTAR_ALIGN_XBYTES(a,4)	///< Macro used to align an integer to 32 bits in excess.
#define NTAR_ALIGN_64BITS(a) NTAR_ALIGN_XBYTES(a,8)	///< Macro used to align an integer to 64 bits in excess.

#define NTAR_ALIGN_NATIVE(a) NTAR_ALIGN_XBYTES(a, sizeof(void*))

#ifdef _MSC_VER

#define NTAR_SWAP_64BITS(a)	(\
								(((a) & 0xFF00000000000000) >> 56) +\
								(((a) & 0x00FF000000000000) >> 40) +\
								(((a) & 0x0000FF0000000000) >> 24) +\
								(((a) & 0x000000FF00000000) >> 8) +\
								(((a) & 0x00000000FF000000) << 8) +\
								(((a) & 0x0000000000FF0000) << 24) +\
								(((a) & 0x000000000000FF00) << 40) +\
								(((a) & 0x00000000000000FF) << 56)\
							)

#else

#define NTAR_SWAP_64BITS(a)	(\
								(((a) & 0xFF00000000000000LL) >> 56) +\
								(((a) & 0x00FF000000000000LL) >> 40) +\
								(((a) & 0x0000FF0000000000LL) >> 24) +\
								(((a) & 0x000000FF00000000LL) >> 8)  +\
								(((a) & 0x00000000FF000000LL) << 8)  +\
								(((a) & 0x0000000000FF0000LL) << 24) +\
								(((a) & 0x000000000000FF00LL) << 40) +\
								(((a) & 0x00000000000000FFLL) << 56) \
							)

#endif


#define NTAR_SWAP_16BITS(a)	((u_int16)(\
								(((a) & 0xFF00) >> 8) +\
								(((a) & 0x00FF) << 8)\
							))

#define NTAR_SWAP_32BITS(a)	((u_int32)(\
								(((a) & 0x000000FF) << 24) +\
								(((a) & 0x0000FF00) << 8) +\
								(((a) & 0x00FF0000) >> 8) +\
								(((a) & 0xFF000000) >> 24)\
							))

#if defined(_MSC_VER) || defined(__MINGW32__) 

typedef unsigned __int64	u_int64;
typedef __int64				int64;
typedef unsigned int		u_int32;
typedef	int					int32;
typedef unsigned short		u_int16;
typedef short				int16;
typedef unsigned char		u_int8;
typedef signed char			int8;

#else 

#include <sys/types.h>

#ifndef u_int32
#define	u_int32		u_int32_t
#define	int32		int32_t
#define	u_int16		u_int16_t
#define	int16		int16_t
#define	u_int8		u_int8_t
#define	int8		int8_t
#define	u_int64		u_int64_t
#define	int64		int64_t
#endif

#endif

typedef int64 ntar_foff;

#endif /*__BITTYPES_11263484553478329233663473*/
