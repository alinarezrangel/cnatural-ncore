/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** OS-dependend dynamic library load functions
**************************
**************************************************** */

#ifndef _NCORE_WRAPOS_DYNLIB_H_
#define _NCORE_WRAPOS_DYNLIB_H_

#include <stdlib.h>
#include <string.h>

#include "wrap_os/ostype.h"
#include "wrap_os/types.h"

#include "error.h"

#if defined(NCORE_OS_POSIXLIKE)
#	include <dlfcn.h>
#else
#	error "Unable to determine what system use for dynamic library load"
#endif

struct NCoreOSDynLib
{
#if defined(NCORE_DYNLIB)
	NCoreDynLibHandler_t handler;
#else
#	error "Required dynamic libraries handlers for NCoreOSDynLib"
#endif

	NCoreBool_t isOpen;
};
typedef struct NCoreOSDynLib NCoreOSDynLib_t;

/**
* @brief Creates a new dynamic library handler.
* By default, is not associated with a dynlib.
* @param dynlib Dynamic Library Handler to create
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_new(NCoreOSDynLib_t* dynlib);

/**
* @brief Destroys a dynamic library handler.
* If the dynlib handler is open, raises a NCORE_ERROR_OPEN error.
* @param dynlib Dynamic Library Handler to close
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_destroy(NCoreOSDynLib_t* dynlib);

/**
* @brief Opens a new dynlib and associates it with a handler.
* If the handler is already associated with a resource, raises a
* NCORE_ERROR_OPEN error.
* @param dynlib Dynamic Library Handler
* @param libname Name of the dynlib to open
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_open(
	NCoreOSDynLib_t* dynlib,
	const NCoreString_t libname
);

/**
* @brief Loads a symbol from the handler.
* If the handler is not opened, raises a NCORE_ERROR_NOPEN error.
*
* The NCoreFunctionType_t argument should be converted to a specific
* function pointer before it's use.
* @param dynlib Dynamic Library Handler
* @param symbol Name of the symbol to load
* @param fcn Symbol loaded
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_load(
	NCoreOSDynLib_t* dynlib,
	const NCoreString_t symbol,
	NCoreFunctionType_t* fcn
);

/**
* @brief Closes a handler.
* If the handler is not opened, raises a NCORE_ERROR_OPEN error.
* @param dynlib Dynamic Library Handler
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_close(NCoreOSDynLib_t* dynlib);

#endif /* ~_NCORE_WRAPOS_DYNLIB_H_ */
