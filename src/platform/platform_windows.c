#include "seul/arch.h"
#include "seul/platform.h"
#include "seul/ints.h"

struct seul_platform_windows_process_environment_block_s* seul_platform_windows_get_peb() {
	return (struct seul_platform_windows_process_environment_block_s*)seul_arch_x64_read_gs(0x60);
}

