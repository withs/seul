#include "stdarg.h"

int get_stdout() {

  void* peb_stdout;
  
  __asm__ __volatile__ (
    "movq %%gs:0x60, %0\n\t" // load peb from GS
    "movq 0x20(%0), %0\n\t" // [peb + 0x20] = process_parameters
    "movq 0x28(%0), %0\n\t" // [process_parameter + 0x28] = stdout
    : "=r" ( peb_stdout )
  );

  return (int)peb_stdout;
}


// NOTE: calling manually but very limitd to nt_write_file
void nt_write_file(int fd, const char* msg, int len) {

  unsigned char isb[0x10];

  __asm__ __volatile__ (
    "subq $0x70, %%rsp\n\t"
    "movq $8, %%rax\n\t"
    "movq %[in_fd], %%r10\n\t"
    "movq $0, %%rdx\n\t"
    "movq $0, %%r8\n\t"
    "movq $0, %%r9\n\t"

    // "lea 0x50(%%rsp), %%rbx\n\t"
    // "movq %%rbx, 0x28(%%rsp)\n\t"
    "movq %[out_isb], 0x28(%%rsp)\n\t" // move addy of isb    
    "movq %[in_buff], 0x30(%%rsp)\n\t" // mov buff ptr
    "movq %[in_len], 0x38(%%rsp)\n\t" // mov msg len
    "movq $0, 0x40(%%rsp)\n\t" // byte offset 
    "movq $0, 0x48(%%rsp)\n\t" // key
    
    "syscall\n\t"
    
    "addq $0x70, %%rsp\n\t"
    :
    : [in_fd] "r" ((long long)fd), [out_isb] "r" (isb), [in_buff] "r" (msg), [in_len] "r" ((long long)len)
    : "rax", "r10", "r9", "r8", "rdx", "memory", "rsp", "rbx"
    );
  
}

// NOTE: let clang generate x64 fastcall
__attribute__((naked))
void nt_write_file2(void* fd, void* event, void* apc_routine, void* apc_context, void* isb, void* buff, long long len, void* byte_offset, void* key) {

  __asm__ __volatile__ (
      "movq %%rcx, %%r10\n\t" // when calling a syscall the fist args goes to r10 not rcx like a normal x64 fastcall
      "movq $8, %%rax\n\t"
      "syscall\n\t"
      "ret\n\t"
    :
    : // could have used input syntax also
    : "rax", "r10"
    );
  
}

// NOTE: put val in r11 which is a volatile register and not used in args passing, im not passing to rax directly because rax is more subject to be used as a temp var in the process of arg passng 
// IDEA: could save r11 on the stack and pop it a the end of nt_syscall, but not sure if its very usefull
void nt_syscall_prepare(long long nb) {
  __asm__ __volatile__ (
    "mov %[in_nb], %%r11\n\t"
    :
    : [in_nb] "r" (nb)
    : "r11"
  );
}

// NOTE: same as above but since we know that the first args is passed in rcx in x64fastcall (windows) we can eliminate stack use of above
__attribute__((naked))
void nt_syscall_prepare2(long long nb) {
  __asm__ __volatile__ (
    "mov %%rcx, %%r11\n\t"
    "ret\n\t"
    :
    :
    : "r11"
  );
}
__attribute__((naked))
void nt_syscall(void* one, ...) {

  __asm__ __volatile__ (
      "movq %%rcx, %%r10\n\t" // swap first arg
      "movq %%r11, %%rax\n\t" // load syscall number,
      "syscall\n\t"
      "ret\n\t"
    :
    : /*[in_syscall_nb] "a" (8)*/
    : "r10"
    );
  
}

void _start(void) {
  int stdout = get_stdout();
  
  nt_write_file(stdout, "manual\n", 7);

  unsigned char isb[0x10];
  nt_write_file2((void*)stdout, 0, 0, 0, isb, "clang\n", 6, 0, 0);


  // kinda hacky but seems to work even with optimisations -O3
  // it avoid the need of having multiple function to handle the numbers of args
  nt_syscall_prepare2(8);
  nt_syscall((void*)stdout, 0, 0, 0, isb, "generic\n", 8, 0, 0);
}

// clang research/win_syscall.c --target=x86_64-windows-msvc -fuse-ld=lld-link --for-linker "/entry:_start" --for-linker "/subsystem:console" -nostdlib -o wrs.exe
// https://gcc.gnu.org/onlinedocs/gcc/x86-Function-Attributes.html


/*
+ 0x0 -> call
+ 0x8 -> shadow store
+ 0x28 -> add isb
+ 0x30 -> buff
+ 0x38 -> msg len
+ 0x40 -> plarge_integer byte offset
+ 0x48 -> pulon kye
*/

// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntwritefile
// https://stackoverflow.com/questions/49947915/assembly-syscalls-in-64-bit-windows
// https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170
// https://wiki.osdev.org/Inline_assembly/
// https://csiflabs.cs.ucdavis.edu/~ssdavis/50/att-syntax.htm
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/peb/index.htm
