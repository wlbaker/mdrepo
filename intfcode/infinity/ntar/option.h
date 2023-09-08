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

#ifndef __OPTION_3655965603483465443
#define __OPTION_3655965603483465443

#include "ntar.h"

/*! \addtogroup InternalFuncs
\{
*/
/*!
	\brief This fcn writes a string option in a caller provided buffer.
	\param option Pointer to the option that should be written.
    \param buffer Caller provided buffer that will be filled with the string option.
	\param buffer_size Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS 
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough to store the option-
	\note
		- This fcn writes both the option header, and the option value. After writing the option,
		It alignes the stuff to 32bits (as specified in the draft, options should be 32-bit aligned)
		As a consequence, buffer_size will always contain a 32-bit aligned value on return.
*/
int write_option_string(ntar_option* option, void *buffer, size_t *buffer_size);

/*!
	\brief This fcn writes a raw buffer option in a caller provided buffer.
	\param option Pointer to the option that should be written.
    \param buffer Caller provided buffer that will be filled with the string option.
	\param buffer_size Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\param raw_data Pointer to the raw_data associated with the option.
	\param raw_data_size Length of the raw_data associated with the option.
	\return
		- \ref NTAR_SUCCESS 
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough to store the option-
	\note
		- This fcn writes both the option header, and the option value. After writing the option,
		It alignes the stuff to 32bits (as specified in the draft, options should be 32-bit aligned)
		As a consequence, buffer_size will always contain a 32-bit aligned value on return.
	\note raw_data_size is 16bit, and not size_t, since the maximum option  length is on 16 bits.
*/
int write_option_raw(ntar_option *option, void *buffer, size_t *buffer_size, void* raw_data, u_int16 raw_data_size);

/*!
	\brief This fcn writes a 64-bit integer option in a caller provided buffer.
	\param option Pointer to the option that should be written.
    \param buffer Caller provided buffer that will be filled with the 64-bit integer  option.
	\param buffer_size Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS 
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough to store the option-
	\note
		- This fcn writes both the option header, and the option value. After writing the option,
		It alignes the stuff to 32bits (as specified in the draft, options should be 32-bit aligned)
		As a consequence, buffer_size will always contain a 32-bit aligned value on return.
*/
int write_option_uint64(ntar_option* option, void *buffer, size_t *buffer_size);

/*!
	\brief This fcn writes a 32-bit integer option in a caller provided buffer.
	\param option Pointer to the option that should be written.
    \param buffer Caller provided buffer that will be filled with the 32-bit integer  option.
	\param buffer_size Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS 
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough to store the option-
	\note
		- This fcn writes both the option header, and the option value. After writing the option,
		It alignes the stuff to 32bits (as specified in the draft, options should be 32-bit aligned)
		As a consequence, buffer_size will always contain a 32-bit aligned value on return.
*/
int write_option_uint32(ntar_option* option, void *buffer, size_t *buffer_size);

/*!
	\brief This fcn writes the NULL (aka END OPTION) in a
	buffer.
	\param buffer Caller provided buffer that will be filled with
		the NULL option
	\param buffer_size Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS 
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough to store the option-
	\note
		- This fcn writes both the option header, and the option value. After writing the option,
		It alignes the stuff to 32bits (as specified in the draft, options should be 32-bit aligned)
		As a consequence, buffer_size will always contain a 32-bit aligned value on return.
*/
int write_null_option(void *buffer, size_t *buffer_size);

/*!
	\brief This function reads a string out of an option 
		and copies it to a caller provided buffer.
	\param oh	Pointer to the option header containing the string. 
	\param byte_order Byte order of the current section. Possible values are
		- \ref HOST_BYTE_ORDER
		- \ref SWAPPED_HOST_BYTE_ORDER
	\param buffer Caller provided buffer that will be filled 
			with the NULL terminated string of the option on output.
	\param buffer_length Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough. In this case
			buffer_length is filled with the number of requested bytes.
	\note 
		- All the values in the parameter oh are already written in host byte order.
		- This function supposes that the string is stored right after the end of the 
		option header oh.
*/
int read_option_string(option_header *oh, int byte_order, void* buffer, size_t *buffer_length);

/*!
	\brief This function reads a 64-bit integer out of an option 
		and copies it to a caller provided buffer in host byte order.
	\param oh	Pointer to the option header containing the 64-bit integer. 
	\param byte_order Byte order of the current section. Possible values are
		- \ref HOST_BYTE_ORDER
		- \ref SWAPPED_HOST_BYTE_ORDER
	\param buffer Caller provided buffer that will be filled 
			with the 64-bit integer of the option on output.
	\param buffer_length Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough. In this case
			buffer_length is filled with the number of requested bytes.
	\note
		- All the values in the parameter oh are already written in host byte order.
		- This function supposes that the integer is stored right after the end of the 
		option header oh.
*/
int read_option_uint64(option_header *oh, int byte_order, void* buffer, size_t *buffer_length);

/*!
	\brief This function reads a 32-bit integer out of an option 
		and copies it to a caller provided buffer in host byte order.
	\param oh	Pointer to the option header containing the 32-bit integer. 
	\param byte_order Byte order of the current section. Possible values are
		- \ref HOST_BYTE_ORDER
		- \ref SWAPPED_HOST_BYTE_ORDER
	\param buffer Caller provided buffer that will be filled 
			with the 64-bit integer of the option on output.
	\param buffer_length Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough. In this case
			buffer_length is filled with the number of requested bytes.
	\note
		- All the values in the parameter oh are already written in host byte order.
		- This function supposes that the integer is stored right after the end of the 
		option header oh.
*/
int read_option_uint32(option_header *oh, int byte_order, void* buffer, size_t *buffer_length);

/*!
	\brief This function reads the data of an option as a raw buffer, 
		and copies it to a caller provided buffer without applying any byte order fixup.
	\param oh	Pointer to the option header containing the raw data.
	\param byte_order Byte order of the current section. Possible values are
		- \ref HOST_BYTE_ORDER
		- \ref SWAPPED_HOST_BYTE_ORDER
	\param buffer Caller provided buffer that will be filled with the raw data associated with
			the option on output.
	\param buffer_length Pointer to an integer. On input, it contains the size of the buffer.
			On output it contains the effective number of bytes used in buffer (if the buffer
			was big enough) or the number of requested bytes (if the buffer was not big enough).
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if the buffer was not big enough. In this case
			buffer_length is filled with the number of requested bytes.
	\note
		- All the values in the parameter oh are already written in host byte order.
		- This function does not make any assumption on the content of the raw data in the option.
		  It's the caller responsibility to check if the raw data has the right size, and to
		  perform byte order fixups.
*/
int read_option_raw(option_header *oh, int byte_order, void* buffer, size_t *buffer_length);

/*!
\}
*/

#endif /*__OPTION_3655965603483465443*/
