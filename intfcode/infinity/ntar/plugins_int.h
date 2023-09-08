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

#ifndef __PLUGINS_INT_12202373443r4hrfr743938474984
#define __PLUGINS_INT_12202373443r4hrfr743938474984

#include "plugins.h"

/*! \addtogroup PluginInterface
	\{
*/

/*! \brief Element of a list representing a generic blob (block of bytes)
    that have to be written to a trace file, or have been read out of it.

    A NULL terminated list of such blocks is dumped to disk without any further
    modification, and no checks are performed on the contents of the internal buffer.
*/
typedef struct _ntar_data_chunk
{
	void *data;	///< Pointer to the raw data associated with the data chunk
	size_t size;	///< Length, in bytes, of the raw data.
	struct _ntar_data_chunk *next;	///< Pointer to the next element in the list, or NULL
}
	ntar_data_chunk;


/*! \brief Initializes a given plugin state.

	This callback is called whenever the data of a block whose type matches 
	with the given plugin is retrieved (i.e. through \ref ntar_get_block_data or \ref ntar_get_block_options)
	The plugin can initialize its internal structures and return a handle to such data in the parameter plugin_state

	\param plugin_state Address of a library defined void pointer. On return, the plugin can set the value of this pointer
					to the state of its internal variables.
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE

	\note Each plugin is initialized and destroyed for each read/written block (if the block type matches the plugin type).
*/
typedef int (*plugin_init)(void **plugin_state);

/*! \brief Destroys a given plugin state.

	This callback is called when a block is closed.

	\param plugin_state state of the plugin, as returned by \ref plugin_init.
	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE

	\note Each plugin is initialized and destroyed for each read/written block (if the block type matches the plugin type).
*/
typedef int (*plugin_destroy)(void *plugin_state);

/*!	\brief Formats the data of a block in order to be written to some storage.
	
	This plugin callback is called by the library when a block should be written to some storage.
	This callback should format the buffer provided by the user through \ref ntar_create_block in the correct format
	that should be written to some storage..
	In particular, this function should write the data of a block to a library provided memory buffer.
	
	\param plugin_state	State of the plugin, set by \ref plugin_init
	\param data			Data of the block to be written. This is the data that the user provided with \ref ntar_create_block
	\param data_buffer	Library provided buffer that has to be used to create a linked list of \ref ntar_data_chunk elements. The first element
						in the list should reside at the very beginning of this buffer.
						The library will write these blocks to the storage.
	\param pbuffer_size	On input, it points to an integer containing the length of the data_buffer. On output, it contains
						the number of bytes actually used in data_buffer (if the buffer was big enough) or the number of needed
						bytes, if the data_buffer was too small.
	\return	The callback should return one of the following codes:	
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if data_buffer was not big enough
		- \ref NTAR_FAILURE in every other case.
	\note 
		- The plugin should create a NULL terminated linked list of \ref ntar_data_chunk elements, using the memory provided in data_buffer. 
		- The plugin can fill the linked list with chunks of memory taken from the data_buffer, or from the data parameter, or 
		   from some memory allocated in the \ref plugin_init phase. In this last case, such memory should be considered owned by the library
		   up to the next call of \ref plugin_write_data or \ref plugin_destroy. 
	\todo The last note is confusing. Is this callback suposed to be called more than once (supposing it succeeds) for one single block. I don't think so. And this should be clearly stated.
*/
typedef int (*plugin_write_data)(void *plugin_state, void* data, void* data_buffer, size_t *pbuffer_size);

/*!	\brief Formats the option data of a block option in order to be written to some storage.
	
	This plugin callback is called by the library when a block option should be written to some storage.
	This callback should format the buffer provided by the user through \ref ntar_add_block_option in the correct format
	that should be written to some storage..
	In particular, this function should write the data of a block option to a library provided memory buffer.
	\note 
	- The library takes care of writing the two standard options (COMMENT and END_OF_OPTIONS) without calling the specific block option writer 
        call.
	- The library provides a set of optimized functions to save the most common option types:
	  - \ref write_option_uint32 writes an unsigned 32bit integer to the caller provided buffer.
	  - \ref write_option_uint64 writes an unsigned 64bit integer to the caller provided buffer.
	  - \ref write_option_string writes a NULL terminated ANSI string to the caller provided buffer.
	  - \ref write_option_raw writes a blob (with a provided size) to the caller provided buffer, without any further modification.
	
	\param plugin_state	State of the plugin, set by \ref plugin_init
	\param option		Pointer to a\ref ntar_option, as passed to \ref ntar_add_block_option.
	\param data_buffer	Library provided buffer that has to be used to create a linked list of \ref ntar_data_chunk elements. The first element
						in the list should reside at the very beginning of this buffer.
						The library will write these blocks to the storage.
	\param pbuffer_size	On input, it points to an integer containing the length of the data_buffer. On output, it contains
						the number of bytes actually used in data_buffer (if the buffer was big enough) or the number of needed
						bytes, if the data_buffer was too small.
	\return	The callback should return one of the following codes:	
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER if data_buffer was not big enough
		- \ref NTAR_FAILURE in every other case.
	\note 
		- The plugin should create a NULL terminated linked list of \ref ntar_data_chunk elements, using the memory provided in data_buffer. 
		- The plugin can fill the linked list with chunks of memory taken from the data_buffer, or from the data parameter, or 
		   from some memory allocated in the \ref plugin_init phase. In this last case, such memory should be considered owned by the library
		   up to the next call of \ref plugin_write_option or \ref plugin_destroy. 
	\todo The last note is confusing. Is this callback suposed to be called more than once (supposing it succeeds) for one single block. I don't think so. And this should be clearly stated.
*/
typedef int (*plugin_write_option)(void *plugin_state, ntar_option *option, void *opt_buffer, size_t *pbuffer_size);

