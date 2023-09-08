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

#ifndef __NTAR_09443049285795464587845827
#define __NTAR_09443049285795464587845827


/** @file ntar.h
 * \brief This file contains prototypes, definitions and data structures of the ntar library.
 * 
 */

#include <stdio.h>
#include "block_headers.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
	\defgroup ExportedStructs  Structures
*/

/*!
	\defgroup ExportedDefs  Definitions
*/

/*!
	\defgroup ExportedErrorCodes Error codes
*/

/*!
	\defgroup ExportedFuncs Exported functions
*/

/*!
	\if ShowPlugins
	\defgroup PluginInterface Block plugins callbacks
	\endif
*/

/*! \mainpage NTAR detailed documentation
 *
 * \section intro Introduction
 *
 * This document describes the data structures and the functions that the NTAR library exports.
 *
 *
 *	This module includes the following sections:
 *  <ul>
 *	<li> \ref ExportedStructs
 *	<li> \ref ExportedDefs
 *	<li> \ref ExportedErrorCodes
 *	<li> \ref ExportedFuncs
 *      \if ShowPlugins <li> \ref PluginArchitecture
 *	\endif
 * </ul>
 *
 *
 * The NTAR library is covered by the \ref License "BSD License".
 *
 *
 *
 */

/*! \addtogroup ExportedErrorCodes
	\{
*/

#define NTAR_SUCCESS                    0   ///< The call to a function succeeded.
#define NTAR_FAILURE                    1   ///< The call to a function failed for some reason.
#define NTAR_FAILURE_INVALID_ID         2   ///< The identifier of a block or an option is not valid or unknown.
#define NTAR_FAILURE_FILENOTFOUND       3   ///< The call to ntar_open failed because the file does not exist.
#define NTAR_FAILURE_FILEEXISTS         4   ///< The call to ntar_open failed because the file does exist.
#define NTAR_FAILURE_CREATEFILEFAILED   5   ///< The call to ntar_open failed because it was not possible to create the file.
#define NTAR_FAILURE_NOMEM              6   ///< No memory is available to allocate the internal structures.
#define NTAR_FAILURE_SECTIONNOTCLOSED   7   ///< An attempt to close a file or create a new section has been made without closing the current opened section.
#define NTAR_FAILURE_WRITEONREADFILE    8   ///< An attempt to write on a read file has been made.
#define NTAR_FAILURE_IOWRITE            9   ///< A request to write to file failed.
#define NTAR_FAILURE_BLOCKNOTCLOSED     10  ///< An attempt to close a section failed because the current block has not been closed.
#define NTAR_FAILURE_IOREAD             11  ///< A request to read from a file failed.
#define NTAR_FAILURE_EOF                12  ///< A request to read from a file failed.
#define NTAR_FAILURE_INVALIDFILE        13  ///< The file opened for reading is not a valid NTAR file. 
#define NTAR_FAILURE_MALFORMED_BLOCK    14  ///< The opened block is not correct (e.g. the block length at the end has not the same value as the one at the beginning)
#define NTAR_FAILURE_NOMOREBLOCKS       15  ///< There are no more blocks in the current section.
#define NTAR_FAILURE_BLOCKDATAUNREAD	16	///< An attempt to read a block option has been made without previously reading the block data.
#define NTAR_FAILURE_SMALLBUFFER		17	///< The buffer passed to a function is too small to retrieve some info.
#define NTAR_FAILURE_BLOCKDATANOTSET	18	///< The block data passed to create a new block are NULL
#define NTAR_FAILURE_DUPPTR				19	///< An attempt to add the same option structure to a block has been made.
#define NTAR_FAILURE_ASCIIDLFILE		20	///< The file was probably downloaded in FTP ASCII mode or another ASCII transfer mode.
#define NTAR_FAILURE_BLOCKTRAILERMISMATCH 21	///< The trailer block size does not match the header one. The block has been closed, however.
#define NTAR_FAILURE_ACCESSDENIED		22	///< An attempt to open a protected file (either in read or write mode) has been been without the proper credentials.
#define NTAR_FAILURE_BADFILEDESCRIPTOR	23	///< An attempt to read or write to an invalid file descriptor has been made by the library.
#define NTAR_FAILURE_INVALIDPARAMETER	24	///< A wrong parameter has been passed to a CRT function.
#define NTAR_FAILURE_TOOMANYOPENFILES	25	///< Too many open files. No more file descriptors are available, so no more files can be opened. 
#define NTAR_FAILURE_DISKFULL			26	///< The disk is full, so any further writes to the file are not allowed.
#define NTAR_FAILURE_UNKNOWNERRNO		27	///< A CRT error has been detected by the library, but the corresponding errno code is unknown.
/*! 
	\}
*/

