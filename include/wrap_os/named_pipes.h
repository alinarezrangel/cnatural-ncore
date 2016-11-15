/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Wrappers for the OS named pipes functions.
*** ** Uses some macros for OS detection
**************************
**************************************************** */

#ifndef _NCORE_WRAPOS_NAMED_PIPES_H_
#define _NCORE_WRAPOS_NAMED_PIPES_H_

#include <stdlib.h>
#include <string.h>

#include "wrap_os/ostype.h"
#include "wrap_os/types.h"

#include "error.h"

#if defined(NCORE_OS_POSIXLIKE)
#	include <fcntl.h>
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <unistd.h>
#else
#	error "Unable to determine what system use for fileno IO"
#endif

#if !defined(NCORE_PIPE_OPEN_FLAGS)
#	if !defined(NCORE_NOT_USE_ASYNCOPEN)
#		define NCORE_PIPE_OPEN_FLAGS O_ASYNC|O_RDWR
#	else
#		define NCORE_PIPE_OPEN_FLAGS O_RDWR
#	endif
#endif

#if !defined(NCORE_IOFCN_READ_BLOCK_SIZE)
#	define NCORE_IOFCN_READ_BLOCK_SIZE 255
#endif

NCORE_DECLARATION_BEGIN

/**
 * @file named_pipes.h
 * Adds a wrapper for the system named pipes
*/

/**
 * @brief Is a named pipe.
 * A named pipe is a special file used for IPC.
*/
struct NCoreOSNamedPipe
{
#if defined(NCORE_FILENO)
	NCoreFileno_t fd;
#else
#	error "Required named pipes for NCoreOSNamedPipe"
#endif

	const char* pipeName;
	NCoreBool_t isOpen;
};
typedef struct NCoreOSNamedPipe NCoreOSNamedPipe_t;

/**
 * @brief Creates a new named pipe.
 * This named pipe is initialized to it's default value and have
 * not associated file.
 *
 * By default, all open/create operations on a named pipe returns
 * a asynchronus (if possible) read-write file handler.
 * @param pipe Pointer to the pipe to create.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_new(NCoreOSNamedPipe_t** pipe);

/**
 * @brief Destroys a specified named pipe.
 * This named pipe IS NOT CLOSED before be destroyed, instead, if
 * the named pipe is still opened, this function return a
 * NCORE_ERROR_OPEN error.
 * @param pipe Pointer to the pipe to destroy.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_destroy(NCoreOSNamedPipe_t** pipe);

/**
 * @brief Creates a named pipe and open this.
 * Creates a named pipe in the path specified by name and opens
 * that pipe in this named pipe struct.
 * @param pipe Pipe to be opened.
 * @param name Filename of the new named pipe.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_create(NCoreOSNamedPipe_t* pipe, const NCoreString_t name);

/**
 * @brief Open a pipe.
 * This function is like ncore_os_namedpipe_create, but if the named
 * pipe filename not exists, returns an error.
 * @param pipe Pipe to be opened.
 * @param name Filename of the pipe to be opened.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_open(NCoreOSNamedPipe_t* pipe, const NCoreString_t name);

/**
 * @brief Closes a pipe
 * If the pipe is not open, returns a NCORE_ERROR_NOPEN error.
 * @param pipe Pipe to be closed.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_close(NCoreOSNamedPipe_t* pipe);

/**
 * @brief Closes a pipe and releases the system FIFO
 * If the pipe is not open, returns a NCORE_ERROR_NOPEN error.
 * @param pipe Pipe to be closed.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_release(NCoreOSNamedPipe_t* pipe);

/**
 * @brief Sends some text to the pipe.
 * The text should be NULL-terminated.
 * @param pipe Pipe
 * @param message Message to send.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_send(NCoreOSNamedPipe_t* pipe, const NCoreString_t message);

/**
 * @brief Sends some data (text or binary) to the pipe.
 * The data not have termination-restrictions.
 * @param pipe Pipe
 * @param message Data to send.
 * @param len Size (in bytes) of the data to send.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_send_fix(NCoreOSNamedPipe_t* pipe, const NCoreString_t message, size_t len);

/**
 * @brief Receives some data from the pipe.
 * By default, reads NCORE_IOFCN_READ_BLOCK_SIZE bytes to message.
 * @param pipe Pipe
 * @param message Output buffer to be written.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_receive(NCoreOSNamedPipe_t* pipe, NCoreString_t message);

/**
 * @brief Receives some data from the pipe.
 * Reads a fixed amount of data from the pipe.
 * @param pipe Pipe
 * @param message Output buffer to be written.
 * @param len Number of bytes to be readed.
 * @return Error (if any)
*/
NCoreError_t ncore_os_namedpipe_receive_fix(NCoreOSNamedPipe_t* pipe, NCoreString_t message, size_t len);

NCORE_DECLARATION_END

#endif /* ~_NCORE_WRAPOS_NAMED_PIPES_H_ */
