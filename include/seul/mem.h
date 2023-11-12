#ifndef SEUL_MEM_H
#define SEUL_MEM_H


void seul_mem_set_val(isize with_len, u8 at_address[static with_len], u8 and_val);
void* memset(void* add, i32 val, isize num);

#endif