/*! \addtogroup ExportedDefs
	\{
*/

#define NTAR_FILEMODE_WRITE             0   ///< The file was opened for writing new data to a new file.
#define NTAR_FILEMODE_READ              1   ///< The file was opened for reading data.
#define NTAR_FILEMODE_CREATE			2   ///< The file was opened for overwriting an existing file.
#define NTAR_FILEMODE_APPEND            3   ///< The file was opened for appending to an existing file.

#define NTAR_OPEN_WRITE         "w"         ///< Open an existing file and overwrite, or create a new one.
#define NTAR_OPEN_READ          "r"         ///< Open an existing file for reading.
#define NTAR_OPEN_CREATE		"c"         ///< Open a new file for writing.
#define NTAR_OPEN_APPEND        "a"         ///< Open an existing file for appending new data.

/*! 
	\}
*/

	
/*! \addtogroup ExportedStructs
	\{
*/

/*! \brief This structure represents an option of a block, at the user level.
*/
typedef struct _ntar_option
{
	struct _ntar_option *next;			///< Next option in the chain.
	u_int16 code;						///< Code of the option, as specified in the draft.
	void *data;							///< Data of the option, as specified in the draft.
}
	ntar_option;

/*!
    \brief This structure represents a generic block contained in a section.
*/
typedef struct _ntar_block_handle ntar_block_handle;

/*!
    \brief This structure represents the root block for a file.
    It corresponds to a Section Header Block of the draft, see 3.1

*/
typedef struct _ntar_section_handle ntar_section_handle;

/*!
    \brief This structure represents the handle to a dump file.
*/
typedef struct _ntar_file_handle ntar_file_handle;

/*!
	\brief This is the callback that is called when the library needs to write some data 
		to the underlying storage. This callback should be defined when the storage (file, or
		memory) is opened (with \ref ntar_open_by_handlers) in write mode.
	\param handle This opaque parameter is the one assigned to \ref ntar_file_handlers::handle when
		the file (or any other storage) was opened with \ref ntar_open_by_handlers. The library takes
		care to passing this parameter untouched to the callback. 
	\param buffer Pointer to the buffer containing the raw data that have to be written on file.
	\param size	Size of the data pointed by parameter buffer.
	\return The function should return one of the following error codes:
		- \ref NTAR_SUCCESS only if the data have been completely written to the file.
		- \ref NTAR_FAILURE_IOWRITE 
		- \ref NTAR_FAILURE_ACCESSDENIED
		- \ref NTAR_FAILURE_BADFILEDESCRIPTOR	
		- \ref NTAR_FAILURE_INVALIDPARAMETER	
		- \ref NTAR_FAILURE_DISKFULL			
		- \ref NTAR_FAILURE_UNKNOWNERRNO
		- \ref NTAR_FAILURE in any other case.
*/
typedef int (*ntar_write_handler)(void *handle, void* buffer, size_t size);

