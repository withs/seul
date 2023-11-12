#ifndef SEUL_ALLOCATORS_H
#define SEUL_ALLOCATORS_H

#include "seul/ints.h"
#include "seul/data_structures.h"
#include "seul/bool.h"

enum seul_allocator_os_proctection_e {
	saop_read = 0x01,
	saop_write = 0x02,
	saop_execute = 0x04,
};

enum seul_allocator_os_result_s {
	saor_ok,
	saor_err,
};

struct seul_allocator_mem_alloc_optional_s {
	struct seul_ds_array_view_s view;
	enum seul_allocator_os_result_s state;
};

struct seul_allocators_allocator_cb_s {
	struct seul_allocator_mem_alloc_optional_s (*alloc_f)(isize, enum seul_allocator_os_proctection_e);
	struct seul_allocator_mem_alloc_optional_s (*realloc_f)(isize);
	bool (*release_f)(isize);
};


// static const struct seul_allocators_allocator_cb_s seul_allocators_os_cb = (struct seul_allocators_allocator_cb_s){
// 	.alloc_f = ,
// 	.realloc_f = ,
// 	.release_f = ,
// };

// TODO: move those to platform.h
struct seul_allocator_mem_alloc_optional_s seul_platform_alloc_virtual_memory(void* att_address, isize of_size, enum seul_allocator_os_proctection_e has_protection); 
enum seul_allocator_os_result_s seul_platform_release_virtual_memory(struct seul_ds_array_view_s from_view);
#endif