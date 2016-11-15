/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Declares ERROR constants
**************************
**************************************************** */

#ifndef _NCORE_ERROR_H_
#define _NCORE_ERROR_H_

#include "wrap_os/types.h"

NCORE_DECLARATION_BEGIN

extern NCoreError_t ncore_errno;

NCORE_DECLARATION_END

#define NCORE_NO_ERROR          0   /* No Error (good exit) */
#define NCORE_ERROR_USENO      -2   /* Use ERRNO instead */
#define NCORE_ERROR_NOMEM       1   /* No memory for the alloc */
#define NCORE_ERROR_BADDEALLOC  2   /* Bad Deallocation of memory */
#define NCORE_ERROR_BADALLOC    1   /* Equal to NOMEM */
#define NCORE_ERROR_TOOMANYREFS 3   /* Too many references */
#define NCORE_ERROR_INVARG      4   /* Invalid Argument */
#define NCORE_ERROR_ARGTYPE     5   /* Bad Argument Type */
#define NCORE_ERROR_NOMETA      6   /* No have metadata */
#define NCORE_ERROR_BADMETA     7   /* Bad metadata */
#define NCORE_ERROR_BADCMD      8   /* Bad Command */
#define NCORE_ERROR_NOCMD       9   /* No/Expected command */
#define NCORE_ERROR_BADMATH     10  /* Bad mathematics (math error) */
#define NCORE_ERROR_DIVZERO     11  /* Division By Zero */
#define NCORE_ERROR_DOMAIN      12  /* Math function domain error */
#define NCORE_ERROR_VALUE       13  /* Bad internal value */
#define NCORE_ERROR_FUNCTN      14  /* Bad function return value */
#define NCORE_ERROR_BADFILE     15  /* Bad file descriptor */
#define NCORE_ERROR_NOFILE      16  /* The file not exists */
#define NCORE_ERROR_NOACCESS    17  /* No have access to the file */
#define NCORE_ERROR_NOPERMS     18  /* No have the permissions */
#define NCORE_ERROR_NOCLIENT    19  /* No client */
#define NCORE_ERROR_IMPOSSIBLE  20  /* The action is impossible */
#define NCORE_ERROR_BADERR      21  /* Bad error */
#define NCORE_ERROR_VERYSLOW    22  /* The action is very slow */
#define NCORE_ERROR_UNTIME      23  /* Undeterminated execution time */
#define NCORE_ERROR_BADCOMPLEX  24  /* Bad complex number */
#define NCORE_ERROR_BADCPLXTIME 25  /* Bad complexity time */
#define NCORE_ERROR_BADPIPE     26  /* Bad PIPE connection */
#define NCORE_ERROR_NULL        27  /* Unexpected NULL pointer */
#define NCORE_ERROR_BADFCN      28  /* Bad function */
#define NCORE_ERROR_NOBLOCK     29  /* Try to block (wait) an async fcn */
#define NCORE_ERROR_PARSE       30  /* Parser error */
#define NCORE_ERROR_TOKEN       31  /* Tokenizer error */
#define NCORE_ERROR_TOOMANY     32  /* Too many arguments */
#define NCORE_ERROR_VERYFEW     33  /* Very few arguments */
#define NCORE_ERROR_NOPEN       34  /* The resource are not opened */
#define NCORE_ERROR_OPEN        35  /* The resource are opened */
#define NCORE_ERROR_READ        36  /* Unable to read / Fail to read */
#define NCORE_ERROR_WRITE       37  /* Unable to wrtie / Fail to write */
#define NCORE_ERROR_IO          38  /* IO error */
#define NCORE_ERROR_IOBUFF      39  /* IO Buffering error */

#define NCORE_TRY(code) if((ncore_errno = code) != NCORE_NO_ERROR)
#define NCORE_CATCH(error) if(ncore_errno == error)
#define NCORE_CATCH_ALL if(TRUE)

#endif /* ~_NCORE_ERROR_H_ */