/*!
	\brief This is the callback that is called when the library needs to read some data 
		from the underlying storage. This callback should be defined when the storage (file, or
		memory) is opened (with \ref ntar_open_by_handlers) in read mode.
	\param handle This opaque parameter is the one assigned to \ref ntar_file_handlers::handle when
		the file (or any other storage) was opened with \ref ntar_open_by_handlers. The library takes
		care to passing this parameter untouched to the callback. 
	\param buffer Pointer to the user allocated buffer that will receive the data read from the file. 
		The buffer should be large enough to contain at least size bytes.
	\param size	Size of the data that should be read from file.
	\param read_bytes Pointer to a user allocated variable that will contain the number of actually read
		bytes, or NULL. 
	\return The function should return one of the following error codes:
		- \ref NTAR_SUCCESS only if size bytes have been successfully read from file. If the end-of-file has been reached, 
			\ref NTAR_FAILURE_EOF should be returned and read_bytes should contain the number of bytes actually read.
		- \ref	NTAR_FAILURE_EOF        
		- \ref NTAR_FAILURE_IOREAD 
		- \ref NTAR_FAILURE_ACCESSDENIED
		- \ref NTAR_FAILURE_BADFILEDESCRIPTOR	
		- \ref NTAR_FAILURE_INVALIDPARAMETER	
		- \ref NTAR_FAILURE_UNKNOWNERRNO
		- \ref NTAR_FAILURE in any other case.
*/
typedef int (*ntar_read_handler)(void *handle, void* buffer, size_t size, size_t *read_bytes);

/*!
	\brief This is the callback that is called when the library needs to obtain the current position in the
		file, and eventually seek to a new position. This callback is optional (both in read and write mode).
		Nonetheless, if this callback is not defined, not all the features of the library are available, in particular
		<br><b>WRITE MODE</b>
		- The section header block length is not written to file (the magic value 0xFFFFFFFFFFFFFFFF is written, instead).
		<br><b>READ MODE</b>
		- It is not possible to perform any backward seek in the file (i.e. only a sequential read of the trace file is possible).
		- Read operations can be slower, since the library uses empty reads to jump between blocks and sections.
	\param handle This opaque parameter is the one assigned to \ref ntar_file_handlers::handle when
		the file (or any other storage) was opened with \ref ntar_open_by_handlers. The library takes
		care to passing this parameter untouched to the callback. 
	\param new_position New position in file. Parameter "origin" describes the origin for this new position.
	\param origin One of:
		- SEEK_SET	Parameter "new_position" is the absolute position in the file from its beginning.
		- SEEK_CUR Parameter "new_position" is the relative position in the file from the current position.
		- SEEK_END Parameter "new_position" is the relative position in the file from its current end.
	\param pold_position Pointer to a user allocate variable that will receive the absolute position in the 
		file (i.e. from the beginning of the file) before the seek operation takes place, or NULL.
		NOTE: in order to obtain the current position in the file, the library calls this callback with new_position = 0 and origin=SEEK_CUR.
		
	\return The function should return one of the following error codes:
		- \ref NTAR_SUCCESS 
		- \ref	NTAR_FAILURE_EOF        
		- \ref NTAR_FAILURE_IOREAD 
		- \ref NTAR_FAILURE_ACCESSDENIED
		- \ref NTAR_FAILURE_BADFILEDESCRIPTOR	
		- \ref NTAR_FAILURE_INVALIDPARAMETER	
		- \ref NTAR_FAILURE_UNKNOWNERRNO
		- \ref NTAR_FAILURE in any other case.
*/
typedef int (*ntar_seek_handler)(void *handle, ntar_foff new_position, int origin, ntar_foff *pold_position);

