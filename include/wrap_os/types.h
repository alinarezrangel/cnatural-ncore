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

#if !defined(NCORE_DECLARATION_BEGIN)
#	if defined(__cplusplus)
#		define NCORE_DECLARATION_BEGIN extern "C" {
#	else
#		define NCORE_DECLARATION_BEGIN
#	endif
#endif
#if !defined(NCORE_DECLARATION_END)
#	if defined(__cplusplus)
#		define NCORE_DECLARATION_END }
#	else
#		define NCORE_DECLARATION_END
#	endif
#endif

#include "wrap_os/ostype.h"

NCORE_DECLARATION_BEGIN

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

#if !defined(NCORE_STR)
#	define NCORE_STR(x) ((const NCoreString_t)(x))
#endif
#if !defined(NCORE_CHR)
#	define NCORE_CHR(x) ((const NCoreChar_t)(x))
#endif
#if !defined(NCORE_RSTR)
#	define NCORE_RSTR(x) ((const char*)(x))
#endif
#if !defined(NCORE_RCHR)
#	define NCORE_RCHR(x) ((const char)(x))
#endif
#if !defined(NCORE_CRSTR)
#	define NCORE_RSTR(x) ((char*)(x))
#endif
#if !defined(NCORE_CRCHR)
#	define NCORE_RCHR(x) ((char)(x))
#endif

NCORE_DECLARATION_END

#endif /* ~_NCORE_WRAPOS_TYPES_H_ */
