#ifndef SEUL_INTS_H
#define SEUL_INTS_H

#include "seul/defines.h"

typedef unsigned char u8;
typedef signed char i8;

typedef unsigned short u16;
typedef short i16;

typedef unsigned int u32;
typedef signed int i32;

typedef unsigned long long u64;
typedef signed long long i64;

typedef float f32;
typedef double f64;

#if __size_of_ptr == 8
  typedef long long int isize;
  typedef long long unsigned int usize;
#else
  typedef int isize;
  typedef unsigned int usize;
#endif

#endif
