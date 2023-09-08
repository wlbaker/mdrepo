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

#include "section.h"
#include "option.h"
#include "plugins_int.h"

#define SCAN_MODE_RETRIEVAL	0
#define SCAN_MODE_SCAN		1

/*!
	\brief This fcn calculates the length of a linked list of ntar_options.
	These are the options set by ntar_add_block_option. The length of the list
	is the amount of raw bytes that are needed to write such options on the storage.
	This fcn invokes the proper plugin to know the length of each option.

	\param block_handle Handle of the block. This fcn computes the length of 
			block_handle->options.
	\param length pointer to an integer that will be filled with the length of the
			options.
	\return 
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_INVALID_ID if the list contains an invalid option for the block.
		- another NTAR_FAILURE_XXX code otherwise

*/
static int get_block_options_length(ntar_block_handle *block_handle, size_t *length)
{
	ntar_option *iterator;
	size_t option_length;
	int ret_value;

	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(block_handle->plugin_data != NULL, __FUNCTION__ " NULL plugin");

	*length = 0;

	if (block_handle->options == NULL)
	{
		return NTAR_SUCCESS;
	}
	
	for (iterator = block_handle->options; iterator != NULL; iterator = iterator->next)
	{
		option_length = 0;

		switch (iterator->code)
		{
		/* we skip this option as we do not save it on disk */
		case OPTION_ENDOFOPT:
			continue;
		
		/* this is the only option that is common to all the blocks
		 * so we can deal with it without invoking the plugin
		 */
		case OPTION_COMMENT:
			ret_value = write_option_string( iterator, NULL,&option_length);
			if (ret_value != NTAR_SUCCESS && ret_value != NTAR_FAILURE_SMALLBUFFER)
				return ret_value;
			*length += option_length;
			break;

		default:
			ret_value = block_handle->plugin_data->write_option(
				block_handle->plugin_state, 
				iterator, 
				NULL, 
				&option_length);
			if (ret_value != NTAR_SUCCESS && ret_value != NTAR_FAILURE_SMALLBUFFER)
				return ret_value;
			NTAR_ASSERT(option_length % 4 == 0, __FUNCTION__ " unaligned option length");
			*length += option_length;
			break;
		}

	}

	/* we must compute the length of the trailing null option */
	ret_value = write_null_option(NULL, &option_length);
	if (ret_value != NTAR_SUCCESS && ret_value != NTAR_FAILURE_SMALLBUFFER)
		return ret_value;
	
	*length += option_length;

	return NTAR_SUCCESS;
}

/*!
	\brief This fcn writes the options of a block to a raw buffer, 
	and then dumps such buffer to disk.
	The options are stored in the block handle, the raw buffer is
	contained in the handle, as well. This fcn assumes that this
	buffer is big enough to contain such options (i.e. this fcn
	does not try to reallocate such buffer if it's too small).
	This fcn assumes that the file pointer points soon after the
	data of a block.

	\param block_handle Handle to the block that contains the options
		and the destination raw buffer (block_handle->options_buffer).

	\return
		- \ref NTAR_SUCCESS
		- \ref NTAR_FAILURE_INVALID_ID if the option list contains an invalid option
		- \ref NTAR_FAILURE_SMALLBUFFER if the raw buffer is too small
		- \ref NTAR_FAILURE_IOWRITE in case fwrite failed
		- NTAR_FAILURE_XX otherwise
*/
static int write_block_options(ntar_block_handle *block_handle)
{
	ntar_option *iterator;
	char* buffer_pointer; /* used to scan the buffer */
	size_t remaining_bytes;	/* sentinel to avoid a buffer overrun */
	size_t option_length;
	int ret_value;

	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");

	/* we suppose that the option_buffer is large enough to contain all the options
	 * otherwise we generate an assertion and we fail 
	 */
	if (block_handle->options == NULL)
	{
		return NTAR_SUCCESS;
	}

	buffer_pointer = block_handle->options_buffer;
	remaining_bytes = block_handle->options_buffer_length;
	
	for (iterator = block_handle->options; iterator != NULL; iterator = iterator->next)
	{
		option_length = remaining_bytes;
		switch (iterator->code)
		{
		case OPTION_ENDOFOPT:
			continue;
		
		case OPTION_COMMENT:
			ret_value = write_option_string(iterator, buffer_pointer, &option_length);
			if (ret_value != NTAR_SUCCESS)
				return ret_value;
			break;
		default:
			ret_value = block_handle->plugin_data->write_option(
				block_handle->plugin_state,
				iterator, 
				buffer_pointer, 
				&option_length);
			if (ret_value != NTAR_SUCCESS)
				return ret_value;
		}

		buffer_pointer += option_length;
		remaining_bytes -= option_length;
	}

	option_length = remaining_bytes;
	ret_value = write_null_option(buffer_pointer, &option_length);
	if ( ret_value != NTAR_SUCCESS)
		return ret_value;

	remaining_bytes -= option_length;

	ret_value = block_handle->file_handlers.write_handler(
		block_handle->file_handlers.handle,
		block_handle->options_buffer, 
		block_handle->options_buffer_length - remaining_bytes);

	return ret_value;
}

