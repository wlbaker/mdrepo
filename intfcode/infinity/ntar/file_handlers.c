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

#ifndef WIN32
#define _LARGEFILE_SOURCE 
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#endif

#include "ntar_int.h"

#ifdef WIN32
#define NTAR_FOPEN_READ_MODE	"rb"
#define NTAR_FOPEN_WRITE_MODE	"wb"
#else
#define NTAR_FOPEN_READ_MODE	"r"
#define NTAR_FOPEN_WRITE_MODE	"w"
#endif

int ntar_native_file_write(void *handle, void* buffer, size_t size)
{
	FILE *fp = (FILE*)handle;
	size_t fwrite_result;

	fwrite_result = fwrite(buffer, size, 1, fp);

	if (fwrite_result == 1)
		return NTAR_SUCCESS;
	else
		return ntar_convert_errno(errno);
}

int ntar_native_file_read(void *handle, void* buffer, size_t size, size_t *read_bytes)
{
	FILE *fp = (FILE*)handle;
	size_t fread_result;

	fread_result = fread(buffer, 1, size, fp);

	if (read_bytes != NULL)
		*read_bytes = fread_result;

	if (fread_result == size)
		return NTAR_SUCCESS;

	if (feof(fp))
		return NTAR_FAILURE_EOF;
	else
		return ntar_convert_errno(errno);
}

int ntar_native_file_seek(void *handle, ntar_foff new_position, int origin, ntar_foff *old_position)
{
#if (defined WIN32) || (defined __MINGW32__)
	FILE *fp = (FILE*)handle;
	ntar_foff old_position_int;

	NTAR_ASSERT(sizeof(u_int64) == sizeof(ntar_foff), "native fseek types mismatch.");

	switch(origin)
	{
	case SEEK_SET:
		if (old_position != NULL)
		{
			if (fgetpos(fp, old_position) != 0)
				return NTAR_FAILURE_IOREAD;
		}

		if (fsetpos(fp, &new_position) != 0)
			return NTAR_FAILURE_IOREAD;
		else
			return NTAR_SUCCESS;

	case SEEK_CUR:
		if (new_position == 0)
		{
			if (old_position != NULL)
				if (fgetpos(fp, old_position) != 0)
					return NTAR_FAILURE_IOREAD;

			return NTAR_SUCCESS;
		}
		else
		{
			if (fgetpos(fp, &old_position_int) != 0)
				return NTAR_FAILURE_IOREAD;

			if (old_position != NULL)
				*old_position = old_position_int;

			new_position += old_position_int;

			if (fsetpos(fp, &new_position) != 0)
				return NTAR_FAILURE_IOREAD;
			else
				return NTAR_SUCCESS;
		}

	case SEEK_END:
	default:
		return NTAR_FAILURE;


	}

	//
	//This code does not work in read mode because of the caching done by the CRT FILE functions.

	//FILE *fp = (FILE*)handle;
	//__int64 lseeki64_result;

	//NTAR_ASSERT(sizeof(u_int64) == sizeof(ntar_foff), "native fseek types mismatch.");

	//fflush(fp);
	//lseeki64_result = _lseeki64(_fileno(fp), new_position, origin);

	//if (old_position!= NULL)
	//	*old_position = lseeki64_result;

	//if	(lseeki64_result == -1L)
	//	return ntar_convert_errno(errno);
	//else
	//	return NTAR_SUCCESS;

#else
	FILE *fp = (FILE*)handle;
	ntar_foff old_position_int;
	int fseeko_result;

	NTAR_ASSERT(sizeof(off_t) == sizeof(ntar_foff), "native fseek types mismatch.");
	
	if (old_position != NULL)
		*old_position = ftello(fp);

	fseeko_result = fseeko(fp, new_position,origin);

	if (fseeko_result != 0)
		return ntar_convert_errno(errno);

	return NTAR_SUCCESS;

#endif

}

int ntar_native_file_open(char *filename, char *flags, ntar_file_handlers *file_handlers)
{
	FILE *fp;
	int file_mode;
	int support_seeks;

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
		return NTAR_FAILURE;
	}

	if ( file_mode == NTAR_FILEMODE_READ )
	{
		if (filename == NULL)
		{
			/* we should use stdin, and stdin does not support seeks */
			fp = stdin;
#ifdef WIN32
			_setmode(_fileno(fp), _O_BINARY);
#endif
			support_seeks = FALSE;
		}
		else
		{
			fp = fopen(filename, NTAR_FOPEN_READ_MODE);

			if (fp == NULL)
				return ntar_convert_errno(errno);

			/* let's see if it supports fseek/fsetpos/fgetpos */
			if (ntar_native_file_seek(fp, 1, SEEK_CUR, NULL) != NTAR_SUCCESS)
				support_seeks = FALSE;
			else
			{
				/* it seems to support seeks, let's move at the beginning of the file
				 */
				if (ntar_native_file_seek(fp, 0, SEEK_SET, NULL) != NTAR_SUCCESS)
				{
					/* what?? it supports a forward seek of 1 byte and not a backward seek??
					 * this is weird! The file is corrupted, simply close it and return
					 * TODO this is not so clean, I know...
					 */
					fclose(fp);
					return NTAR_FAILURE;
				}
				else
					support_seeks = TRUE;
			}
		}
		
		file_handlers->handle = fp;
		file_handlers->read_handler = ntar_native_file_read;
		
		if (support_seeks)
			file_handlers->seek_handler = ntar_native_file_seek;
		else
			file_handlers->seek_handler = NULL;

		file_handlers->write_handler = NULL;

		return NTAR_SUCCESS;
	}
	else
	if (file_mode == NTAR_FILEMODE_WRITE)
	{
		if (filename == NULL)
		{
			/* we should use stdin, and stdin does not support seeks */
			fp = stdout;
#ifdef WIN32
			_setmode(_fileno(fp), _O_BINARY);
#endif
			support_seeks = FALSE;
		}
		else
		{
			fp = fopen(filename, NTAR_FOPEN_WRITE_MODE);

			if (fp == NULL)
				return ntar_convert_errno(errno);

			/* let's see if it supports fseek/fsetpos/fgetpos */
			if (ntar_native_file_seek(fp, 1, SEEK_CUR, NULL) != NTAR_SUCCESS)
				support_seeks = FALSE;
			else
			{
				/* it seems to support seeks, let's move at the beginning of the file
				 */
				if (ntar_native_file_seek(fp, 0, SEEK_SET, NULL) != NTAR_SUCCESS)
				{
					/* what?? it supports a forward seek of 1 byte and not a backward seek??
					 * this is weird! The file is corrupted, simply close it and return
					 * TODO this is not so clean, I know...
					 */
					fclose(fp);
					return NTAR_FAILURE;
				}
				else
					support_seeks = TRUE;
			}
		}
		
		file_handlers->handle = fp;
		file_handlers->write_handler = ntar_native_file_write;
		if (support_seeks)
			file_handlers->seek_handler = ntar_native_file_seek;
		else
			file_handlers->seek_handler = NULL;
		
		file_handlers->read_handler = NULL;

		return NTAR_SUCCESS;
	}

	return NTAR_FAILURE;
}

int ntar_native_file_close(ntar_file_handlers file_handlers)
{
	FILE *fp = (FILE*)file_handlers.handle;
	
	if (file_handlers.write_handler != NULL)
		fflush(fp);

	if (fp != stdin && fp != stdout)
		fclose(fp);

	return NTAR_SUCCESS;
}

