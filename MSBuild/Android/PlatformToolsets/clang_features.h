// This file contains carefully maintained preprocessor definitions
// to mimic clang built-in defines within Intellisense.
//
// The switches in android_gcc_compile.xml for various compiler
// features should trigger the conditionals in this file.

#ifdef ___cplusplus
	#define _GNU_SOURCE 1
	#define __DEPRECATED 1
	#ifndef __VA_NO_EXCEPTIONS
		#define __EXCEPTIONS 1
	#endif
	#define __GNUG__ 4
	#ifndef __VA_NO_RTTI
		#define __GXX_RTTI 1
	#endif
	#define __GXX_WEAK__ 1
	#undef __cplusplus
	#define __cplusplus 199711L
	#define __GNUC_GNU_INLINE__ 1
	#define __private_extern__ extern
#else
	#define __GNUC_STDC_INLINE__ 1
	#define __STDC_VERSION__ 199901L
#endif

#ifdef __VA_ARM5
	#define __ARM_ARCH 5
	#define __ARM_ARCH_5TE__ 1
	#define __GCC_ATOMIC_BOOL_LOCK_FREE 1
	#define __GCC_ATOMIC_CHAR_LOCK_FREE 1
	#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 1
	#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 1
	#define __GCC_ATOMIC_INT_LOCK_FREE 1
	#define __GCC_ATOMIC_LLONG_LOCK_FREE 1
	#define __GCC_ATOMIC_LONG_LOCK_FREE 1
	#define __GCC_ATOMIC_POINTER_LOCK_FREE 1
	#define __GCC_ATOMIC_SHORT_LOCK_FREE 1
	#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE 1
	#define __SOFTFP__ 1
#endif

#ifdef __VA_ARM7
	#define __ARM_ARCH 7
	#define __ARM_ARCH_7A__ 1
	#define __ARM_ARCH_PROFILE A
	#define __ARM_VFPV3__ 1
	#define __GCC_ATOMIC_BOOL_LOCK_FREE 2
	#define __GCC_ATOMIC_CHAR_LOCK_FREE 2
	#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 2
	#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 2
	#define __GCC_ATOMIC_INT_LOCK_FREE 2
	#define __GCC_ATOMIC_LLONG_LOCK_FREE 2
	#define __GCC_ATOMIC_LONG_LOCK_FREE 2
	#define __GCC_ATOMIC_POINTER_LOCK_FREE 2
	#define __GCC_ATOMIC_SHORT_LOCK_FREE 2
	#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE 2
	#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
	#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
	#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
	#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
	#define __VFP_FP__ 1
#endif

#ifdef __VA_ARM7_HARD_FLOAT
	#define __ARM_PCS_VFP 1
#endif

#ifdef __VA_SHORT_WCHAR
	#define __SIZEOF_WCHAR_T__ 2
	#define __WCHAR_MAX__ 65535U
	#define __WCHAR_TYPE__ unsigned short
	#define __WCHAR_WIDTH__ 16
#else
	#define __SIZEOF_WCHAR_T__ 4
	#define __WCHAR_MAX__ 4294967295U
	#define __WCHAR_TYPE__ unsigned int
	#define __WCHAR_WIDTH__ 32
#endif

#if defined(__VA_THUMB) && defined(__arm__)
	#define __thumb__ 1
	#define __thumb2__ 1
	#define __THUMBEL__ 1
#endif

#ifndef __VA_NO_PIC
	#define __PIC__ 1
	#define __pic__ 1
#endif

#include "intellisense.h"