/*!
	\brief This function closes a block that was opened in write mode.
	It's the backend of ntar_close_block()
	It basically
	- calculate the options length in the file
	- retrieves the needed bytes to format the block data
	- format the block data to a list of memory blobs
	- computes the entire block length
	- writes the block header
	- writes the block data
	- reallocates the options buffer, if needed
	- writes the options to disk
	- writes the trailing block length

	\param block_handle block to close.
	\return 
	  - \ref NTAR_SUCCESS on success
	  - one of the NTAR_FAILURE_xxx values on failure
*/
static int close_write_block(ntar_block_handle *block_handle)
{
	int ret_value;
	size_t options_length;
	size_t data_buffer_bytes;
	size_t data_length;
	ntar_data_chunk *iterator;
	u_int32 align_bytes;

	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " received a NULL parameter");

	if (block_handle->block_data == NULL)
		return NTAR_FAILURE_BLOCKDATANOTSET;

	/* since we need to write the block header before writing the data
	 * and the options, we must calculate the length of them, write
	 * the block header, and finally write data and options
	 */

	ret_value = get_block_options_length(block_handle, &options_length);

	if (ret_value != NTAR_SUCCESS)
		goto error;
	
	/* here we set the length of the raw data buffer to 0, so that
	 * write_data fails for small buffer and returns the requested size
	 * for the raw bytes it uses to create the linked list of blobs that
	 * will be written to disk
	 */
	data_buffer_bytes = 0;
	ret_value = block_handle->plugin_data->write_data(
		block_handle->plugin_state,
		block_handle->block_data,
		NULL,
		&data_buffer_bytes);

	/* ret_Value can be SUCCESS if the plugin does not write anything in
	 * the block data
	 */
	if (ret_value != NTAR_SUCCESS && ret_value != NTAR_FAILURE_SMALLBUFFER)
		goto error;

	/* we need to reallocate the data buffer if it's too small */
	if (ret_value == NTAR_FAILURE_SMALLBUFFER)
	{
		/* the (void**) cast is necessary to avoid some compiler warnings */
		ret_value = reallocate_memory(
			(void**)&block_handle->data_buffer, 
			&block_handle->data_buffer_length,
			data_buffer_bytes);

		if (ret_value != NTAR_SUCCESS)
			goto error;
	}

	/* now we actually retrieve the list of blobs (i.e. \ref ntar_data_chunk's)
	 * that should be written to storage.
	 */
    
	data_buffer_bytes = block_handle->data_buffer_length;

	ret_value = block_handle->plugin_data->write_data(
		block_handle->plugin_state, 
		block_handle->block_data, 
		block_handle->data_buffer, 
		&data_buffer_bytes);

	if (ret_value != NTAR_SUCCESS)
		goto error;

	data_length = 0;
	
	/* let's calculate the block data size by iterating through the list of blobs*/
	for (iterator = (ntar_data_chunk*)block_handle->data_buffer; iterator != NULL; iterator = iterator->next)
	{
		data_length += iterator->size;
	}
    
	/* finally we can compute the block size */
	block_handle->bh.block_total_length = (u_int32)(sizeof (block_header) 
		+ data_length
		+ options_length
		+ sizeof(u_int32));

	/* we write the block header */
	ret_value = block_handle->file_handlers.write_handler(
		block_handle->file_handlers.handle,
		&(block_handle->bh), 
		sizeof(block_header));

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}
	
	/* now we write the blobs to disk */
	for (iterator = (ntar_data_chunk*)block_handle->data_buffer; iterator != NULL; iterator = iterator->next)
	{
		ret_value = block_handle->file_handlers.write_handler(
			block_handle->file_handlers.handle,
			iterator->data, 
			iterator->size);
		
		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}
	}

	/* the block data can be unaligned, we need to put some dummy bytes to align it to 32 bits*/
	align_bytes = NTAR_ALIGN_32BITS(block_handle->bh.block_total_length) - block_handle->bh.block_total_length;

	if (align_bytes > 0)
	{
		u_int32 dummy_value;

		dummy_value = 0;
		
		ret_value = block_handle->file_handlers.write_handler(
			block_handle->file_handlers.handle,
			&dummy_value, 
			align_bytes);

		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}
	}

	/* now we can deal with the options */

	/* we need to reallocate the options buffer if it's too small */
	ret_value = reallocate_memory(
		(void**)&block_handle->options_buffer,
		&block_handle->options_buffer_length,
		options_length);

	if (ret_value != NTAR_SUCCESS)
		goto error;

	NTAR_ASSERT(options_length %4 == 0, __FUNCTION__ " options are not aligned\n");

	/* write the options */
	ret_value = write_block_options(block_handle);

	if (ret_value != NTAR_SUCCESS)
		goto error;

	/* and finally write the trailing block length at the end of the block */
	ret_value = block_handle->file_handlers.write_handler(
		block_handle->file_handlers.handle,
		&(block_handle->bh.block_total_length), 
		sizeof(u_int32));
	
	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}

	/* release the plugin */
	ret_value = block_handle->plugin_data->destroy(block_handle->plugin_state);

	if (ret_value != NTAR_SUCCESS)
		goto error;

	/* and seignal the section that the block has been closed */
	block_handle->section_handle->block_opened = FALSE;

	return NTAR_SUCCESS;

