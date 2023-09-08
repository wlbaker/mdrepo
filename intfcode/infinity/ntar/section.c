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

#include "option.h"
#include "section.h"



/*!
	\brief This function closes a section that was opened in read mode.
	It's another backend of ntar_close_section()
	\param section_handle section to close.
	\return 
	  - \ref NTAR_SUCCESS on success
	  - one of the NTAR_FAILURE_xxx values on failure
*/
static int close_section_read_mode(ntar_section_handle *section_handle)
{
	int ret_value;
	ntar_foff new_position = NTAR_POS_NOT_DEFINED;

	/* first we need to check that all the blocks have been closed */
	if (section_handle->block_opened)
		return NTAR_FAILURE_BLOCKNOTCLOSED;

	/* if the file support seeking, and we have a valid section length in the header 
	 * we use that number to skip at the end of the section 
	 */
	if (section_handle->file_handlers.seek_handler != NULL && section_handle->shb.section_length != -1)
	{
		/* we move the file pointer at the end of the section */
		new_position = section_handle->block_start 
			+ NTAR_ALIGN_32BITS(section_handle->bh.block_total_length)
			+ section_handle->shb.section_length;

		ret_value = section_handle->file_handlers.seek_handler(
			section_handle->file_handlers.handle,
			new_position, 
			SEEK_SET,
			NULL);

		if (ret_value != NTAR_SUCCESS)
			return ret_value;

		/* and we read the block header of the next block */
		ret_value = section_handle->file_handlers.read_handler(
			section_handle->file_handlers.handle,
			&section_handle->file_handle->last_bh,
			sizeof(block_header), 
			NULL);

		if (ret_value != NTAR_SUCCESS && ret_value != NTAR_FAILURE_EOF)
		{	/* we should not return error if we reached the end of file
			* If we cannot read the block header, we return success
			* when we try to read the next section, get_next_section
			* will fail while trying to read the shb.
			*/
			return ret_value;
		}
	}
	else
	{
		/* iether the file doesn't support seeking, 
		 * or we do not have the section length
		 * We move to the end of the file by scanning all the blocks
		 */

		ntar_block_handle *block_handle;
		int ret_value;

		/* now we must scan all the blocks in the section until we reach the end of the section
		 */
		ret_value = ntar_get_next_block(section_handle, &block_handle); 
		while(ret_value == NTAR_SUCCESS)
		{
			ret_value = ntar_close_block(block_handle);
			if (ret_value != NTAR_SUCCESS)
				return ret_value;

			ret_value = ntar_get_next_block(section_handle, &block_handle);
		}

		if (ret_value != NTAR_FAILURE_NOMOREBLOCKS && ret_value != NTAR_FAILURE_EOF)
		{
			return ret_value;
		}
	}
	/* TODO maybe we should check the section size obtained scanning the file
	 * with the one written in the shb
	 * We must be careful with the byte order
	 */

	/* first of all we correct the iterator
	 */
	/* TODO THIS CODE HAS BEEN COMMENTED BECAUSE FPOS_T IS NOT AN
	 * INTEGRAL TYPE ON ALL PLATFROMS (I.E. NO + and -)
	 */
	//if (section_handle->file_handle->read_iterator.next_pos == -1 && section_handle->file_data.support_seeks)
	//	section_handle->file_handle->read_iterator.next_pos = new_position;

	/* we signal the file handle that the section has been closed */
	section_handle->file_handle->section_opened = FALSE;

	return NTAR_SUCCESS;
}


