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

#include "wrap_os/ostype.h"
#include "wrap_os/types.h"

struct NCoreOSNamedPipe
{
#if defined(NCORE_FILENO)
	NCoreFileno_t fd;
#else
#	error "Required named pipes for NCoreOSNamedPipe"
#endif

	NCoreBool_t isOpen;
};
typedef struct NCoreOSNamedPipe NCoreOSNamedPipe_t;



#endif /* ~_NCORE_WRAPOS_NAMED_PIPES_H_ */
