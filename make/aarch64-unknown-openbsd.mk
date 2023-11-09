EXE_EXT =
LIB_EXT = .a

INCLUDES = include
# fake libc that we build bellow
LIBS = c
LIBS_SEARCH = $(BUILD_OUT)

# when crosscompiling its needed
CFLAGS = -fno-stack-protector
LDFLAGS = -Wl,--dynamic-linker=/usr/libexec/ld.so

platform_deps: $(BUILD_OUT)/libc.so

$(BUILD_OUT)/libc.so:
	$(CC) --target=$(TARGET_TRIPLET) -fuse-ld=$(LD) -nostdlib -shared research/openbsd_libc_syscall/ld_so_mock.c -o $@
	
	