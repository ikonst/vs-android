// This file contains carefully maintained preprocessor definitions
// to mimic gcc built-in defines within Intellisense.
//
// The switches in android_gcc_compile.xml for various compiler
// features should trigger the conditionals in this file.

#ifdef ___cplusplus
	#define _GNU_SOURCE 1
	#define __DEPRECATED 1
	#define __GNUG__ 4
	#if __VA_RTTI
		#define __GXX_RTTI 1
	#endif
	#define __GXX_WEAK__ 1
	#define __WCHAR_UNSIGNED__ 1
	#undef __cplusplus
	#define __cplusplus 199711L
#endif

#if __VA_EXCEPTIONS
	#define __EXCEPTIONS 1
#endif

#ifdef __VA_ARM5
	#define __ARM_ARCH 5
	#define __ARM_ARCH_5TE__ 1
	#define __ARM_ARCH_ISA_THUMB 1
#endif

#ifdef __VA_ARM7
	#define __ARM_ARCH_PROFILE 65
	#define __ARM_ARCH_ISA_THUMB 2
	#define __ARM_ARCH 7
	#define __ARM_ARCH_7A__ 1
#endif

#ifdef __VA_ARM7_HARD_FLOAT
	#define __ARM_PCS_VFP 1
#else
	#define __ARM_PCS 1
	#define __SOFTFP__ 1
#endif

#ifdef __VA_SHORT_ENUMS
	#define __ARM_SIZEOF_MINIMAL_ENUM 1
#else
	#define __ARM_SIZEOF_MINIMAL_ENUM 4
#endif

#ifdef __VA_SHORT_WCHAR
	#ifdef __arm__
		#define __ARM_SIZEOF_WCHAR_T 2
	#endif
	#define __SIZEOF_WCHAR_T__ 2
	#define __WCHAR_MAX__ 65535U
	#define __WCHAR_TYPE__ unsigned short
#else
	#ifdef __arm__
		#define __ARM_SIZEOF_WCHAR_T 4
	#endif
	#define __SIZEOF_WCHAR_T__ 4
	#define __WCHAR_MAX__ 4294967295U
	#define __WCHAR_TYPE__ unsigned int
#endif

#if defined(__VA_THUMB) && defined(__arm__)
	#define __THUMBEL__ 1
#endif

#if __VA_PIC
	#define __PIC__ 1
	#define __pic__ 1
#endif

#include "intellisense.h"
