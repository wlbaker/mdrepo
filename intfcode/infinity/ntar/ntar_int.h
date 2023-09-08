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

#ifndef __NTAR_INT_H_2233343443h4h4437y3y4
#define __NTAR_INT_H_2233343443h4h4437y3y4

#include "ntar.h"

#include "ntar_debug.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#ifdef WIN32
#include <io.h>
#endif

#include <fcntl.h>


#ifndef WIN32
#define stricmp strcasecmp
#endif

struct _ntar_file_handle;       /* Forward structure declaration to make the compiler happy. */
struct _ntar_section_handle;    /* Forward structure declaration to make the compiler happy. */
struct _ntar_plugin_data;       /* Forward structure declaration to make the compiler happy. */

/*!
    \brief This structure is used to maintain the offset of previous, current
    and next section or block in a file opened in read mode.
*/
typedef struct _ntar_read_iterator
{
#define NTAR_POS_NOT_DEFINED    ((ntar_foff)(-1))    ///< The position of a block/section is not defined
#define NTAR_BEGINNING_OF_FILE  ((ntar_foff)0)			///< The position of a block/section is at the beginning of the file (i.e. offset 0)
    ntar_foff  prev_pos;                   ///< Position (offset in the file) of the previous section, or \ref NTAR_POS_NOT_DEFINED
	ntar_foff  curr_pos;                   ///< Position (offset in the file) of the current section, or \ref NTAR_POS_NOT_DEFINED
	ntar_foff  next_pos;                   ///< Position (offset in the file) of the next section, or \ref NTAR_POS_NOT_DEFINED
}
    ntar_read_iterator;

/*!
    \brief This structure represents a generic block contained in a section.
*/
struct _ntar_block_handle
{
	/*! General information about the underlying file.
	*/
	ntar_file_handlers file_handlers;

    /*!
    Byte order for this section. Possible values are 
     - HOST_BYTE_ORDER
     - SWAPPED_HOST_BYTE_ORDER
     This field is valid in read mode only.
    */
    int byte_order;             

	/*! Position in the file where the section/block begins.
     */
	ntar_foff block_start; 
    
    /*! Handle to the section containing this block
     */
    struct _ntar_section_handle *section_handle;    
    
    /*! Pointer to data used by the plugin. TODO currently not in use.
     */
    void *plugin_state;        
    
    ntar_option *options;    
    
    /*! A opaque handle to the plugin used to manage this block.
     */
    struct _ntar_plugin_data *plugin_data;  
    
    /*! The block header of this block, as written on file. 
        This field is valid in read mode only, and it contains data in host byte order
     */
    block_header bh;                

	/*! TRUE if the fixed block data (i.e. the content of the block excluding the options)
	    has been read
	*/
	int are_block_data_read;

	/*! Pointer to a temp buffer used to read/write the options.
	*/
	char* options_buffer;

	/*! Length of the options_buffer
	*/
	size_t	options_buffer_length;

	/*! Length of the data_buffer
	*/
	size_t	data_buffer_length;

	/*! Pointer to a temp buffer used to read/write the data.
	*/
	char* data_buffer;

	void *block_data;
	void *raw_data_buffer;
	size_t raw_data_buffer_length;
	size_t raw_data_buffer_start_options;
};

/*!
    \brief This structure represents the root block for a file.
    It corresponds to a Section Header Block of the draft, see 3.1

*/
struct _ntar_section_handle
{
	/*! General information about the underlying file.
	*/
	ntar_file_handlers file_handlers;
    
	/*! Position in the file where the section/block begins.
    */
	ntar_foff block_start; 
    
    /*! The block header of this section, as written on file. 
        This field is valid in read mode only, and it contains data in host byte order
     */
    block_header bh;

	/*! The section header block that will be written to file or that has been read from file.
		This field is always written in host byte order.
	*/
	section_header_block shb;

	/*! Linked list of the options that will be written to file, or that have been read from file.
		The linked list does NOT contain the trailing END OPTION.
	*/
	ntar_option *options;

    /*! Handle to the ntar file containing this section
    */
    struct _ntar_file_handle *file_handle;  

