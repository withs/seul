cross:
	clang --target=aarch64-unknown-openbsd -nostdlib -shared -c shared.c -o shared.o
	ld.lld -nostdlib -shared shared.o -o libc.so
	clang --target=aarch64-unknown-openbsd -c app.c -o app.o
	ld.lld -dynamic-linker /usr/libexec/ld.so -nostdlib -L. -lc -v app.o -o app

clean:
	rm *.so
	rm *.o
	rm app