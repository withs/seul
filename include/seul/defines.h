#ifndef SEUL_DEFINES_H
#define SEUL_DEFINES_H

// constants

#define __is_char_unsigned __CHAR_UNSIGNED__
#define __size_of_ptr __SIZEOF_POINTER__

// platforms

#if __OpenBSD__
  #define __target_openbsd __OpenBSD__
#else
  #define __target_openbsd 0
#endif

#if __APPLE__
  #define __target_macos __APPLE__
#else
  #define __target_macos 0
#endif

#if _WIN32 || _WIN64
  #define __target_windows 1
#else
  #define __target_windows 0
#endif

// archs

#if __aarch64__
  #define __arch_aarch64 __aarch64__
#else
  #define __arch_aarch64 0
#endif

#if __x86_64__ || __amd64__
  #define __arch_x64 1
#else
  #define __arch_x64 0
#endif

#ifdef __i386__
  #define __arch_x86 __i386__
#else
  #define __arch_x86 0
#endif

// compiler

#if __clang__
  #define __cc_is_clang __clang__
#else
  #define __cc_is_clang 0
#endif

#if __TINYC__
  #define __cc_is_tcc__ 1
#else
  #define __cc_is_tcc__ 0
#endif

#endif