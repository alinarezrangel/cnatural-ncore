/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Declares ERROR constants
**************************
**************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

#include <sys/fcntl.h>

#include "wrap_os/named_pipes.h"

NCoreError_t ncore_os_namedpipe_new(NCoreOSNamedPipe_t** pipe)
{
	*pipe = malloc(sizeof(NCoreOSNamedPipe_t));

	if(*pipe == NULL)
		return NCORE_ERROR_BADALLOC;

	(*pipe)->fd = -1;
	(*pipe)->isOpen = FALSE;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_destroy(NCoreOSNamedPipe_t** pipe)
{
	if((*pipe)->isOpen)
	{
		return NCORE_ERROR_OPEN;
	}

	free(*pipe);

	*pipe = NULL;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_namedpipe_create(NCoreOSNamedPipe_t* pipe, const NCoreString_t name)
{
	if(pipe->isOpen)
		return NCORE_ERROR_OPEN;

	int rt = 0;
	pipe->pipeName = name;

#if defined(NCORE_OS_POSIXLIKE)
	rt = mkfifo(NCORE_RSTR(name), 0666);
#else
#	error "Unable to determine what system use for create a named pipe ncore_os_namedpipe_create"
#endif

	if(rt != 0)
		return NCORE_ERROR_USENO;

#if defined(NCORE_OS_POSIXLIKE)
	pipe->fd = open(NCORE_RSTR(name), NCORE_PIPE_OPEN_FLAGS);
#else
#	error "Unable to determine what system use for open a fd ncore_os_namedpipe_create"
#endif

	if(pipe->fd < 0)
		return NCORE_ERROR_USENO;

	pipe->isOpen = TRUE;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_open(NCoreOSNamedPipe_t* pipe, const NCoreString_t name)
{
	if(pipe->isOpen)
		return NCORE_ERROR_OPEN;

	pipe->pipeName = name;

#if defined(NCORE_OS_POSIXLIKE)
	pipe->fd = open(NCORE_RSTR(name), NCORE_PIPE_OPEN_FLAGS);
#else
#	error "Unable to determine what system use for open a fd ncore_os_namedpipe_open"
#endif

	if(pipe->fd < 0)
		return NCORE_ERROR_USENO;

	pipe->isOpen = TRUE;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_close(NCoreOSNamedPipe_t* pipe)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = close(pipe->fd);
#else
#	error "Unable to determine what system use for close a fd ncore_os_namedpipe_close"
#endif

	if(rt < 0)
		return NCORE_ERROR_USENO;

	pipe->isOpen = FALSE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_namedpipe_release(NCoreOSNamedPipe_t* pipe)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = close(pipe->fd);
	unlink(NCORE_RSTR(pipe->pipeName));
#else
#	error "Unable to determine what system use for close a fd ncore_os_namedpipe_close"
#endif

	if(rt < 0)
		return NCORE_ERROR_USENO;

	pipe->isOpen = FALSE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_namedpipe_send(NCoreOSNamedPipe_t* pipe, const NCoreString_t message)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = write(pipe->fd, NCORE_RSTR(message), strlen(NCORE_RSTR(message)));
#else
#	error "Unable to determine what system use for write a fd ncore_os_namedpipe_send"
#endif

	if(rt != strlen(message))
		return NCORE_ERROR_IOBUFF;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_send_fix(NCoreOSNamedPipe_t* pipe, const NCoreString_t message, size_t len)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = write(pipe->fd, NCORE_RSTR(message), len);
#else
#	error "Unable to determine what system use for write a fd ncore_os_namedpipe_send_fix"
#endif

	if(rt != len)
		return NCORE_ERROR_IOBUFF;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_receive(NCoreOSNamedPipe_t* pipe, NCoreString_t message)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = read(pipe->fd, NCORE_RSTR(message), NCORE_IOFCN_READ_BLOCK_SIZE);
#else
#	error "Unable to determine what system use for read a fd ncore_os_namedpipe_receive"
#endif

	if(rt != NCORE_IOFCN_READ_BLOCK_SIZE)
		return NCORE_ERROR_IOBUFF;

	return NCORE_NO_ERROR;
}
NCoreError_t ncore_os_namedpipe_receive_fix(NCoreOSNamedPipe_t* pipe, NCoreString_t message, size_t len)
{
	int rt = 0;

	if(!pipe->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = read(pipe->fd, NCORE_RSTR(message), len);
#else
#	error "Unable to determine what system use for write a fd ncore_os_namedpipe_receive_fix"
#endif

	if(rt != len)
		return NCORE_ERROR_IOBUFF;

	return NCORE_NO_ERROR;
}
