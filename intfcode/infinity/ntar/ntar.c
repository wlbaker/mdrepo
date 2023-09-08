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
#include "version.h"

/* This function does nothing more than using the internal, predefined read/write/seek
 * callbacks in ntar_file_handlers, and then call ntar_open_by_handlers
 */
int	ntar_open(char* filename, char* flags, ntar_file_handle** pfile_handle)
{
	int result;
	
	ntar_file_handlers file_handlers;

	/* Open the file with our internal open handler
	 */
	result = ntar_native_file_open(filename, flags, &file_handlers);

	if (result != NTAR_SUCCESS)
		return result;

    /* now let's try to open the ntar file using our callbacks.
	 */
	result = ntar_open_by_handlers(file_handlers, flags, pfile_handle);
		
	if (result == NTAR_SUCCESS)
	{
		/* if we successfully open the ntar file, set a flag in the file_handle
		 * that reminds us that we are using internal handlers.
		 * This flag is later used when closing the file, in order to know
		 * that we need to call our internal closing function (ntar_native_file_close)
		 */
		(*pfile_handle)->using_internal_handlers = TRUE;
		return NTAR_SUCCESS;
	}
	else
	{
		/* close the file with our internal calls and return the error
		 */
		ntar_native_file_close(file_handlers);
		return result;
	}
}

//TODO: the flags do not make any sense: we know if we are reading/writing by looking at the callbacks.
// what if the user passes both the read and the write handler?
int ntar_open_by_handlers(ntar_file_handlers file_handlers, char* flags, ntar_file_handle** pfile_handle)
{
	ntar_file_handle *new_file_handle;
	int file_mode;
	block_header bh;

	/* convert the flags to the proper integer open file mode
	 */
	if ( stricmp(flags,NTAR_OPEN_READ)		== 0) 
		file_mode = NTAR_FILEMODE_READ;
	else 
	if ( stricmp(flags,NTAR_OPEN_WRITE)		== 0)
		file_mode = NTAR_FILEMODE_WRITE;
	else //TODO
	if ( stricmp(flags,NTAR_OPEN_APPEND)	== 0)
		file_mode = NTAR_FILEMODE_WRITE;
	else //TODO
	if ( stricmp(flags,NTAR_OPEN_CREATE) == 0)
		file_mode = NTAR_FILEMODE_WRITE;
	else
	{
		/* unknown mode, return error */
		return NTAR_FAILURE_INVALIDPARAMETER;
	}

	/* check that the user passed a valid write callback in case
	 * the file is opened in write mode
	 */
	if (file_mode == NTAR_FILEMODE_WRITE)
	{
		if (file_handlers.write_handler == NULL)
		{
			return NTAR_FAILURE_INVALIDPARAMETER;
		}
	}

	/* check that the user passed a valid read callback in case
	 * the file is opened in read mode
	 */
	if (file_mode == NTAR_FILEMODE_READ)
	{
		if (file_handlers.read_handler == NULL)
		{
			return NTAR_FAILURE_INVALIDPARAMETER;
		}
	}

	/* NOTE: we do not check for the existence of a seek callback,
	 * because it's optional 
	 */

	if ( file_mode == NTAR_FILEMODE_READ )
	{
		int read_result;

		/* we read the 1st block header and check that it could be a proper file */
		read_result = file_handlers.read_handler(file_handlers.handle, &bh, sizeof(bh), NULL);
		
		if (read_result != NTAR_SUCCESS)
			return read_result;

		if (bh.block_type != SHB_BLOCK_TYPE)
		{
			//TODO: the procedure to detect a file downloaded in FTP in ASCII mode
			//should be here
			return NTAR_FAILURE_INVALIDFILE;
		}

		/* now we create the handle and fill the appropriate stuff inside */
		new_file_handle = (ntar_file_handle*) malloc (sizeof(ntar_file_handle));
		if (new_file_handle == NULL)
		{
			return NTAR_FAILURE_NOMEM;
		}

		/* we initialize all the structures to 0, including the cached 
		 * structures ->section_handle and ->section_handle->block_handle
		 */
		memset(new_file_handle, 0, sizeof(ntar_file_handle));

		new_file_handle->file_handlers = file_handlers;
		new_file_handle->section_opened = FALSE;
		new_file_handle->last_bh = bh;
		new_file_handle->read_iterator.curr_pos = NTAR_POS_NOT_DEFINED;
		new_file_handle->read_iterator.prev_pos = NTAR_POS_NOT_DEFINED;
		new_file_handle->read_iterator.next_pos = NTAR_BEGINNING_OF_FILE;
		new_file_handle->file_mode = file_mode;
		new_file_handle->using_internal_handlers = FALSE;

		/* here we initialize the local data of the cached section */
		new_file_handle->cache_section.file_handle = new_file_handle;
		new_file_handle->cache_section.file_handlers = file_handlers;

		/* here we initialize the local data of the cached block in the cached section */
		new_file_handle->cache_section.cache_block.section_handle = &(new_file_handle->cache_section);
		new_file_handle->cache_section.cache_block.file_handlers = file_handlers;

		*pfile_handle = new_file_handle;
		return NTAR_SUCCESS;
	}
	else
	if (file_mode == NTAR_FILEMODE_WRITE)
	{
		/* now we create the handle and fill the appropriate stuff inside */
		new_file_handle = (ntar_file_handle*) malloc (sizeof(ntar_file_handle));
		if (new_file_handle == NULL)
		{
			return NTAR_FAILURE_NOMEM;
		}

		/* we initialize all the structures to 0, including the cached 
		 * structures ->section_handle and ->section_handle->block_handle
		 */
		memset(new_file_handle, 0, sizeof(ntar_file_handle));

		new_file_handle->file_handlers = file_handlers;
		new_file_handle->section_opened = FALSE;

		/* here we initialize the local data of the cached section */
		new_file_handle->cache_section.file_handle = new_file_handle;
		new_file_handle->cache_section.file_handlers = file_handlers;

		/* here we initialize the local data of the cached block in the cached section */
		new_file_handle->cache_section.cache_block.section_handle = &(new_file_handle->cache_section);
		new_file_handle->cache_section.cache_block.file_handlers = file_handlers;

		*pfile_handle = new_file_handle;
		return NTAR_SUCCESS;
	}

	NTAR_ASSERT(1!=1, __FUNCTION__ " - trying to open a file in an unknown method");

	return NTAR_FAILURE;
}