static int read_section_options(ntar_section_handle *section_handle)
{
	size_t requested_bytes;
	option_header original_oh;
	option_header *oh;
	option_header *new_oh;
	size_t sentinel;
	char* options_temp_ptr;
	ntar_option *option;
	ntar_option *old_option;
	size_t option_length;
	int ret_value;

	requested_bytes = section_handle->bh.block_total_length 
		- sizeof(block_header) 
		- sizeof(section_header_block) 
		- sizeof(u_int32);

	if (requested_bytes == 0)
	{
		section_handle->options = NULL;
		return NTAR_SUCCESS;
	}

	ret_value = reallocate_memory(
		(void**)&(section_handle->raw_options_buffer), 
		&(section_handle->raw_options_buffer_length), 
		requested_bytes);
	if (ret_value != NTAR_SUCCESS)
		return ret_value;

	ret_value = section_handle->file_handlers.read_handler(
			section_handle->file_handlers.handle,
			section_handle->raw_options_buffer, 
			requested_bytes, 
			NULL);
	
	if (ret_value != NTAR_SUCCESS)
		return ret_value;

	requested_bytes = 0;

	sentinel = 0;
	oh = (option_header*)section_handle->raw_options_buffer;
	sentinel += sizeof(option_header);

	while(sentinel <= section_handle->raw_options_buffer_length && !IS_END_OPTION(*oh))
	{
		original_oh = *oh;
		if (section_handle->byte_order != HOST_BYTE_ORDER)
		{
			oh->option_code = NTAR_SWAP_16BITS(oh->option_code);
			oh->option_length = NTAR_SWAP_16BITS(oh->option_length);
		}
		
		sentinel += + NTAR_ALIGN_32BITS(oh->option_length) + sizeof(option_header);
		if (sentinel > section_handle->raw_options_buffer_length + 1)
			continue;
	
		switch(oh->option_code)
		{
			case OPTION_ENDOFOPT:
				break;		
			case OPTION_COMMENT:
			case SHB_OPTION_HARDWARE:
			case SHB_OPTION_OS:
			case SHB_OPTION_APPLICATION:

			read_option_string(oh, section_handle->byte_order, NULL,&option_length);
			requested_bytes += NTAR_ALIGN_NATIVE(option_length);
			requested_bytes += sizeof(ntar_option);
			break;
		default:
			break;
		}
			
		new_oh = (option_header*)((char*)oh + NTAR_ALIGN_32BITS(oh->option_length) + sizeof(option_header));
		*oh = original_oh;
		oh = new_oh;

	}

	ret_value = reallocate_memory(
		(void**)&(section_handle->options_buffer), 
		&(section_handle->options_buffer_length), 
		requested_bytes);
	if (ret_value != NTAR_SUCCESS)
		return ret_value;

	/* let's copy the options */
	sentinel = 0;
	oh = (option_header*)section_handle->raw_options_buffer;
	options_temp_ptr = section_handle->options_buffer;
	sentinel += sizeof(option_header);
	old_option = NULL;

	while(sentinel <= section_handle->raw_options_buffer_length && !IS_END_OPTION(*oh))
	{
		if (section_handle->byte_order != HOST_BYTE_ORDER)
		{
			oh->option_code = NTAR_SWAP_16BITS(oh->option_code);
			oh->option_length = NTAR_SWAP_16BITS(oh->option_length);
		}
		
		sentinel += + NTAR_ALIGN_32BITS(oh->option_length) + sizeof(option_header);
		if (sentinel > section_handle->raw_options_buffer_length + 1)
			continue;
	
		switch(oh->option_code)
		{
			case OPTION_ENDOFOPT:
				break;		
			case OPTION_COMMENT:
			case SHB_OPTION_HARDWARE:
			case SHB_OPTION_OS:
			case SHB_OPTION_APPLICATION:

				option = (ntar_option*)options_temp_ptr;
				option->data = options_temp_ptr + sizeof(ntar_option);
				option->code = oh->option_code;
				if (old_option != NULL)
					old_option->next = option;
				option->next = NULL;
				old_option = option;
				options_temp_ptr += sizeof(ntar_option);
				read_option_string(oh, section_handle->byte_order, options_temp_ptr,&option_length);
			
				requested_bytes += NTAR_ALIGN_NATIVE(option_length);
				requested_bytes += sizeof(ntar_option);
				options_temp_ptr += NTAR_ALIGN_NATIVE(option_length);

				break;
			default:
				break;
		}
			
		oh = (option_header*)((char*)oh + NTAR_ALIGN_32BITS(oh->option_length) + sizeof(option_header));

	}

	if (old_option != NULL)
		section_handle->options = (ntar_option*)section_handle->options_buffer;
	else
		section_handle->options = NULL;

	return NTAR_SUCCESS;
}

