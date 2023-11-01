#ifndef SEUL_PLATFORM_H
#define SEUL_PLATFORM_H

#include "seul/ints.h"

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