error:

	return ret_value;
}





/*!
	\brief This function closes a block that was opened in read mode.
	It's the backend of ntar_close_block()
	It basically
	- destroys the plugin
	- jumps to the end of the block, either by a seek or by reading all
	  the block payload.

	\param block_handle block to close.
	\return 
	  - \ref NTAR_SUCCESS on success
	  - one of the NTAR_FAILURE_xxx values on failure
*/

static int close_block_read_mode(ntar_block_handle *block_handle)
{
	int ret_value;
	ntar_foff new_position;
	u_int32 trailer_block_length;
	
	ret_value = NTAR_SUCCESS;

	/* if plugin_data is NULL, it means that the plugin has not
	 * been initialized, i.e. ntar_get_block_[data|option] has not
	 * been called
	 */
	if (block_handle->plugin_data != NULL)
	{
		ret_value = block_handle->plugin_data->destroy(block_handle);

		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	}

	/* if the file support seeks, we can go to the end of the block
	 * with a seek...
	 */
	if (block_handle->file_handlers.seek_handler != NULL)
	{
		new_position = block_handle->block_start + NTAR_ALIGN_32BITS(block_handle->bh.block_total_length);

		ret_value = block_handle->file_handlers.seek_handler(
			block_handle->file_handlers.handle,
			new_position,
			SEEK_SET,
			NULL);
	}
	else
	{
		/* we cannot use seeks, we read data out of the block until
		 * we reach the end of the block
		 */
		if (block_handle->are_block_data_read == FALSE)
		{
			char temp_buffer[1024];
			size_t total_read_bytes;
			size_t read_bytes;
			size_t bytes_to_read;
			int ret_value;
			
			total_read_bytes = 0;
			
			bytes_to_read = 
				NTAR_ALIGN_32BITS(block_handle->bh.block_total_length) /* block length */
				- sizeof(block_header) /* we have already read the block header */
				- sizeof(u_int32);     /* we do not read the treiling block length 
									    * since we will read it after, even if
										* we have already read the block data and
										* options
										*/
				
			ret_value = NTAR_SUCCESS;

			/* loop to read all the block payload */
			while(total_read_bytes < bytes_to_read && ret_value == NTAR_SUCCESS)
			{
				if (sizeof(temp_buffer) < bytes_to_read - total_read_bytes)
					read_bytes = sizeof(temp_buffer);
				else
					read_bytes = bytes_to_read - total_read_bytes;

				ret_value = block_handle->file_handlers.read_handler(
					block_handle->file_handlers.handle,
                    temp_buffer, 
					read_bytes, 
					NULL);

				if (ret_value != NTAR_SUCCESS)
					goto error;

				total_read_bytes += read_bytes;
			}
		}

		/* we need to read the trailing block size */
		ret_value = block_handle->file_handlers.read_handler(
			block_handle->file_handlers.handle,
			&trailer_block_length, 
			sizeof(u_int32),
			NULL);

		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}

		/* Let's fix the byte order of the trailer block size*/
		if ( block_handle->byte_order != HOST_BYTE_ORDER)
		{
			trailer_block_length = NTAR_SWAP_32BITS(trailer_block_length);
		}

		/*sanity check: verify that the trailer block size matches the header block size */
		if (block_handle->bh.block_total_length != trailer_block_length)
		{
			ret_value = NTAR_FAILURE_BLOCKTRAILERMISMATCH;
		}
	}

	/* NOTE: in this moment the file pointer points to the first 
	 * byte of the following block (if any)
	 */
	
	/* we signal the section that the block has been called */
	block_handle->section_handle->block_opened = FALSE;

error:
	return ret_value;
}

/*!
	\brief This function reads the entire raw data of a block,
	i.e. its payload.
	
	This fcn writes all the payload in the buffer block_handle->raw_data_buffer
	If this buffer is too small, the buffer gets reallocated before reading the
	data.
	
	\param block_handle Handle to the block to read.
	\return 
		- \ref NTAR_SUCCESS
		- \ref one of the NTAR_FAILURE_xxx otherwise.
*/	
static int read_raw_block_data(ntar_block_handle *block_handle)
{
	size_t needed_raw_bytes;
	int ret_value;

	NTAR_ASSERT(block_handle->are_block_data_read == FALSE, __FUNCTION__ " block data already read");

	/* compute the payload length, 
	 * that is the block length 
	 *             - the block header 
	 *			   - the trailing block length 
     */
	needed_raw_bytes = NTAR_ALIGN_32BITS(block_handle->bh.block_total_length)
		- sizeof(block_header)
		- sizeof(u_int32);
    
	if (needed_raw_bytes > block_handle->raw_data_buffer_length)
	{	/* the current raw buffer is not big enough */
		ret_value = reallocate_memory(
			&(block_handle->raw_data_buffer), 
			&(block_handle->raw_data_buffer_length),
			needed_raw_bytes);

		if (ret_value!= NTAR_SUCCESS)
			return ret_value;
	}

	ret_value = block_handle->file_handlers.read_handler(
		block_handle->file_handlers.handle,
		block_handle->raw_data_buffer, 
		needed_raw_bytes,
		NULL);

	if (ret_value != NTAR_SUCCESS)
	{
		return ret_value;
	}

	/* we signal the block handle that we have read
	 * the block payload. This is needed to keep
	 * track of the current position of the file
	 * pointer
	 */
	block_handle->are_block_data_read = TRUE;
	
	/* NOTE: now the file pointer points to the first byte
	 * of the trailing block length
	 */
	return NTAR_SUCCESS;
}

