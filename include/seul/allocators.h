#ifndef SEUL_ALLOCATORS_H
#define SEUL_ALLOCATORS_H

#include "seul/ints.h"

enum seul_allocator_os_proctection_e {
	saop_read = 0x01,
	saop_write = 0x02,
	saop_execute = 0x04,
};

enum seul_allocator_os_flags_e {
	saof_default = 0x0,
};

enum seul_allocator_os_result_s {
	saor_ok,
	saor_err,
};

struct seul_allocator_mem_alloc_optional_s {
	void* address;
	isize size;
	enum seul_allocator_os_result_s state;
};

// struct allocator_cb_s {
// 	void* (alloc_f*)(isize);
// 	void* (realloc_f*)(isize);
// 	void* (release_f*)(isize);
// }


// static const struct allocator_cb_s seul_allocator_os_cb = (struct allocator_cb_s){
// 	.alloc_f = ,
// 	.realloc_f = ,
// 	.release_f = ,
// };


struct seul_allocator_mem_alloc_optional_s seul_platform_alloc_virtual_memory(void* att_address, isize of_size, enum seul_allocator_os_proctection_e has_protection); 
#endif