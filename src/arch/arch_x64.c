#include "arch_internal.h"
#include "seul/defines.h"
#include "seul/ints.h"

// TODO: add include guard for arch, and maybe platform too ?

#if __target_x64

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



// NOTE: kinda hacky but seems to work even with optimisations -O3
// it avoid the need of having multiple function to handle the numbers of args
// it put the syscall number in r11 which is a volatile register and not used in args passing, im not passing to rax directly because rax is more subject to be used as a temp var in the process of arg passng 
// IDEA: could save r11 on the stack and pop it a the end of nt_syscall, but not sure if its very usefull
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

#endif