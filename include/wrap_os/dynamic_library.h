/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** OS-dependend dynamic library load functions

Copyright 2016 Alejandro Linarez Rangel

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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

#if !defined(NCORE_DYNLIB_EXPORT)
#	if defined(NCORE_OS_POSIXLIKE)
#		if defined(__cplusplus)
#			define NCORE_DYNLIB_EXPORT /* None on POSIX-like systems when using C */
#		else
#			define NCORE_DYNLIB_EXPORT extern "C" /* when using C++ */
#		endif
#	else
#		error "Unable to determine what system use for declare an exportable dynlib symbol"
#	endif
#endif

NCORE_DECLARATION_BEGIN

/**
* @file dynapi.h
* Dynamic Library API (wraping the OS)
*/

/**
* @brief It's a OS-dependend dynamic library handler.
*
* Is NOT Copyable.
*/
struct NCoreOSDynLib
{
#if defined(NCORE_DYNLIB)
	NCoreDynLibHandler_t handler;
#else
#	error "Required dynamic libraries handlers for NCoreOSDynLib"
#endif

	NCoreBool_t isOpen; /* !PUBLIC! */
};
typedef struct NCoreOSDynLib NCoreOSDynLib_t;

/**
* @brief Creates a new dynamic library handler.
* By default, is not associated with a dynlib.
* @param dynlib Dynamic Library Handler to create
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_new(NCoreOSDynLib_t** dynlib);

/**
* @brief Destroys a dynamic library handler.
* If the dynlib handler is open, raises a NCORE_ERROR_OPEN error.
* @param dynlib Dynamic Library Handler to close
* @return Error (if any)
*/
NCoreError_t ncore_os_dynlib_destroy(NCoreOSDynLib_t** dynlib);

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

NCORE_DECLARATION_END

#endif /* ~_NCORE_WRAPOS_DYNLIB_H_ */
