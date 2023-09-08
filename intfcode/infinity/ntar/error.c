#include "ntar_int.h"
#include <errno.h>

int ntar_convert_errno(int local_errno)
{
	switch (local_errno)
	{
	case EACCES:	return NTAR_FAILURE_ACCESSDENIED;
	case EBADF:		return NTAR_FAILURE_BADFILEDESCRIPTOR;
	case EEXIST:	return NTAR_FAILURE_FILEEXISTS;
	case EINVAL:	return NTAR_FAILURE_INVALIDPARAMETER;
	case EMFILE:	return NTAR_FAILURE_TOOMANYOPENFILES;
	case ENOENT:	return NTAR_FAILURE_FILENOTFOUND;
	case ENOMEM:	return NTAR_FAILURE_NOMEM;
	case ENOSPC:	return NTAR_FAILURE_DISKFULL;
	default:		return NTAR_FAILURE_UNKNOWNERRNO;
	}
}