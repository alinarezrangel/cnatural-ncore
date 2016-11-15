/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** OS-dependend dynamic library load functions
**************************
**************************************************** */

#include "wrap_os/dynapi.h"

NCoreError_t ncore_os_dynlib_new(NCoreOSDynLib_t** dynlib)
{
	*dynlib = malloc(sizeof(NCoreOSDynLib_t));

	if(dynlib == NULL)
		return NCORE_ERROR_BADALLOC;

	(*dynlib)->handler = NULL;
	(*dynlib)->isOpen = FALSE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_dynlib_destroy(NCoreOSDynLib_t** dynlib)
{
	if((*dynlib)->isOpen)
		return NCORE_ERROR_OPEN;

	free(*dynlib);

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_dynlib_open(
	NCoreOSDynLib_t* dynlib,
	const NCoreString_t libname
)
{
	if(dynlib->isOpen)
		return NCORE_ERROR_OPEN;

#if defined(NCORE_OS_POSIXLIKE)
	dynlib->handler = dlopen(NCORE_RSTR(libname), RTLD_LAZY);
#else
#	error "Unable to determine what system use for open a dynamic library ncore_os_dynlib_open"
#endif

	if(dynlib->handler == NULL)
		return NCORE_ERROR_USENO;

	dynlib->isOpen = TRUE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_dynlib_load(
	NCoreOSDynLib_t* dynlib,
	const NCoreString_t symbol,
	NCoreFunctionType_t* fcn
)
{
	int rt = 0;
#if defined(NCORE_OS_POSIXLIKE)
	char* dl_msg = NULL;
#endif

	if(!dynlib->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	dlerror();
	fcn = dlsym(dynlib->handler, NCORE_RSTR(symbol));
	dl_msg = dlerror();
	rt = dl_msg == NULL;
#else
#	error "Unable to determine what system use for load a symbol of a dynamic library ncore_os_dynlib_load"
#endif

	if(rt != 0)
		return NCORE_ERROR_USENO;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_os_dynlib_close(NCoreOSDynLib_t* dynlib)
{
	int rt = 0;

	if(!dynlib->isOpen)
		return NCORE_ERROR_NOPEN;

#if defined(NCORE_OS_POSIXLIKE)
	rt = dlclose(dynlib->handler);
#else
#	error "Unable to determine what system use for close a dynamic library ncore_os_dynlib_close"
#endif

	if(rt != 0)
		return NCORE_ERROR_USENO;

	dynlib->isOpen = FALSE;

	return NCORE_NO_ERROR;
}