static int ntar_read_section(ntar_file_handle *file_handle)
{
	block_header bh;
	section_header_block shb;
	int byte_order;
	int ret_value;
	ntar_section_handle *section_handle;
	ntar_foff	current_position;
	u_int32	trailer_block_size;

	NTAR_ASSERT(file_handle->section_opened == FALSE, __FUNCTION__ " current_section should be null");
	
	if (file_handle->file_handlers.seek_handler != NULL)
	{
		ret_value = file_handle->file_handlers.seek_handler(
			file_handle->file_handlers.handle,
			0,
			SEEK_CUR,
			&current_position);
		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}

		/* we suppose that we have already read the bh, 
		 * so the file pointer is not at the proper position
		 */
		current_position -= sizeof(block_header);
	}
	else
		current_position = NTAR_POS_NOT_DEFINED;

	bh = file_handle->last_bh;

	if (bh.block_type == SHB_BLOCK_TYPE) /* it's palyndromic, so no swaps are needed. */
	{
		/* ok, let's check the block magic:
		 * we read the standard header
		 */

		ret_value = file_handle->file_handlers.read_handler(
			file_handle->file_handlers.handle,
			&shb, 
			sizeof(shb),
			NULL);

		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}
			
		if (shb.byte_order_magic == SHB_MAGIC)
			byte_order = HOST_BYTE_ORDER;
		else
		if (shb.byte_order_magic == NTAR_SWAP_32BITS(SHB_MAGIC))
			byte_order = SWAPPED_HOST_BYTE_ORDER;
		else
		{
			ret_value = NTAR_FAILURE_INVALIDFILE;
			goto error;
		}
	}
	else
	{
		/* ok, the file is wrong, let's check for
		 * the magic somewhere
		 */
		/* this code is an hack to recognize files
		 * downloaded in aSCII format
		 */
		int i;
		u_int32 supposed_magic;
		char magic_buffer[sizeof(shb) + sizeof(bh)];
		
		ret_value = file_handle->file_handlers.read_handler(
			file_handle->file_handlers.handle,
            &shb, 
			sizeof(shb),
			NULL);

		if (ret_value != NTAR_SUCCESS)
		{
			goto error;
		}
	
		memcpy(magic_buffer, &bh, sizeof(bh));
		memcpy(magic_buffer + sizeof(bh), &shb, sizeof(shb));

		for (i = 2; i < sizeof(magic_buffer) - sizeof(u_int32); i++)
		{
			((char*)(&supposed_magic))[0] = magic_buffer[i];
			((char*)(&supposed_magic))[1] = magic_buffer[i+1];
			((char*)(&supposed_magic))[2] = magic_buffer[i+2];
			((char*)(&supposed_magic))[3] = magic_buffer[i+3];
			
			if (supposed_magic == SHB_MAGIC || supposed_magic == NTAR_SWAP_32BITS(SHB_MAGIC))
			{
				ret_value = NTAR_FAILURE_ASCIIDLFILE;
				goto error;
			}
		}

		ret_value = NTAR_FAILURE_INVALIDFILE;
		goto error;
	}
		
	if (byte_order != HOST_BYTE_ORDER)
	{
		shb.major_version = NTAR_SWAP_16BITS(shb.major_version);
		shb.minor_version = NTAR_SWAP_16BITS(shb.minor_version);
		shb.section_length = NTAR_SWAP_64BITS(shb.section_length);
		bh.block_total_length = NTAR_SWAP_32BITS(bh.block_total_length);
		bh.block_type = SHB_BLOCK_TYPE;
	}
	
	section_handle = &file_handle->cache_section;
	section_handle->bh = bh;
	section_handle->shb = shb;
	section_handle->byte_order = byte_order;
	section_handle->block_opened = FALSE;
	section_handle->shb_header_length = bh.block_total_length;
	section_handle->block_start = current_position;
	section_handle->bh = bh;
	section_handle->options = NULL;
	section_handle->reached_end_of_section = FALSE;

	section_handle->cache_block.byte_order = byte_order;

	/* now we read all the section options */
	ret_value = read_section_options(section_handle);
	if (ret_value != NTAR_SUCCESS)
			goto error;

	/* and arrive at the end of the section, over the trailer */
	ret_value = file_handle->file_handlers.read_handler(
		file_handle->file_handlers.handle,
		&trailer_block_size, 
		sizeof(trailer_block_size), 
		NULL);

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}

	/* let's check that the block is consistent */
	if (byte_order != HOST_BYTE_ORDER)
		trailer_block_size = NTAR_SWAP_32BITS(trailer_block_size);

	if (trailer_block_size != bh.block_total_length)
	{
		ret_value = NTAR_FAILURE_MALFORMED_BLOCK;
		goto error;
	}

	file_handle->read_iterator.prev_pos = file_handle->read_iterator.curr_pos;
	file_handle->read_iterator.curr_pos = file_handle->read_iterator.next_pos;
	if (shb.section_length == (u_int64)-1)
		file_handle->read_iterator.next_pos = NTAR_POS_NOT_DEFINED;
	else
		file_handle->read_iterator.next_pos = current_position + shb.section_length + sizeof(block_header);

	file_handle->section_opened = TRUE;

	return NTAR_SUCCESS;

