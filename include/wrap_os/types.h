/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Some OS-dependend types.
**************************
**************************************************** */

#ifndef _NCORE_WRAPOS_TYPES_H_
#define _NCORE_WRAPOS_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#if !defined(NCORE_NOT_USE_BOOL)
#	include <stdbool.h>
#endif

#include "wrap_os/ostype.h"

/* = First: Fileno type = */
/*
	If the current OS not supports POSIX filenos,
	NCoreFileno_t should not exists and the macro
	NCORE_FILENO should be undefined.
*/

#if defined(NCORE_OS_POSIXLIKE)
#	define NCORE_FILENO 1
typedef int NCoreFileno_t;
#else
#	if defined(NCORE_FILENO)
#		undef NCORE_FILENO
#	endif
#endif

/* = File Type = */
/*
	The C stdlib provides a FILE* type for handling
	files, but this type is a replacement in case of
	the NCORE_FILENO type is not defined.
*/
typedef FILE* NCoreFile_t;

#if !defined(NCORE_NOT_USE_BOOL)
typedef bool NCoreBool_t;
#else
typedef unsigned char NCoreBool_t;
#endif

/* = Dynamic Library type = */
/*
	In POSIX-like systems: void* (return type of dlopen).
*/
#if defined(NCORE_OS_POSIXLIKE)
#	define NCORE_DYNLIB 1
typedef void* NCoreDynLibHandler_t;
#else
#	if defined(NCORE_DYNLIB)
#		undef NCORE_DYNLIB
#	endif
#endif

/* = Universal function type = */
/*
	All functions that returns or gets a function uses this type.
*/
#if defined(NCORE_OS_POSIXLIKE)
#	define NCORE_FCN_TYPE 1
typedef void* NCoreFunctionType_t; /* Converted to an (any(*)(any...)) */
#else
#	if defined(NCORE_FCN_TYPE)
#		undef NCORE_FCN_TYPE
#	endif
#endif

#if !defined(FALSE)
#	if !defined(NCORE_NOT_USE_BOOL)
#		define FALSE false
#	else
#		define FALSE 0
#	endif
#endif
#if !defined(TRUE)
#	if !defined(NCORE_NOT_USE_BOOL)
#		define TRUE true
#	else
#		define TRUE !FALSE
#	endif
#endif

typedef int NCoreError_t;
typedef char NCoreChar_t;
typedef NCoreChar_t* NCoreString_t;

#if !defined(NCORE_FAST_CMP)
#	define NCORE_FAST_CMP(x,y) !(x ^ y)
#endif

#endif /* ~_NCORE_WRAPOS_TYPES_H_ */
