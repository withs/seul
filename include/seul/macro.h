#ifndef SEUL_MACRO_H
#define SEUL_MACRO_H

#include "seul/ints.h"

#define seul_size_of(expression) ((isize)sizeof(expression))
#define seul_align_as(align_size) _Alignas(align_size)
#define seul_align_of(expression) ((isize)(_Alignof(expression)))

#define seul_count_of_static_array(array) ((usize)(seul_size_of(array) / seul_size_of( array[0] )))
#define seul_len_of_static_array(array) ((usize)(seul_count_of_static_array(array) -1))

#define seul_offset_of_struct(type, member) (isize)( &(((struct type*)0)->member) )

#endif