/*!
	\brief This fcn decodes the data part of a block payload
	that was previously read with \ref read_raw_block_data.

	The decoded data are saved in block_handle->block_data
	If the underlying buffer (block_handle->data_buffer) 
	is not big enough, it gets reallocated.

	\param	block_handle Handle to the block.
	\return 
		- \ref NTAR_SUCCESS
		- one of the NTAR_FAILURE_xxx otherwise
*/
static int decode_block_data(ntar_block_handle *block_handle)
{
	void *data_buffer;
	size_t data_buffer_length;
	size_t start_options;
	int ret_value;
	size_t raw_data_buffer_effective_length;

	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(block_handle->are_block_data_read == TRUE, __FUNCTION__ " raw block has not beeen read");

	/* we need to use a local copy of data_buffer
	 * The reason is explained some lines below,
	 * where the plugin is invoked
	 */
	data_buffer = block_handle->data_buffer;
	
	data_buffer_length = block_handle->data_buffer_length;

	/* we recompute the length of the raw data in the block
	 * This is because block_handle->raw_data_buffer_length
	 * is NOT the length of the raw data in the block, BUT
	 * the length of the raw data buffer (that is, it could be
	 * bigger than actual size of the block payload we have read
	 * with read_raw_block_data
	 */
	raw_data_buffer_effective_length = NTAR_ALIGN_32BITS(block_handle->bh.block_total_length)
		- sizeof(block_header)
		- sizeof(u_int32);

	/* we call the plugin to decode the data
	 * We assume that the plugin has been initialized by the caller.
	 */
	ret_value = block_handle->plugin_data->read_data(
		block_handle->plugin_state,
		block_handle->byte_order,
        block_handle->raw_data_buffer,
		raw_data_buffer_effective_length,
		&data_buffer,	/* here we use a local copy of data_buffer because */
						/* it's used as an output parameter, as well */
		&data_buffer_length,
		&start_options
		);
	
	if (ret_value == NTAR_SUCCESS)
	{	/* the block_data buffer was large enough, we return success
		*/
		block_handle->block_data = data_buffer;

		/* this field is used by decode_block_options to understand
		 * where the options begin
		 */
		block_handle->raw_data_buffer_start_options = start_options;
		return NTAR_SUCCESS;
	}

	/* data_buffer was to small, reallocate it and invoke the plugin again
	 */
	if (ret_value == NTAR_FAILURE_SMALLBUFFER)
	{
		int sb_ret_value;

		sb_ret_value = reallocate_memory(
			(void**)(&block_handle->data_buffer), 
			&block_handle->data_buffer_length, 
			data_buffer_length);
		if (sb_ret_value != NTAR_SUCCESS)
			return sb_ret_value;
	
		data_buffer = block_handle->data_buffer;
		data_buffer_length = block_handle->data_buffer_length;
	
		sb_ret_value = block_handle->plugin_data->read_data(
			block_handle->plugin_state,
			block_handle->byte_order,
			block_handle->raw_data_buffer,
			raw_data_buffer_effective_length,
			&data_buffer,
			&data_buffer_length,
			&start_options
			);

		if (sb_ret_value == NTAR_SUCCESS)
		{	/* this time the plugin was sccessfull */
			block_handle->block_data = data_buffer;

			/* this field is used by decode_block_options to understand
			 * where the options begin
			 */
			block_handle->raw_data_buffer_start_options = start_options;
			return NTAR_SUCCESS;
		}
		else /* something weird is happenign with the plugin, return the error */
			return sb_ret_value;
	}
		
	/* we reach this if the first invokation of the plugin was unsuccessful for
	 * some weird reason (not a small buffer), we return the error to the caller
	 */
	return ret_value;
}

