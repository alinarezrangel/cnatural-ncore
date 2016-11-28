/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** OS-independend dynamic library load functions
**************************
**************************************************** */

#ifndef _NCORE_DYNLIN_H_
#define _NCORE_DYNLIB_H_

#include <stdlib.h>
#include <string.h>

#include "wrap_os/types.h"
#include "wrap_os/dynamic_library.h"

#include "error.h"

/**
* @file dynapi.h
* Dynamic Library OS-independend calls.
*/

NCORE_DECLARATION_BEGIN

/**
* @brief It's a dynamic load library.
*
* Is NOT Copyable
*/
struct NCoreDynLib
{
	NCoreOSDynLib_t* dynlib; /* !PUBLIC! */
};
typedef struct NCoreDynLib NCoreDynLib_t;

NCORE_DECLARATION_END

#endif /* ~_NCORE_DYNLIB_H_ */
