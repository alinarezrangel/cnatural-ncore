/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Detect the OS name and type.

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

#ifndef _NCORE_WRAPOS_OSTYPE_H_
#define _NCORE_WRAPOS_OSTYPE_H_

#if defined(_AIX)
#	define NCORE_OS_AIX 1
#	define NCORE_OS "AIX"
#elif defined(__ANDROID__)
#	define NCORE_OS_ANDROID 1
#	define NCORE_OS "Android"
#elif defined(AMIGA) || defined(__amigaos__)
#	define NCORE_OS_AMIGAOS 1
#	define NCORE_OS "AmigaOS"
#elif defined(__BEOS__)
#	define NCORE_OS_BEOS 1
#	define NCORE_OS "BeOS"
#elif defined(__bg__) || defined(__THW_BLUEGENE__)
#	define NCORE_OS_BLUEGENE 1
#	define NCORE_OS "BlueGene"
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#	define NCORE_OS_BSD 1
#	define NCORE_OS_POSIXLIKE 1
#	if defined(__FreeBSD__)
#		define NCORE_OS_FREEBSD 1
#		define NCORE_OS "FreeBSD"
#	elif defined(__NetBSD__)
#		define NCORE_OS_NETBSD 1
#		define NCORE_OS "NetBSD"
#	elif defined(__OpenBSD__)
#		define NCORE_OS_OPENBSD 1
#		define NCORE_OS "OpenBSD"
#	elif defined(__bsdi__)
#		define NCORE_OS_BSDI 1
#		define NCORE_OS_BSDOS 1
#		define NCORE_OS "BSD/OS"
#	elif defined(__DragonFly__)
#		define NCORE_OS_DRAGONFLY 1
#		define NCORE_OS "DragonFly BSD"
#	else
#		define NCORE_OS "BSD-based"
#	endif
#elif defined(__CYGWIN__)
#	define NCORE_OS_CYGWIN 1
#	define NCORE_OS "CygWin"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(_WIN32)
#	define NCORE_OS_WIN 1
#	if defined(_WIN64)
#		define NCORE_OS_WIN64 1
#		define NCORE_OS "Windows 64-bits"
#	else
#		define NCORE_OS_WIN32 1
#		define NCORE_OS "Windows 32-bits"
#	endif
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
#	define NCORE_OS_LINUX 1
#	define NCORE_OS "GNU/Linux based"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__GNU__) || defined(__gnu_hurd__)
#	define NCORE_OS_HURD 1
#	define NCORE_OS "GNU/Hurd based"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__FreeBSD_kernel__) && defined(__GLIBC__)
#	define NCORE_OS_KFREEBSD 1
#	define NCORE_OS "GNU/kFreeBSD based"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(_hpux) || defined(__hpux) || defined(hpux)
#	define NCORE_OS_HPUX 1
#	define NCORE_OS "HP-UX"
#elif defined(__OS400__)
#	define NCORE_OS_OS400 1
#	define NCORE_OS "OS400"
#elif defined(__INTEGRITY)
#	define NCORE_OS_INTEGRITY 1
#	define NCORE_OS "Integrity"
#elif defined(__INTERIX)
#	define NCORE_OS_INTERIX 1
#	define NCORE_OS "Interix"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__INTEGRITY)
#	define NCORE_OS_INTEGRITY 1
#	define NCORE_OS "Integrity"
#elif defined(__Lynx__)
#	define NCORE_OS_LYNX 1
#	define NCORE_OS "Lynx"
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__)
#	define NCORE_OS_APPLE 1
#	define NCORE_OS "Apple macOS or Apple-based"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__OS9000) || defined(_OSK)
#	define NCORE_OS_MICROWAVEOS9 1
#	define NCORE_OS "OS-9"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__minix)
#	define NCORE_OS_MINIX 1
#	define NCORE_OS "Minix"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__MORPHOS__)
#	define NCORE_OS_MORPHOS 1
#	define NCORE_OS "MorphOS"
#	define NCORE_OS_POSIXLIKE 1
#elif defined(__TANDEM)
#	define NCORE_OS_NONSTOP 1
#	define NCORE_OS "NonStop"
#elif defined(__nucleus__)
#	define NCORE_OS_NUCLEUS 1
#	define NCORE_OS "Nucleus"
#else
#	error "Undetected OS, please define NCORE_OS to an string indicating the OS\
name and define NCORE_OS_POSIXLIKE if is POSIX-like"
#endif

#endif /* ~_NCORE_WRAPOS_OSTYPE_H_ */