/*!
	\brief This structure contains the read/write/seek callbacks that ntar uses to manage an ntar file when the application provides
		its own read/write/seek functions to deal with the underlying storage. 

		These callbacks are useful when the application wants to read and write data from non-standard files, or compressed/cripted files,
		or directly to memory.
*/
typedef struct _ntar_file_handlers
{
	ntar_read_handler read_handler;		///< This function is called by ntar to read some data out of the underlying storage. It is necessary to define this function when the file is opened in read mode.
	ntar_write_handler write_handler;	///< This function is called by ntar to write some data to the underlying storage. It is necessary to define this function when the file is opened in write mode.
	/*!
		\brief This function is used by ntar in various occasions when the file is opened in both read or 
			write mode. It is usually used to perform backwards seeks in the file, block skipping, and to
			rewrite some fields in the trace file. This function is optional (in case it's missing, it 
			should be set to NULL).
	*/
	ntar_seek_handler seek_handler;		

	/*!
		\brief Opaque handler defined by the application defining the read/write/seek handlers. This pointer is
			passed untouched by the library to the handlers as their first parameter. The user usually uses this
			opaque handle to store a pointer to some sort of descriptor (e.g. the typical FILE* pointer) of the underlying
			file.
	*/
	void *handle;
}
	ntar_file_handlers;

/*! 
	\}
*/
/*! \addtogroup ExportedFuncs
	\{
*/


/* NOTE: we include the plugins only here because the plugins need 
         the definitions of all the ntar structures. If we include
         the header at the beginning of the file, the definition of
         _NTAR_H_xxxxxx will be already there, but the structures will
         not be declared, yet.
*/
#include "plugins.h"
    
/*!
    \brief This functions open a new dump file for reading or writing.

    \param filename Name of the file to be opened.
    \param flags The opening mode of the file. At the moment the accepted values are
        - "r" to read the file
        - "w" to write a new file. If the file exists, the file is overwritten.
        - "a" to append a new capture to an existing file.
        - "c" to write a new file. If the file exists, the function fails.
    \param pfile_handle Address of a user allocated pointer that will be filled with the handle to a dump file.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_open(char* filename, char* flags, ntar_file_handle** pfile_handle);

/*!
	\brief This functions open a new dump file for reading or writing using some external read/write/seek
		callbacks defined by the caller.

	\param file_handlers Structure containing the file handlers that the library will use to read or write the
		trace file. All the pointers contained in this structure should remain valid until the file is closed
		with \ref ntar_close. 
    \param flags The opening mode of the file. At the moment the accepted values are
        - "r" to read the file. In this case the \ref ntar_file_handlers::read_handler must not be NULL.
        - "w" to write a new file. If the file exists, the file is overwritten. In this case the \ref ntar_file_handlers::write_handler must not be NULL.
        - "a" to append a new capture to an existing file. In this case the \ref ntar_file_handlers::write_handler must not be NULL.
        - "c" to write a new file. If the file exists, the function fails. In this case the \ref ntar_file_handlers::write_handler must not be NULL.
    \param pfile_handle Address of a user allocated pointer that will be filled with the handle to a dump file.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
	
	\todo The flags are completely nonsense. What is the meaning of appending when the user provides the callbacks??

*/
int ntar_open_by_handlers(ntar_file_handlers file_handlers, char* flags, ntar_file_handle** pfile_handle);

/*!
    \brief This function closes a dump file flushing all the unwritten data to disk.

    \param file_handle Handle to the dump file to be closed.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_close(ntar_file_handle* file_handle);

/*!
    \brief This function creates a new section (SHB as specified in 3.1 in the draft) into a dump file.
    \note It's not possible to create a new section if the dump file was opened in read mode.

    \param file_handle handle to the dump file.
    \param psection_handle Address of a user allocated pointer that will be filled with an handle to the newly created section.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_create_section(ntar_file_handle* file_handle, ntar_section_handle** psection_handle);

/*!
    \brief This function closes a section in a dump file, eventually flushing all the unsaved data to disk (if in write mode).

    \param section_handle Section that must be closed.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_close_section(ntar_section_handle* section_handle);

/*!
    \brief This function adds a new option value to a section.
    \note It's not possible to set an option if the dump file was opened in read mode.

    \param section_handle Handle to the target section.
    \param option Pointer to a ntar_structure containing all the data of the option.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     - \ref NTAR_FAILURE_INVALID_ID if the ID of the option was invalid.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.

  	\todo Because of a limit of the current ntar engine, all the options are saved to disk
		when the section is closed. As a consequence, the option pointer, as well as all the data
		stored in it, must remain valid and unmodified until the section is closed.

*/
int ntar_add_section_option(ntar_section_handle* section_handle, ntar_option *option);