error:

	return ret_value;

}

/*!
	\brief This function closes a section that was opened in write mode.
	It's the backend of ntar_close_section()
	\param section_handle section to close.
	\return 
	  - \ref NTAR_SUCCESS on success
	  - one of the NTAR_FAILURE_xxx values on failure
*/
static int close_section_write_mode(ntar_section_handle *section_handle)
{
	int ret_value;

	/* first we need to check that all the blocks have been closed */
	if (section_handle->block_opened)
		return NTAR_FAILURE_BLOCKNOTCLOSED;

	/* now we check that the options have been closed */
	if (!section_handle->header_written)
	{
		ret_value = write_section_header_block(section_handle);
		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	}
	
	if (section_handle->file_handlers.seek_handler != NULL)
	{
		ntar_foff current_position, new_position;

		/* we retrieve the current position of the file to compute the 
		 * section length
		 */
		ret_value = section_handle->file_handlers.seek_handler(
			section_handle->file_handlers.handle,
			0, 
			SEEK_CUR,
			&current_position);

		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	
		/* now we move to the beginning of the section header block */
		new_position = section_handle->block_start + sizeof(block_header);

		ret_value = section_handle->file_handlers.seek_handler(
			section_handle->file_handlers.handle,
			new_position,
			SEEK_SET,
			NULL);

		if (ret_value != NTAR_SUCCESS)
			return ret_value;

		/* we recreate the section header block */
		section_handle->shb.section_length = current_position 
			- section_handle->block_start 
			- section_handle->bh.block_total_length;

		/* and we write it to disk */
		ret_value = section_handle->file_handlers.write_handler(
			section_handle->file_handlers.handle,
			&(section_handle->shb), 
			sizeof(section_header_block));
		
		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	
		/* then we move the file pointer to the original position 
		 * at the end of the section
		 */
		ret_value = section_handle->file_handlers.seek_handler(
			section_handle->file_handlers.handle,
			current_position,
			SEEK_SET,
			NULL);
		
		if (ret_value != NTAR_SUCCESS)
			return ret_value;
	}
	
	/* we inform the ntar_header that the section has been closed */
	section_handle->file_handle->section_opened = FALSE;

	return NTAR_SUCCESS;

}

/*!
	\note length is on 32 bits, sinve the total size of a block is on 32 bits
*/
static int get_section_options_length(ntar_section_handle *section_handle, u_int32 *length)
{
	ntar_option *iterator;
	size_t option_length;

	NTAR_ASSERT(section_handle != NULL, __FUNCTION__ " NULL parameter");

	*length = 0;

	if (section_handle->options == NULL)
	{
		return NTAR_SUCCESS;
	}
	
	for (iterator = section_handle->options; iterator != NULL; iterator = iterator->next)
	{
		option_length = 0;

		switch (iterator->code)
		{
		case OPTION_ENDOFOPT:
			continue;
		
		case OPTION_COMMENT:
		case SHB_OPTION_HARDWARE:
		case SHB_OPTION_OS:
		case SHB_OPTION_APPLICATION:

			write_option_string( iterator, NULL,&option_length);
			*length += (u_int32)option_length;
			break;
		default:
			return NTAR_FAILURE_INVALID_ID;
		}

	}

	write_null_option(NULL, &option_length);
	*length += (u_int32)option_length;

	return NTAR_SUCCESS;
}

