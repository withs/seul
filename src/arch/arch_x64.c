#include "arch_internal.h"
#include "seul/ints.h"



void* seul_arch_x64_read_gs(usize with_offset) {

  void* gs;
  
  __asm__ __volatile__ (
    "movq %%gs:(%[in_offset]), %[out_gs]\n\t" // load gs:with_offset
		: [out_gs] "=r" (gs)
		: [in_offset] "r" (with_offset)
  	:
	);

  return gs;
}

__attribute__((naked))
void seul_arch_x64fastcall_syscall_set_call(usize with_number) {

	__asm__ __volatile__ (
		"mov %%rcx, %%r11\n\t"
		"ret\n\t"
		:
		:
		: "r11"
	);
}

__attribute__((naked))
void seul_arch_x64fastcall_syscall(void* _first, ...) {

  __asm__ __volatile__ (
    "movq %%rcx, %%r10\n\t" // swap first arg
    "movq %%r11, %%rax\n\t" // load syscall number,
    "syscall\n\t"
    "ret\n\t"
    :
    :
    : "r10"
  ); 
}