/*!
    \brief This function creates a new block into a section of a dump file.
    \note It's not possible to create a new block if the dump file was opened in read mode.

    \param section_handle Handle to the section that will contain the new block.
    \param block_type Id of the block that should be created
    \param data Pointer to the header value thatt should be set in the block handle.
    \param pblock_handle Address of a user allocated pointer that will be filled with the handle of the newly created block.
    \return      
     - \ref NTAR_SUCCESS if the operation was successful.
     - \ref NTAR_FAILURE_INVALID_ID if the ID of the block was invalid.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.

*/
int ntar_create_block(ntar_section_handle* section_handle, u_int32 block_type, void *data, ntar_block_handle** pblock_handle);

/*!
    \brief This function closes a block in a dump file, eventually flushing all the unsaved data to disk (if in write mode).
    \param block_handle Handle to the block that must be closed.
    \return
     - \ref NTAR_SUCCESS if the operation was successful.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_close_block(ntar_block_handle* block_handle);

/*!
    \brief This function adds a specified option value to a block handle
    \param block_handle HAndle to the block we want to add an option
	\param option Pointer to a ntar_structure containing all the data of the option.
    \return
     - \ref NTAR_SUCCESS on success
     - \ref NTAR_FAILURE_INVALID_ID if the ID of the option was invalid.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.

	\todo Because of a limit of the current ntar engine, all the options are saved to disk
		when the block is closed. As a consequence, the option pointer, as well as all the data
		stored in it, must remain valid and unmodified until the block is closed.
*/
int ntar_add_block_option(ntar_block_handle* block_handle, ntar_option *option);

/*!
    \brief This function returns the next available section in a dump file.
    \note This function fails if the file was not opened in read mode.
    \param file_handle Handle to the dump file. 
    \param psection_handle Address of a user allocated pointer that will be filled with an handle to the
           next section.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
    \note If there are no more sections, this function returns \ref NTAR_FAILURE_EOF
*/
int ntar_get_next_section(ntar_file_handle* file_handle, ntar_section_handle** psection_handle);

/*!
    \brief This function returns the section in a dump file prior to the current one.
    \note This function fails if the file was not opened in read mode.
    \param file_handle Handle to the dump file. 
    \param psection_handle Address of a user allocated pointer that will be filled with an handle to the
            previous section.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
    \note If there are no more sections, this function returns \ref NTAR_FAILURE_NOMOREBLOCKS
    \todo At the moment it's not implemented nor exported
*/
int ntar_get_previous_section(ntar_file_handle* file_handle, ntar_section_handle** psection_handle);

/*!
    \brief This function reads the option value of a given section in a dump file.
    \param section_handle Handle to the section.
	\param options Address of a user allocated pointer to a ntar_structure that
				   will be filled with the head of a list containing all the options of the section.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
    \note The data retrieved with this function (in parameter data) should NOT be freed, and
    remain valid up to the next call to \ref ntar_get_section_options or \ref ntar_close_section, 
    whatever comes first.
*/
int ntar_get_section_options(ntar_section_handle* section_handle, ntar_option **options);

/*!
    \brief This function returns the next available block (excluding the SHB) in a section of a dump file.
    \note This function fails if the file was not opened in read mode.
    \param section_handle Handle to a section of a dump file. 
    \param pblock_handle Address of a user allocated pointer that will be filled with an handle to the
           next block.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
    \note If there are no more blocks, this function returns \ref NTAR_FAILURE_NOMOREBLOCKS
*/
int ntar_get_next_block(ntar_section_handle* section_handle, ntar_block_handle** pblock_handle);

