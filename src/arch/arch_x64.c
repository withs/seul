#include "arch_internal.h"
#include "seul/defines.h"
#include "seul/ints.h"

// TODO: add include guard for arch, and maybe platform too ?

#if __arch_x64

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

// NOTE: changed to a fix args pass, to match openbsd syscall fn + it is more simple to call than set_nb() + syscall()
// only problem is that you can't pass more than 11 args, but 11 is the max i was atm + its sligthly slower since it have to 
// move all the args even if you not using it
// rcx 1 -> rdx
// rdx 2 -> r8
// r8  3 -> r9
// r9  4 -> 28(%rsp) 

// mov rcx, rax

// mov rdx, r10
// mov r8, rdx
// mov r9, r8
// mov 28(%rsp), r9

__attribute__((naked))
i32 seul_arch_x64fastcall_syscall(usize number, ...) {

  __asm__ __volatile__ (
    "movq %%rcx, %%rax\n\t" // load syscall number,

    // TEST: to try, it seems that rcx replace r10 for syscalls ? since when ? maybe be its my aarch64 windows vm ?
    // "movq %%rdx, %%r10\n\t"
    "movq %%rdx, %%rcx\n\t"
    "movq %%r8, %%rdx\n\t"
    "movq %%r9, %%r8\n\t"
    "movq 0x28(%%rsp), %%r9\n\t"

    "movq 0x30(%%rsp), %%r12\n\t"
    "movq %%r12, 0x28(%%rsp)\n\t"

    "movq 0x38(%%rsp), %%r12\n\t"
    "movq %%r12, 0x30(%%rsp)\n\t"
 
    "movq 0x40(%%rsp), %%r12\n\t"
    "movq %%r12, 0x38(%%rsp)\n\t"
 
    "movq 0x48(%%rsp), %%r12\n\t"
    "movq %%r12, 0x40(%%rsp)\n\t"
 
    "movq 0x50(%%rsp), %%r12\n\t"
    "movq %%r12, 0x48(%%rsp)\n\t"
  
    "movq 0x58(%%rsp), %%r12\n\t"
    "movq %%r12, 0x50(%%rsp)\n\t"
 
    "movq 0x50(%%rsp), %%r12\n\t"
    "movq %%r12, 0x58(%%rsp)\n\t"
    
    "syscall\n\t"
    "ret\n\t"
    :
    :
    : "r10", "r12"
  ); 
}

#endif