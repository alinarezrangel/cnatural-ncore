/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** OS-independend dynamic library load functions

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
