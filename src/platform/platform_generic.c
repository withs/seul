#include "seul/arch.h"
#include "seul/ints.h"
#include "seul/defines.h"
#include "seul/platform.h"
#include "seul/allocators.h"

i32 seul_platform_write(void* to_fd, void* from_buff, usize with_len) {

	#if __target_windows

	u8 out_isb[0x10];

	return seul_platform_windows_syscall(8, to_fd, 0, 0, 0, out_isb, from_buff, with_len, 0, 0);
	
	#endif

	#if __target_openbsd

	return seul_platform_openbsd_syscall(4, to_fd, from_buff, with_len);
	
	#endif
	
}

void seul_platform_exit(i32 with_code) {

	#if __target_windows
	// FIXME: Both -1 and 0 make the program crash instead of killing it, again maybe its my aarch64 vm
	// https://undocumented-ntinternals.github.io/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FProcess%2FNtTerminateProcess.html
	// https://doxygen.reactos.org/d3/d5c/zwfuncs_8h.html#a719a7ce85358702f11dce2cd31896b4b
	// fixed by casting handle to a 8bytes type
	seul_platform_windows_syscall(44, (usize)-1, with_code);
	#endif

	#if __target_openbsd
	seul_platform_openbsd_syscall(1, with_code);
	#endif
}

i32 seul_platfom_windows_mem_protection_translate(i32 from_unix) {
	i32 windows_eq_prot = 0x1;

	if ( from_unix & saop_read )    windows_eq_prot *= 0x2;
	if ( from_unix & saop_write )   windows_eq_prot *= ( 0x2 + ((~from_unix & saop_read) * 6) );
	if ( from_unix & saop_execute ) windows_eq_prot *= 0x10;

	return windows_eq_prot;
}


// FIXME: tmp decl to make lld happy
void* memset(void* a, i32 b, isize c) {}



// NOTE: by default alloc flags are PRIVATE | ANON for openbsd and RESERVE | COMMIT for windows
// TODO: add if flags or prot ! 0 in args to overwrite default flags
// FIXME: check openbsd on x86_64 because on an aarch64 one i can't alloc anything tried different prot, flags etc silk get errno 22, windows work tho
// NOTE: fault was fd flags not set on -1, should have look use of mmap in openbsd srcs earlier..
struct seul_allocator_mem_alloc_optional_s seul_platform_alloc_virtual_memory(void* att_address, isize of_size, enum seul_allocator_os_proctection_e has_protection) {

	struct seul_allocator_mem_alloc_optional_s probably_allocated_buff = (struct seul_allocator_mem_alloc_optional_s){ 
		.state = saor_ok,
		.address = 0,
		.size = 0,
	};

	#if __target_windows
	isize in_out_size = of_size;
	void* in_out_address = att_address;

	i32 windows_eq_prot_flags = seul_platfom_windows_mem_protection_translate(has_protection);
	i32 nt_status = seul_platform_windows_syscall(0x18, (usize)-1, &in_out_address, 0, &in_out_size, (usize)(0x1000 | 0x2000), (usize)windows_eq_prot_flags);

	if ( nt_status != 0 ) {
		probably_allocated_buff.state = saor_err;
		return probably_allocated_buff;
	}
		
	probably_allocated_buff.address = in_out_address;
	probably_allocated_buff.size = in_out_size;
	#endif

	#if __target_openbsd
	probably_allocated_buff.address = (void*)seul_platform_openbsd_syscall(0x31, att_address, of_size, (i32)has_protection, (i32)(0x1 | 0x1000), (i32)-1, 0);

	if ( (usize)probably_allocated_buff.address == -1 ) {
		probably_allocated_buff.state = saor_err;
		return probably_allocated_buff;		
	}
	
	probably_allocated_buff.size = of_size;
	#endif

	return probably_allocated_buff;
	
}