static int write_section_options(ntar_section_handle *section_handle)
{
	ntar_option *iterator;
	char* buffer_pointer;
	size_t remaining_bytes;
	size_t option_length;
	int ret_value;

	NTAR_ASSERT(section_handle != NULL, __FUNCTION__ " NULL parameter");

	/* we suppose that the option_buffer is large enough to contain all the options
	 * otherwise we generate an assertion and we fail 
	 */

	if (section_handle->options == NULL)
	{
		return NTAR_SUCCESS;
	}

	buffer_pointer = section_handle->options_buffer;
	remaining_bytes = section_handle->options_buffer_length;
	
	for (iterator = section_handle->options; iterator != NULL; iterator = iterator->next)
	{
		option_length = remaining_bytes;

		switch (iterator->code)
		{
		case OPTION_ENDOFOPT:
			continue;
		
		case OPTION_COMMENT:
		case SHB_OPTION_HARDWARE:
		case SHB_OPTION_OS:
		case SHB_OPTION_APPLICATION:

			if (write_option_string( iterator, buffer_pointer,&option_length) != NTAR_SUCCESS)
				return NTAR_FAILURE; //TODO
			break;
		default:
			return NTAR_FAILURE_INVALID_ID;
		}

		buffer_pointer += option_length;
		remaining_bytes -= option_length;
	}

	if (write_null_option(buffer_pointer, &option_length) != NTAR_SUCCESS)
		return NTAR_FAILURE;

	remaining_bytes -= option_length;

	ret_value = section_handle->file_handlers.write_handler(
		section_handle->file_handlers.handle,
		section_handle->options_buffer, 
		section_handle->options_buffer_length - remaining_bytes);
	
	return ret_value;
}

/*!
	\brief This function writes the entire section header block header to file.
	It does not write the section header block itself.
	The section header block header is a block header, that contains the
	actual section header block.
	This function is called automatically when the first block is added to the 
	section, or when the section is closed.
	\param section_handle Handle to section to write.
*/
int write_section_header_block(ntar_section_handle *section_handle)
{
	int ret_value;
	u_int32 options_length;

	NTAR_ASSERT(section_handle != NULL, __FUNCTION__ " received a NULL paramter");
	NTAR_ASSERT(section_handle->header_written == FALSE, __FUNCTION__ " section block header already closed");

	/* we are sure that no blocks have been added, since the first call 
	   to add a block write the section_header
	 */

	/* First of all, check if it has options. 
	   In this case we need to close the options with the option terminator
	 */
	ret_value = get_section_options_length(section_handle, &options_length);

	if (ret_value != NTAR_SUCCESS)
		goto error;
	
	section_handle->bh.block_total_length = sizeof (block_header) 
		+ sizeof(section_header_block)
		+ options_length
		+ sizeof(u_int32);

	/* we write the block header */
	ret_value = section_handle->file_handlers.write_handler(
		section_handle->file_handlers.handle,
		&(section_handle->bh), 
		sizeof(block_header));

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}
	
	ret_value = section_handle->file_handlers.write_handler(
		section_handle->file_handlers.handle,
		&(section_handle->shb), 
		sizeof(section_header_block));

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}
	
	/* we need to reallocate the options buffer if it's too small */

	ret_value = reallocate_memory(
		(void**)&(section_handle->options_buffer), 
		&(section_handle->options_buffer_length), 
		options_length);
	if (ret_value != NTAR_SUCCESS)
		goto error;

	ret_value = write_section_options(section_handle);

	if (ret_value != NTAR_SUCCESS)
		goto error;

	ret_value = section_handle->file_handlers.write_handler(
		section_handle->file_handlers.handle,
		&(section_handle->bh.block_total_length), 
		sizeof(u_int32));

	if (ret_value != NTAR_SUCCESS)
	{
		goto error;
	}

	section_handle->header_written = TRUE;

	return NTAR_SUCCESS;

error:
	return ret_value;
}


