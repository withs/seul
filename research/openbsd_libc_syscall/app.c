__asm__ (
	".section \".note.openbsd.ident\", \"a\"\n"
	".p2align 2\n"
	".long 0x8\n"
	".long 0x4\n"
	".long 0x1\n"
	".asciz \"OpenBSD\"\n"
	".long 0x0\n"
	".previous\n"
);

extern int syscall(int number, ...);

void _start() {
  syscall(4, 1, "heloo\n", 6);
  syscall(4, 1, "heloo\n", 6);
  syscall(1, 1);
}

// clang --target=aarch64-unknown-openbsd -nostdlib -shared -c shared.c -o shared.o
// ld.lld -nostdlib -shared shared.o -o libc.so
// clang --target=aarch64-unknown-openbsd -c app.c -o app.o
// ld.lld -dynamic-linker /usr/libexec/ld.so -nostdlib -L. -lc -v app.o -o app
