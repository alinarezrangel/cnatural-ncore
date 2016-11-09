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
typedef unsigned char NCoreBool_t;

#if !defined(FALSE)
#	define FALSE 0
#endif
#if !defined(TRUE)
#	define TRUE !FALSE
#endif

typedef int NCoreError_t;
typedef char NCoreChar_t;

#if !defined(NCORE_FAST_CMP)
#	define NCORE_FAST_CMP(x,y) !(x ^ y)
#endif

#endif /* ~_NCORE_WRAPOS_TYPES_H_ */