int ntar_create_section(ntar_file_handle* file_handle, ntar_section_handle** psection_handle)
{
	int ret_value;
	ntar_section_handle *new_section;

	NTAR_ASSERT(file_handle != NULL, __FUNCTION__ " called with NULL parameter");

	/* first of all we check that the file has not been opened in read mode */
	if (file_handle->file_mode == NTAR_FILEMODE_READ)
	{
		ret_value = NTAR_FAILURE_WRITEONREADFILE;
		goto exit;
	}

	/* now we check that the current_section has been closed */
	if (file_handle->section_opened)
	{
		ret_value = NTAR_FAILURE_SECTIONNOTCLOSED;
		goto exit;
	}

	new_section = &(file_handle->cache_section);

	new_section->byte_order = HOST_BYTE_ORDER;
	new_section->cache_block.byte_order = HOST_BYTE_ORDER;
	new_section->header_written = FALSE;
	new_section->block_opened = FALSE;
	new_section->options = NULL;

	/* we need to store the beginning of the section 
	 * in order to close it properly 
	 */
	if (new_section->file_handlers.seek_handler != NULL)
	{
		ret_value = new_section->file_handlers.seek_handler(
			new_section->file_handlers.handle,
			0,
			SEEK_CUR,
            &(new_section->block_start));

		if (ret_value != NTAR_SUCCESS)
		{
			goto exit;
		}
	}

	new_section->bh.block_type = SHB_BLOCK_TYPE;
	/*
		We do not know the length of the block until we close it 
	
		new_section->bh.block_total_length = ??;
	*/
	
	/* now we create the section header block */
	new_section->shb.byte_order_magic = SHB_MAGIC;
	new_section->shb.major_version = CURRENT_MAJOR_VERSION;
	new_section->shb.minor_version = CURRENT_MINOR_VERSION;
	/* we use the invalid value, so that the SHB hopefully remains valid 
	 * even if we do not close the section
	 */
	new_section->shb.section_length = (u_int64)-1; 

	/* we return the allocated section and we inform the file_handle 
	 * that a section has been opened
	 */
	*psection_handle = new_section;
	file_handle->section_opened = TRUE;

	ret_value = NTAR_SUCCESS;

exit:
	return ret_value;
}

int ntar_close_section(ntar_section_handle* section_handle)
{
	NTAR_ASSERT(section_handle != NULL, __FUNCTION__ " received a NULL parameter");
	NTAR_ASSERT(section_handle->file_handle != NULL, __FUNCTION__ " section_handle->file_handle is NULL");

	switch(section_handle->file_handle->file_mode)
	{
	case NTAR_FILEMODE_READ:
        return close_section_read_mode(section_handle);

	case NTAR_FILEMODE_WRITE:
	case NTAR_FILEMODE_APPEND:
	case NTAR_FILEMODE_CREATE:
        return close_section_write_mode(section_handle);

	default:
		return NTAR_FAILURE;
	}
}

int ntar_add_section_option(ntar_section_handle* section_handle, ntar_option *option)
{
	NTAR_ASSERT(section_handle != NULL, __FUNCTION__ " NULL parameter");

	/* we can add options only if we have not closed the block header */
	if (section_handle->header_written)
		//TODO add a better code
		return NTAR_FAILURE;

	/* we only check that the option is supported */
	switch (option->code)
	{
	case OPTION_ENDOFOPT:
//		return NTAR_SUCCESS;  /* we do not write anything, since the section options will be closed by the library */
	
	case OPTION_COMMENT:
	case SHB_OPTION_HARDWARE:
	case SHB_OPTION_OS:
	case SHB_OPTION_APPLICATION:
		/* TODO the insertion is at the head, so the options are written 
		 * upside down. Maybe it would be better to add the option at the end
		 */
		option->next = section_handle->options;
		section_handle->options = option;	
		return NTAR_SUCCESS;

	default:
		return NTAR_FAILURE_INVALID_ID;
	}
}

int ntar_get_next_section(ntar_file_handle *file_handle, ntar_section_handle** psection_handle)
{
	int ret_value;
	if (file_handle->section_opened)
		return NTAR_FAILURE_BLOCKNOTCLOSED;

	ret_value = ntar_read_section(file_handle);
	*psection_handle = &(file_handle->cache_section);
	return ret_value;
}



int ntar_get_section_options(ntar_section_handle* section_handle, ntar_option **options)
{
	*options = section_handle->options;
	return NTAR_SUCCESS;
}