    /*!
    Byte order for this section. Possible values are 
     - HOST_BYTE_ORDER
     - SWAPPED_HOST_BYTE_ORDER
     This field is valid in read mode only.
    */
    int byte_order;             
    
    /*! Handle to a block handle cache.
    */
    ntar_block_handle cache_block;   

	/*! TRUE if the cache block is opened
	*/
    int block_opened;

    /*! TRUE if the block header has been closed.
        This field is valid in read mode only.
    */
    int header_written;   
    
    /*! Length of the Section Header Block, excluding the heading/trailing generic block header
        This field is valid in read mode only.
    */
    u_int32 shb_header_length;      
    
    /*! Indexes of the current, previous and next block in the section.
    */
    ntar_read_iterator read_iterator;

	/*! Pointer to a temp buffer used to read the options.
	*/
	char* options_buffer;

	/*! Length of the options_buffer
	*/
	size_t	options_buffer_length;
	
	char* raw_options_buffer;

	size_t raw_options_buffer_length;

	int reached_end_of_section;

};

/*!
    \brief This structure represents the handle to a dump file.
*/
struct _ntar_file_handle
{
    /*! Working mode of the file. Possible values are
        - \ref NTAR_FILEMODE_READ
        - \ref NTAR_FILEMODE_CREATE
        - \ref NTAR_FILEMODE_WRITE
        - \ref NTAR_FILEMODE_APPEND
    */
    int file_mode;

	int using_internal_handlers;

	/*! General information about the underlying file.
	*/
	ntar_file_handlers file_handlers;

    /*! Handle to the current section, both in read and write mode, or NULL.
    */
    ntar_section_handle cache_section;   
	
	/*! True if a section of the file is opened
	*/
	int section_opened;

    /*! Indexes of the current, previous and next section in the file.
    */
    ntar_read_iterator read_iterator;

	block_header last_bh;
};


/*! \addtogroup InternalFuncs
	\{
*/
/*! 
	\brief This fcn reallocates a given buffer if it's too small
	\param buffer Address of a user allocated pointer to the current buffer. 
				  On return it contains the pointer to the new buffer.
	\param buffer_size Address of an integer containing the current size 
				  of the buffer. On return it contains the size of the
				  newly allocated buffer.
	\param new_size Requested new size of the buffer.
	\return
		- \ref NTAR_SUCCESS if the resizing was successful.
		- \ref NTAR_FAILURE_NOMEM if the allocation failed.
	\note This fcn does not reallocate the buffer if is large enough.
*/
int reallocate_memory(void **buffer, size_t *buffer_size, size_t new_size);

/*! 
	\brief This fcn converts an errno value to the corresponding ntar error code.
	\param local_errno errno code.
	\return
		- \ref NTAR_FAILURE_NOMEM for ENOMEM
		- \ref NTAR_FAILURE_ACCESSDENIED for EACCES
		- \ref NTAR_FAILURE_BADFILEDESCRIPTOR for EBADF
		- \ref NTAR_FAILURE_FILEEXISTS for EEXIST
		- \ref NTAR_FAILURE_INVALIDPARAMETER for EINVAL
		- \ref NTAR_FAILURE_TOOMANYOPENFILES for EMFILE
		- \ref NTAR_FAILURE_FILENOTFOUND for ENOENT
		- \ref NTAR_FAILURE_DISKFULL for ENOSPC
		- \ref NTAR_FAILURE_UNKNOWNERRNO in any other case.
*/
int ntar_convert_errno(int local_errno);


int ntar_native_file_write(void *handle, void* buffer, size_t size);
int ntar_native_file_read(void *handle, void* buffer, size_t size, size_t *read_bytes);
int ntar_native_file_seek(void *handle, ntar_foff new_position, int origin, ntar_foff *old_position);
int ntar_native_file_close(ntar_file_handlers file_handlers);
int ntar_native_file_open(char *filename, char *flags, ntar_file_handlers *file_handlers);



/*!
\}
*/
#endif /*__NTAR_INT_H_2233343443h4h4437y3y4*/
