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

#ifndef _NTAR_DEBUG_13039489843867293475378934786
#define _NTAR_DEBUG_13039489843867293475378934786


#ifdef _DEBUG
#if defined _MSC_VER || defined __MINGW32__
#include <windows.h>

#if _MSC_VER < 1300
#define __FUNCTION__  __FILE__ "-VC6"
#endif 


#define NTAR_ASSERT(cond,msg) \
{\
	if (!(cond))\
	{\
		MessageBoxA(NULL,msg, "-- NTAR_ASSERTION --",0);\
		DebugBreak();\
	}\
}
#else /*_MSC_VER*/
#error You must correct this if you do not use the MSVC compiler
#endif /*_MSC_VER*/

#else  /*_DEBUG*/
#define NTAR_ASSERT(a, b)
#endif /*_DEBUG*/

#endif /*_NTAR_DEBUG_13039489843867293475378934786*/
