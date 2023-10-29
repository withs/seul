#ifndef SEUL_PLATFORM_H
#define SEUL_PLATFORM_H

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

void seul_platform_none(void);

#endif