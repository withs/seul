#ifndef SEUL_PLATFORM_H
#define SEUL_PLATFORM_H

#include "seul/ints.h"
#include "seul/defines.h"

enum platform_e {
	platform_nonen,
	platform_openbsd,
	platform_macos,
	platform_windows,
};

#if __target_openbsd
	#define __target_platform ((enum platform_e)platform_openbsd)
#elif __target_macos
	#define __target_platform ((enum platform_e)platform_macos)
#elif __taget_windows
	#define __target_platform ((enum platform_e)platform_windows)
#else
	#define __target_platform ((enum platform_e)platform_none)
#endif

// TODO: add include guard for platform
#if __target_windows
// NOTE: this is a small subset of peb below, i'll add more when i'll need it same for all the structs bellow
struct seul_platform_windows_user_process_parameters_s {
	u32 maximum_length;
	u32 length;
	u32 flags;
	u32 debug_flags;
	void* console_handle;
	u32 console_flags;
	void* standard_input;
	void* standard_output;
	void* standard_error;
};

struct seul_platform_windows_process_environment_block_s {
	u8 inherited_address_spacei;
	u8 read_image_file_exec_options;
	u8 being_debugged;
	u8 spare_bool;
	u8 padding_0[4];
	void* mutant;
	void* image_base_address;
	void* ldr;
	struct seul_platform_windows_user_process_parameters_s* process_parameters;
};

struct seul_platform_windows_process_environment_block_s* seul_platform_windows_get_peb();
#endif

#endif