/*!
	\brief This fcn decodes the options part of a block payload
	that was previously read with \ref read_raw_block_data.

	The decoded options are saved in block_handle->options
	If the underlying buffer (block_handle->options_buffer) 
	is not big enough, it gets reallocated.

	\note This fxn assumes that the block data has been already 
	      decoded with \ref decode_block_data

	\param	block_handle Handle to the block.
	\return 
		- \ref NTAR_SUCCESS
		- one of the NTAR_FAILURE_xxx otherwise
*/
static int decode_block_options(ntar_block_handle *block_handle)
{
	size_t			options_length;
	ntar_option		*current_option;
	ntar_option		*new_option;
	option_header	*opt_header;
	option_header	original_opt_header;
	size_t			opt_buffer_written_bytes;
	size_t			raw_buffer_position;
	char			*temp_opt_buffer;
	size_t			remaining_bytes;
	int				more_options;
	int				ret_value;
	int				scan_mode;
	
	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(block_handle->are_block_data_read == TRUE, __FUNCTION__ " raw block has not beeen read");
	
	/* we must check that some options are present in the block
	 * there are options if the options start before the end of the
	 * block
	 */
	options_length = NTAR_ALIGN_32BITS(block_handle->bh.block_total_length)
		- sizeof(block_header) 
		- sizeof(u_int32)	/* for the trailing block length */
		- block_handle->raw_data_buffer_start_options;

	if (options_length == 0)
	{
		block_handle->options = NULL;
		return NTAR_SUCCESS;
	}

	/* this big loop is used to decode the entire options:
	 * it start by supposing that the options_buffer is big
	 * enough (scan_mode = SCAN_MODE_RETRIEVAL). If the buffer is not
	 * big enough, it turns the scan_mode to SCAN_MODE_SCAN.
	 * At the beginning of each loop, scan_mode is always 
	 * reset to RETRIEVAL, if at the end of the loop is in SCAN_MODE
	 * option_buffer is reallocated (the new size is computed in the
	 * loop), and the loop restarts.
	 * If scan_mode at the end is on RETRIEVAL, it means that we
	 * have decoded the options successfully.
	 */
	do
	{
		/* use a local copy of the option_buffer pointer and size, 
		 * in order not to make it "dirty"
		 */
		temp_opt_buffer = block_handle->options_buffer;
		remaining_bytes = block_handle->options_buffer_length;

		/* initialize the test variable for the internal loop
		 * scanning the options 
		 */
		more_options = TRUE;
		scan_mode = SCAN_MODE_RETRIEVAL;
		
		/* reset the counter holding the number of bytes written/needed
		 * in options_buffer
		 */
		opt_buffer_written_bytes = 0;
		
		/* pointer to the last written option in option_buffer
		 */
		current_option = NULL;
		
		/* pointer to the new_option that gets created at each loop
		 */
		new_option = NULL;
		
		/* position in the raw buffer containing the packet payload.
		 * We initialize it to the start of the options. 
		 * raw_data_buffer_start_options has been initialized by 
		 * decode_block_data
		 */
		raw_buffer_position = block_handle->raw_data_buffer_start_options;
		
		/* last option_header analyzed */
		opt_header = NULL;

		/* local copy of the last option header analyzed 
		 * This inizilization is not necessary, it's needed
		 * to avoid a compiler wraning about uninitialized variable
		 */
		original_opt_header = END_OPTION;

		while(more_options)
		{
			size_t option_data_length;
			
			/* since we always work on the option_header contained in the
			 * raw buffer, and since we swap the values to host byte order,
			 * we need to write the original option_header in the raw buffer
			 * because we scan the options in the raw buffer twice, usually,
			 * one to understand the needed bytes, and one to actually decode
			 * the buffer
			 * Here we restore the original option_header
			 * The initialization opt_header = NULL before the beginning of the
			 * loop is used to restore the original option header in the first
			 * run of the loop
			 */
			if (opt_header != NULL)
				*opt_header = original_opt_header;

			/* this check is used to avoid a buffer overrun in the raw_buffer */
			if (raw_buffer_position + sizeof(option_header) <= block_handle->raw_data_buffer_length)
			{
				opt_header = (option_header*)((char*)block_handle->raw_data_buffer + raw_buffer_position);
				raw_buffer_position += sizeof(option_header);
			}
			else
				return NTAR_FAILURE_MALFORMED_BLOCK;

			/* here we save a local copy of the option_header in order
			 * to be able to restore it at the end of the loop
			 */
			original_opt_header = *opt_header;
			
			if (IS_END_OPTION(*opt_header))
			{
				/* we can end the scan of the options */
				more_options = FALSE;
				continue;
			}
			
			if (block_handle->byte_order != HOST_BYTE_ORDER)
			{
				opt_header->option_code = NTAR_SWAP_16BITS(opt_header->option_code);
				opt_header->option_length = NTAR_SWAP_16BITS(opt_header->option_length);
			}

			/* here we check the consistency of the option:
			 * there should be at least option_length (aligned to 32 bits) bytes after
			 * the option header
			 */
			if( NTAR_ALIGN_32BITS(opt_header->option_length) + raw_buffer_position > block_handle->raw_data_buffer_length)
				return NTAR_FAILURE_MALFORMED_BLOCK;

			/* the option in the raw buffer seems ok 
			 * we "allocate" an ntar_option in the options_buffer,
			 * if there is enough space
			 */
			if (remaining_bytes < sizeof(ntar_option))
			{
				/* there is no enough space in the buffer, 
				* we continue to scan the options	to understand the needed bytes
				*/
				scan_mode = SCAN_MODE_SCAN;

				/* we take into consideration the space for the ntar_handle 
				 * in the buffer 
				 * NOTE: the NATIVE alignment is needed so that the plugins
				 * recieve a buffer that is always aligned to the underlying architecture,
				 * more or less as the plugin would call a malloc to have the buffer.
				*/
				opt_buffer_written_bytes += NTAR_ALIGN_NATIVE(sizeof(ntar_option));

				/* this is used to inform the option readers that we are querying
				* for the needed bytes, only.
				*/
				option_data_length = 0;
			}
			else
			{
				/* we "allocate" a new ntar_option out of the buffer 
				* and we fix all the pointers 
				*/
				new_option = (ntar_option*)temp_opt_buffer;


				/* We in/decrement the pointers/indexes of the options_buffer
				 * NOTE: the NATIVE alignment is needed so that the plugins
				 * recieve a buffer that is always aligned to the underlying architecture,
				 * more or less as the plugin would call a malloc to have the buffer.
				 */
				opt_buffer_written_bytes += NTAR_ALIGN_NATIVE(sizeof(ntar_option));
				temp_opt_buffer += NTAR_ALIGN_NATIVE(sizeof(ntar_option));
				remaining_bytes -= NTAR_ALIGN_NATIVE(sizeof(ntar_option));
				new_option->code = opt_header->option_code;
				new_option->data = temp_opt_buffer;
				new_option->next =  NULL;

				/* we do not put the new option in the list, yet. This
				* This is because we cannot be sure that the option reader
				* has enough bytes to fill the option
				*
				* current_option->next = new_option;
				* current_option = new_option;
				*/

				/* this is used to inform the option readers the 
				 * number of bytes available in the buffer 
				 */
				option_data_length = remaining_bytes;
			}

			/* now we read the option data with the option readers */
			if (opt_header->option_code == OPTION_COMMENT)
			{	/* this is the only option that is common 
				 * to the various blocks
				 */
				ret_value = read_option_string(opt_header,
					block_handle->byte_order,
					temp_opt_buffer, 
					&option_data_length);
			}
			else
			{
				/* call the plugin to decode the option */
				ret_value = block_handle->plugin_data->read_option(
					block_handle->plugin_state,
					opt_header,
					block_handle->byte_order,
					temp_opt_buffer,
					&option_data_length);
			}
			
			/* then we must move the raw_buffer position over this option.
			 */
			raw_buffer_position += NTAR_ALIGN_32BITS(opt_header->option_length);

			if (ret_value == NTAR_SUCCESS)
			{
				/* we were able to read the option correctly,
				 * we can add the option to the linked list
				 * We do not move the buffer pointers because
				 * this is done afterwards, to group the code
				 * that moves such pointers
				 */

				/* if current_option is NULL, we have read the first option */
				if (current_option != NULL) 
					current_option->next = new_option;
				current_option = new_option;
			}
			else
			if (ret_value == NTAR_FAILURE_SMALLBUFFER)
			{
				/* the buffer was too small, we move to MODE_SCAN
				* it's not important to "free" the allocated new_option,
				* since we do not write anything in the buffer.
				*/
				scan_mode = SCAN_MODE_SCAN;
			}
			else
			if (ret_value == NTAR_FAILURE_INVALID_ID)
			{
				/* if the option was not recognized, we must skip it
				* First we fix again the buffer pointers, so that 
				* we "virtually" free the ntar_option we "allocated"
				*/
				if (scan_mode == SCAN_MODE_RETRIEVAL)
				{
					opt_buffer_written_bytes -= NTAR_ALIGN_NATIVE(sizeof(ntar_option));
					temp_opt_buffer -= NTAR_ALIGN_NATIVE(sizeof(ntar_option));
					remaining_bytes += NTAR_ALIGN_NATIVE(sizeof(ntar_option));
				}

				/* since we have skipped the option, we should avoid to increment
				 * the position in the options_buffer, so we reset the number of
				 * bytes written in the options_buffer for the option data to 0
				 */
				option_data_length = 0;
			}
			else
			{
				/* severe error, we stop scanning the options */
				return ret_value;
			}

				
			/* This is done in order to have the next ntar_option aligned 
			 * to the machine alignment
			 */
			option_data_length = NTAR_ALIGN_NATIVE(option_data_length);

			if (scan_mode == SCAN_MODE_SCAN)
			{
				/* we are not interested in fixing the buffer pointers,
				 * we simply fix the counter that takes into account the
				 * the number of bytes needed. Even if the buffer if large
				 * enough to take some other option (and the previous code
				 * will write something, we are in SCAN_MODE, so the options
				 * will be scanned again
				 */
				opt_buffer_written_bytes += option_data_length;
			}
			else
			{
				/* the buffer was big enough, we fix all the buffer pointers */
				opt_buffer_written_bytes += option_data_length;
				temp_opt_buffer += option_data_length;
				remaining_bytes -= option_data_length;
			}
		}	
		
		/* here we have finished to scan the options:
		 * scan_mode tells us if we were able to decode the options successfully
		 * i.e. if the options_buffer was big enough
		 * opt_buffer_written_bytes tells us the written bytes in such buffer,
		 * if big enough, or the number of needed bytes
		 * block_handle->options_buffer is the head of the options linked list
		 * (if the buffer was big enough, obviously)
		 */
		if (scan_mode == SCAN_MODE_SCAN)
		{
			/* the options_buffer was not big enough */
				int reall_ret_value;

				reall_ret_value = reallocate_memory(
					(void**)(&block_handle->options_buffer), 
					&block_handle->options_buffer_length,
					opt_buffer_written_bytes);

				if (reall_ret_value != NTAR_SUCCESS)
					return reall_ret_value;
		}
	} /* this is the end of the big loop */
	while (scan_mode == SCAN_MODE_SCAN);
	
	/* if it's null, we do not have any "previous" option, 
	 * so there are no options
	 */
	if (current_option == NULL)
		block_handle->options = NULL;
	else
		block_handle->options = (ntar_option*)(block_handle->options_buffer);

	return NTAR_SUCCESS;
}

