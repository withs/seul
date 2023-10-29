#include "stdio.h"

#include "seul/ints.h"
#include "seul/defines.h"
#include "seul/platform.h"
#include "seul/arch.h"

int main(void) {

	printf("is macos: %d\n", __target_macos);
	printf("target_platform: %d\n", __target_platform);
	printf("target_arch: %d\n", __target_arch);

	seul_arch_none();

	return 1;
}
