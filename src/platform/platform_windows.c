#include "seul/arch.h"
#include "seul/platform.h"
#include "seul/defines.h"
#include "seul/ints.h"

#if __target_windows
struct seul_platform_windows_process_environment_block_s* seul_platform_windows_get_peb() {
	return (struct seul_platform_windows_process_environment_block_s*)seul_arch_x64_read_gs(0x60);
}
#endif