int ntar_create_block(ntar_section_handle* section_handle, u_int32 block_type, void* data, ntar_block_handle** pblock_handle)
{
	ntar_block_handle *new_block = NULL;
	int ret_value;
	ntar_plugin_data *block_plugin;

	/* first check that the previous block has been closed */
	if (section_handle->block_opened)
	{
		ret_value = NTAR_FAILURE_BLOCKNOTCLOSED;
		goto error;
	}

	/* second, if the section header has not been closed, we must close it 
	 * this hack is needed because the section_handle is opened, but we can
	 * write a new block only if we have written the section_header_block
	 */
	if (!section_handle->header_written)
	{
		ret_value = write_section_header_block(section_handle);
		if (ret_value != NTAR_SUCCESS)
			goto error;
	}

	/* find the plugin for this block in the available ones 
	 */
	block_plugin = get_plugin_data(block_type);
	if (block_plugin == NULL)
	{
		ret_value = NTAR_FAILURE_INVALID_ID;
		goto error;
	}

	/* "allocate" a new block, by using the cached one in the section_handle */
	new_block = &(section_handle->cache_block);
	
	/* reset all the pointers that depend on the current block,
	 * basically all the stuff related to the plugin, and the
	 * block data
	 */
	new_block->plugin_state = NULL;
	new_block->plugin_data = block_plugin;
	new_block->options = NULL;
	new_block->block_data = data;
	new_block->bh.block_type = block_type;
	/* we do not know the length of the block  
	 * new_block->bh.block_total_length = ???
	 */

	ret_value = new_block->plugin_data->init(&new_block->plugin_state);

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}

	/* we return the new block to the caller
	 * and we inform the section that a new block has been created
	 */
	*pblock_handle = new_block;
	section_handle->block_opened = TRUE;

	return NTAR_SUCCESS;