/*!	\brief Verifies that a given option is compatible with a given block.
	
	This plugin callback is called by the library when the user tries to add an option to a block using \ref ntar_add_block_option.
	It should return success only if the option is actually supported by the block *and* the data associated with the option have 
	a proper format.
	
	\param plugin_state	State of the plugin, set by \ref plugin_init
	\param option		Pointer to a \ref ntar_option, as passed to \ref ntar_add_block_option.
	\return	The callback should return one of the following codes:	
		- \ref NTAR_SUCCESS if the option is supported and verified.
		- \ref NTAR_FAILURE_INVALID_ID in every other case.
	\note The library does not request the verification for the standard options COMMENT and END_OF_OPTIONS.
		- The plugin should create a NULL terminated linked list of \ref ntar_data_chunk elements, using the memory provided in data_buffer. 
*/
typedef int (*plugin_validate_option)(void *plugin_state, ntar_option *option);

/*! \brief This function should decode the data of a block to a library provided memory buffer.
	
	\param plugin_state	State of the plugin, set by \ref plugin_init
	\param byte_order Byte order of the current section. Possible values are HOST_BYTE_ORDER and SWAPPED_HOST_BYTE_ORDER. The callback must
	always return data in host byte order.
	\param raw_data		Raw data of the block, as written to file. 
	\param raw_data_size On input, it contains the length of the raw_data buffer, on output the plugin 
						 should fill it with the number of bytes actually read from the raw_data buffer.
	\param data_buffer	Address of the pointer to a library provided buffer that has to be used to return the decoded block data. 
						This address can contain the same pointer passed on input, a pointer to an address in the raw_data buffer, 
						or a pointer to some memory allocated by the plugin in the plugin_init phase. In this last case, such memory 
						should be considered owned by the library up to the next call of plugin_read_data or plugin_destroy.
	\param pbuffer_size	On input, it points to an integer containing the length of parameter data_buffer. On output, it contains
						the number of bytes actually used in data_buffer (if the buffer was big enough) or the number of needed
						bytes, if the data_buffer was too small.
	\return	The callback should return one of the following codes:	
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER
		- \ref NTAR_FAILURE_MALFORMED_BLOCK
	\todo The note on data_buffer in [out] is again confusing. Is it possible that the library calls this function twice (when the fcn succeeds)? I don't think so.

*/
typedef int (*plugin_read_data)(void *plugin_state, int byte_order, void *raw_data, size_t raw_data_size, void** data_buffer, size_t *pbuffer_size, size_t *poption_start);

/*! \brief This function should decode the option data of a block to a library provided memory buffer.
	
	\param plugin_state	State of the plugin, set by \ref plugin_init
	\param opt_header	Header of the option, already converted in host byte order. The data of the option immediately follow the option header.
	\param byte_order Byte order of the current section. Possible values are HOST_BYTE_ORDER and SWAPPED_HOST_BYTE_ORDER. The callback must
	always return data in host byte order.
	\param opt_buffer	Address of the pointer to a library provided buffer that has to be used to return the decoded option data. 
						This address can contain the same pointer passed on input, a pointer to an address in the opt_header buffer, 
						or a pointer to some memory allocated by the plugin in the plugin_init phase. In this last case, such memory 
						should be considered owned by the library up to the next call of plugin_read_option or plugin_destroy.
	\param pbuffer_size	On input, it points to an integer containing the length of parameter opt_buffer. On output, it contains
						the number of bytes actually used in opt_buffer (if the buffer was big enough) or the number of needed
						bytes, if the opt_buffer was too small.
	\return	The callback should return one of the following codes:	
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_SMALLBUFFER
		- \ref NTAR_FAILURE_INVALID_ID if the option code is not supported/recognized by the block plugin.
		- \ref NTAR_FAILURE in any other case.

	\todo The note on opt_buffer in [out] is again confusing. Is it possible that the library calls this function twice (when the fcn succeeds)? I don't think so.

*/
typedef int (*plugin_read_option)(void *plugin_state, option_header *opt_header, int byte_order, void* opt_buffer, size_t *pbuffer_size);

/*! \brief This structure is used to uniquely identify a given plugin. It contains the unique identifier of a block, as well as all the
    pointers to the plugin callbacks.
*/

typedef struct _ntar_plugin_data
{
	u_int32						block_type;
	plugin_init					init;
	plugin_destroy				destroy;
    plugin_write_data			write_data;
	plugin_write_option			write_option;
	plugin_validate_option		validate_option;
	plugin_read_data			read_data;
	plugin_read_option			read_option;
}
	ntar_plugin_data;

/*! \brief This function returns a pointer to a \ref ntar_plugin_data structure
    uniquely identifying the callbacks of a given block.

    \param block_id Identifier of the block.
    \return A pointer to a \ref ntar_plugin_data structure
    uniquely identified by the block ID, or NULL.
*/
ntar_plugin_data* get_plugin_data(u_int32 block_id);

#include "plugin_idb_int.h"
#include "plugin_pktb_int.h"
#include "plugin_spb_int.h"
/*****************************************
 * other plugin private includes go here *
 ****************************************/

/*! \todo The definition of this list here is non-sense, as each source
    including this file will have its own copy of this array. This does
    not cause any problem, since all the values in the structures are 
    constant, however it's a waste of memory (and it's not elegant!!).
*/
extern ntar_plugin_data ntar_plugins[];

/*!
	\}
*/


#endif /* __PLUGINS_INT_12202373443r4hrfr743938474984 */