int ntar_close(ntar_file_handle* file_handle)
{
	switch (file_handle->file_mode)
	{
	case NTAR_FILEMODE_CREATE:
	case NTAR_FILEMODE_WRITE:
	case NTAR_FILEMODE_APPEND:
		/* first we check that the current section has been closed */
		if (file_handle->section_opened)
			return NTAR_FAILURE_SECTIONNOTCLOSED;
		/* now we can simply close the FILE structure */
		if (file_handle->using_internal_handlers)
		{
			ntar_native_file_close(file_handle->file_handlers);
		}
		break;

	case NTAR_FILEMODE_READ:
		/* first we check that the current section has been closed */
		if (file_handle->section_opened)
			return NTAR_FAILURE_SECTIONNOTCLOSED;
		
		/* now we can simply close the FILE structure */
		if (file_handle->using_internal_handlers)
		{
			ntar_native_file_close(file_handle->file_handlers);
		}
		break;

	default:
		/* it's an invalid mode, we return FAILURE since we do not know what to do */
		return NTAR_FAILURE;
	}

	/* here we free all the buffers used in pooling by the cached section
	 * and by the cached block
	 */
	if (file_handle->cache_section.cache_block.raw_data_buffer_length > 0)
		free(file_handle->cache_section.cache_block.raw_data_buffer);
		
	if (file_handle->cache_section.cache_block.data_buffer_length > 0)
		free(file_handle->cache_section.cache_block.data_buffer);

	if (file_handle->cache_section.cache_block.options_buffer_length > 0)
		free(file_handle->cache_section.cache_block.options_buffer);

	if (file_handle->cache_section.options_buffer_length > 0)
		free(file_handle->cache_section.options_buffer);

	if (file_handle->cache_section.raw_options_buffer_length > 0)
		free(file_handle->cache_section.raw_options_buffer);

	free(file_handle);
	return NTAR_SUCCESS;
}

int reallocate_memory(void **buffer, size_t *buffer_size, size_t new_size) 
{
	if (new_size == 0)
		return NTAR_SUCCESS;
	
	if (new_size > *buffer_size)
	{
		if (*buffer != NULL)
		{
			free(*buffer);
			*buffer = NULL;
			*buffer_size = 0;
		}

		*buffer = (char*)malloc(new_size);
		if (*buffer == NULL)
			return NTAR_FAILURE_NOMEM;

		*buffer_size = new_size;
	}

	return NTAR_SUCCESS;

}

int ntar_getversion(char* buffer, u_int32 *pbuffer_size)
{
	size_t ver_len;

	if (buffer == NULL && *pbuffer_size != 0)
	{
		return NTAR_FAILURE;
	}

	ver_len = strlen(NTAR_VER_STRING) + 1;

	if (*pbuffer_size < ver_len)
	{
		*pbuffer_size = (u_int32)ver_len;
		return NTAR_FAILURE_SMALLBUFFER;
	}
	else
	{
		memcpy(buffer, NTAR_VER_STRING, ver_len);
		*pbuffer_size = (u_int32)ver_len;
		return NTAR_SUCCESS;
	}
}