error:
	return ret_value;
}

int ntar_close_block(ntar_block_handle* block_handle)
{
	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " received a NULL parameter");
	NTAR_ASSERT(block_handle->section_handle != NULL, __FUNCTION__ " block_handle->section_handle is NULL");

	// TODO this is UGLY. What is the perf hit of such an indirection??
	switch(block_handle->section_handle->file_handle->file_mode)
	{
	case NTAR_FILEMODE_READ:
		return close_block_read_mode(block_handle);

	case NTAR_FILEMODE_WRITE:
	case NTAR_FILEMODE_APPEND:
	case NTAR_FILEMODE_CREATE:
        return close_write_block(block_handle);

	default:
		return NTAR_FAILURE;
	}
}

int ntar_add_block_option(ntar_block_handle* block_handle, ntar_option *option)
{
	int ret_value;
	ntar_option *iterator;

	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(option != NULL, __FUNCTION__ " NULL parameter");

	/* we do not actually write the option in the storage, we simply
	 * add it to the list in the block_handle
	 * we only check that the option is supported 
	 */
	switch (option->code)
	{
	case OPTION_ENDOFOPT:
		/* we do not write anything, since the section options will be closed by the library */
		return NTAR_SUCCESS;  
	case OPTION_COMMENT:
		ret_value = NTAR_SUCCESS;
		break;

	default:
		/* we invoke the plugin in order to see if the option is supported
		 * in this block
		 */
		ret_value = block_handle->plugin_data->validate_option(block_handle->plugin_state, option);
	}

	if (ret_value == NTAR_SUCCESS)
	{	/* insert the option at the end of the linked list */
		if (block_handle->options == NULL)
		{	/* empty list */
			block_handle->options = option;
			option->next = NULL;
		}
		else
		{	/* reach the end of the list and add a new element */
			/* TODO this code could be optimized by using a tail pointer */
			for (iterator = block_handle->options; iterator->next != NULL; iterator = iterator->next)
			{
				if (iterator == option)
					return NTAR_FAILURE_DUPPTR;
			}

			iterator->next = option;
			option->next = NULL;
		}
	}

	return ret_value;
}