/*!
    \brief This function returns the block in a section of  a dump file prior to the current one (excluding the SHB).
    \note This function fails if the file was not opened in read mode.
    \param section_handle Handle to a section of a dump file. 
    \param pblock_handle Address of a user allocated pointer that will be filled with an handle to the
           previous block.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
    \note If there are no more blocks, this function returns NTAR_FAILURE_NOMOREBLOCKS
*/
int ntar_get_previous_block(ntar_section_handle* section_handle, ntar_block_handle** pblock_handle);

/*!
    \brief This function returns the block type of a given block.
    \param block_handle Handle to the block
    \param pblock_type Pointer to an integer that will be filled with the block type of the current block.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_get_block_type(ntar_block_handle* block_handle, u_int32 *pblock_type);

/*!
    \brief This function retrieves the fixed data of a block.
    \param block_handle Handle to the block.
    \param data Address of a user allocated pointer that will be filled with the block data.
    \note The data retrieved with this function (in parameter data) should NOT be freed, and
    remain valid up to the next call to \ref ntar_get_block_data or \ref ntar_close_block, 
    whatever comes first.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_get_block_data(ntar_block_handle* block_handle, void** data);

/*!
    \brief This function reads all the options of a given block in a section.
    \param block_handle Handle to the block.
	\param options Address of a user allocated pointer to a ntar_structure that
				   will be filled with the head of a list containing all the options of the block.
    \return
     - \ref NTAR_SUCCESS on success
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
	\note This function will fail with error code \ref NTAR_FAILURE_BLOCKDATAUNREAD 
	if the function \ref ntar_get_block_data has not been called previously on the same block_handle.
*/
int ntar_get_block_options(ntar_block_handle* block_handle, ntar_option **options);

/*!
    \brief This function returns the version of the library.
    \param buffer Pointer to a user allocate buffer that will be filled with a NULL terminated
		string representing the version of the library.
	\param pbuffer_size Pointer to a user allocated unsigned integer. On input, it should contain
		the length of the buffer. If the buffer is too small, this function returns 
		\ref NTAR_FAILURE_SMALLBUFFER.
		On output, if the function is successful it contains the number 
		of used bytes in the buffer, if the buffer is too small it returns the number of needed bytes to return the
		library version. In order to retrieve the number of needed bytes, it is possible to set
		buffer to NULL, and buffer_size to 0. The function will return \ref NTAR_FAILURE_SMALLBUFFER
		and pbuffer_size will contain the number of needed bytes.
	\note The suggested pattern to call this function is the following one
	\code
	char *buffer;
	u_int32 buffer_size;

	buffer_size = 0;

	if (ntar_getversion(NULL, &buffer_size) != NTAR_FAILURE_SMALLBUFFER)
	{
		...some failure occurred...
	}

	buffer = (char*)malloc(buffer_size);
	...add check for failed malloc...

	if (ntar_getversion(buffer, &buffer_size) != NTAR_SUCCESS)
	{
		...some failure occurred...
	}
	else
		printf("NTAR version: %s\n", buffer);
	\endcode

  
	\return
     - \ref NTAR_SUCCESS on success
     - \ref NTAR_FAILURE_SMALLBUFFER if the buffer is too small.
     -  one of the other \ref ExportedErrorCodes "NTAR error codes" in any other case.
*/
int ntar_getversion(char* buffer, u_int32 *pbuffer_size);

#ifdef __cplusplus
}
#endif


#endif /* __NTAR_09443049285795464587845827 */

/*!
    \example test001.c
*/
/*!
    \example test002.c
*/
/*!
    \example test003.c
*/
/*!
    \example test004.c
*/
/*!
    \example test005.c
*/
/*!
    \example test006.c
*/
/*!
    \example test007.c
*/
/*!
    \example test008.c
*/
/*!
    \example test009.c
*/
/*!
    \example test010.c
*/
/*!
    \example test011.c
*/
/*!
    \example test012.c
*/
/*!
    \example test013.c
*/
/*!
    \example test014.c
*/
/*!
    \example test015.c
*/
/*!
    \example test016.c
*/
/*!
    \example test017.c
*/
/*!
    \example test018.c
*/

/*! 
	\}
*/
