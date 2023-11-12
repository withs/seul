#include "seul/ints.h"

void seul_mem_set_val(isize with_len, u8 at_address[static with_len], u8 and_val) {
	for ( isize cnt = 0 ; cnt < with_len ; cnt++ ) {
		at_address[cnt] = and_val;
	}
}

void* memset(void* add, i32 val, isize num) {
	seul_mem_set_val(num, add, (u8)val);
	return add;
}