int ntar_get_next_block(ntar_section_handle *section_handle, ntar_block_handle** pblock_handle)
{	
	ntar_foff current_position;
	block_header bh;
	int ret_value;

	/* we can retrieve a new block only if the preceding one has been closed */
	if (section_handle->block_opened)
		return NTAR_FAILURE_BLOCKNOTCLOSED;
	
	/* if we are the end of the section, and we already read the BH, simply
	 * return NOMOREBLOCKS
	 */
	if (section_handle->reached_end_of_section)
	{
		return NTAR_FAILURE_NOMOREBLOCKS;
	}
		
	/* if the previous block/section has been closed,
	 * the file pointer points to the first byte of
	 * a block header (or to EOF)
	 * We try to read the next block header.
	 * this fcn reads a shb header, as well, in this case
	 * we cache the block header in the file handle, and return
	 * failure
	 */
	ret_value = section_handle->file_handlers.read_handler(
		section_handle->file_handlers.handle,
        &bh, 
		sizeof(block_header),
		NULL);
	
	if (ret_value != NTAR_SUCCESS)
	{
		/* in case of EOF, shouldn't it be a NTAR_FAILURE_NOMOREBLOCKS?? */
		return ret_value;
	}

	/* we see if it's a SHB, maybe corrupted by an FTP transfer */
	if (   bh.block_type == SHB_BLOCK_TYPE 
		   || MAYBE_IS_SHB_FTP_MESSED(bh.block_type)
		)
	{  /* it's probably and SHB, return NOMOREBLOCKS
	    */
		section_handle->file_handle->last_bh = bh;
		section_handle->reached_end_of_section = TRUE;
		return NTAR_FAILURE_NOMOREBLOCKS;
	}

	/* ok, it's a normal block. Let's fix the byte order */
	if ( section_handle->byte_order != HOST_BYTE_ORDER)
	{
		bh.block_total_length = NTAR_SWAP_32BITS(bh.block_total_length);
		bh.block_type = NTAR_SWAP_32BITS(bh.block_type);
	}
 	/* store the beginning of the block, it the file support seeks 
	 * This is used to skip at the end of the block when we close it
	 */
	if (section_handle->file_handlers.seek_handler != NULL)
	{
		ret_value = section_handle->file_handlers.seek_handler(
			section_handle->file_handlers.handle,
			0,
			SEEK_CUR,
            &current_position);

		if (ret_value == NTAR_SUCCESS)
			/* TODO shouldn't we return an error?? */
			current_position -= sizeof(block_header);
		else
			current_position = NTAR_POS_NOT_DEFINED;
	}
	else
		current_position = NTAR_POS_NOT_DEFINED;

	/* "allocate" the block handle by reusing the cached block of the 
	 * section handle. Reset the fields that are local to this block,
	 * basically the plugin info, the block handle and the start of the block
	 * on the file
	 */
	*pblock_handle = &section_handle->cache_block;
	(*pblock_handle)->bh = bh;
	(*pblock_handle)->are_block_data_read = FALSE;
	(*pblock_handle)->plugin_data = NULL;
	(*pblock_handle)->plugin_state = NULL;
	(*pblock_handle)->options = NULL;

	(*pblock_handle)->block_start = current_position;

	/* signal the section handle that the block is opened
	 */
	section_handle->block_opened = TRUE;
    
	/* fix the pointers used to move backwards in the file */
	section_handle->read_iterator.prev_pos = section_handle->read_iterator.curr_pos;
	section_handle->read_iterator.curr_pos = section_handle->read_iterator.next_pos;
	section_handle->read_iterator.next_pos = current_position + bh.block_total_length;

	return NTAR_SUCCESS;
}

int ntar_get_block_data(ntar_block_handle* block_handle, void** data)
{
	int ret_value;
		
	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(data != NULL, __FUNCTION__ " NULL parameter");

	/* first we check that the plugin has been initialized 
	 * the field plugin data is NULL if the plugin has not been initialized 
	 */
	if (block_handle->plugin_data == NULL)
	{
		/* we retrieve the plugin for such block */
		block_handle->plugin_data = get_plugin_data(block_handle->bh.block_type);
		if (block_handle->plugin_data == NULL)
			return NTAR_FAILURE_INVALID_ID;
		/* the plugin must be initialized for this block */
		ret_value = block_handle->plugin_data->init(block_handle->plugin_state);

		if (ret_value != NTAR_SUCCESS)
		{  /* if the inizialization fails, set the plugin data to NULL and return the error */
			block_handle->plugin_data = NULL;
			return ret_value;
		}
	}
	
	if (!block_handle->are_block_data_read)
	{

		ret_value = read_raw_block_data(block_handle);
		if (ret_value != NTAR_SUCCESS)
			return ret_value;

		ret_value = decode_block_data(block_handle);
		if (ret_value != NTAR_SUCCESS)
			return ret_value;

		ret_value = decode_block_options(block_handle);
		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	}

	*data = block_handle->block_data;
		
	return NTAR_SUCCESS;

}

int ntar_get_block_type(ntar_block_handle* block_handle, u_int32 *pblock_type)
{
	NTAR_ASSERT(block_handle != NULL, __FUNCTION__ " NULL parameter");
	NTAR_ASSERT(pblock_type != NULL, __FUNCTION__ " NULL parameter");

	*pblock_type = block_handle->bh.block_type;

	return NTAR_SUCCESS;
}

int ntar_get_block_options(ntar_block_handle *block_handle, ntar_option **options)
{
	int ret_value;
	void *ptr;
	
	ret_value = NTAR_SUCCESS;

	if (!block_handle->are_block_data_read)
		ret_value = ntar_get_block_data(block_handle, &ptr);

	*options = block_handle->options;

	return ret_value;
}
