#ifndef __INTELLISENSE__
#error This header is intended for Intellisense consumption. Do not include it.
#endif

// Undefine Microsoft predefined macros
#undef _ATL_VER
#undef _M_IX86
#undef _M_X64
#undef _MFC_VER
#undef _MSC_VER
#undef _MSC_EXTENSIONS
#undef _NATIVE_WCHAR_T_DEFINED
#undef _WCHAR_T_DEFINED
#undef _WIN32
#undef _WIN64

//
// Polyfill for gcc and clang features which Intellisense misses
//

typedef char *__builtin_va_list, *__gnuc_va_list;

#define asm(...)
#define __asm__(...)
#define __asm
#define __asm(...)
#define __nonnull(...)
#define __attribute__(...)
#define __extension__
#define __inline__ inline
#define __signed__ signed
#define __restrict__
#define __gthrw(...)

// clang language extensions
#define __has_include(...) 0
#define __has_include_next(...) 0

// This is a crude hack to emulate clang __has_feature
// (since by defining __clang__, we lead libc++ to believe we're clang-compliant)
#define __has_feature(feature) (feature==1)
#define cxx_nullptr 1
#define cxx_decltype 1
#define cxx_exceptions __VA_EXCEPTIONS
#define cxx_rtti __VA_RTTI
#define cxx_strong_enums 1
#define is_base_of 1

#define __const const
#define __volatile volatile
#define __THROW

#define __cdecl

#define __typeof decltype
#define __builtin_va_start(...)
#define __builtin_va_end(...)
#define __builtin_vsnprintf(...)
#define __null 0

#endif
