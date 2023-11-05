.POSIX:
.SUFFIXES:
.PHONY: clean playground pre

# yes it's weird ^^, it miss the prod/debug
# to add new components:
# $(OBJ_FOLDER)/comp.o: source_files.c
# and add $(OBJ_FOLDER)/comp.o to $(OUT_FOLDER)/$(TARGET_OUT): $(OBJ_FOLDER)/comp.o:

TARGET_TRIPLE := aarch64-unknown-openbsd
TARGET_OUT := libseul.a
BUILD_FOLDER = target
OBJ_FOLDER = $(BUILD_FOLDER)/$(TARGET_TRIPLE)/obj
OUT_FOLDER = $(BUILD_FOLDER)/$(TARGET_TRIPLE)

CC = clang
CFLAGS = -Os --target=${TARGET_TRIPLE} -I include/

all: pre $(OUT_FOLDER)/$(TARGET_OUT)

$(OUT_FOLDER)/$(TARGET_OUT): $(OBJ_FOLDER)/arch.o $(OBJ_FOLDER)/platform.o $(OBJ_FOLDER)/arch_x64.o $(OBJ_FOLDER)/platform_windows.o $(OBJ_FOLDER)/platform_openbsd.o $(OBJ_FOLDER)/platform_generic.o
	$(AR) -rcs $@ $^
$(OBJ_FOLDER)/arch.o: src/arch/arch_none.c src/arch/arch_internal.h
$(OBJ_FOLDER)/arch_x64.o: src/arch/arch_x64.c src/arch/arch_internal.h
$(OBJ_FOLDER)/platform.o: src/platform/platform_none.c
$(OBJ_FOLDER)/platform_windows.o: src/platform/platform_windows.c 
$(OBJ_FOLDER)/platform_openbsd.o: src/platform/platform_openbsd.c 
$(OBJ_FOLDER)/platform_generic.o: src/platform/platform_generic.c 

%.o %.c:
	 $(CC) $(CFLAGS) -c $(filter %.c,$^) -o $@
	
clean:
	rm -rf $(BUILD_FOLDER)

pre:
	mkdir -p ${OBJ_FOLDER}
	mkdir -p $(OUT_FOLDER)

playground: all 
	$(CC) $(CFLAGS) -I include/ -c research/generic_playground.c -o $(OUT_FOLDER)/playground.o
	ld.lld -dynamic-linker /usr/libexec/ld.so -nostdlib -L./research/openbsd_libc_syscall -lc -L $(OUT_FOLDER) -l seul $(OUT_FOLDER)/playground.o -o $(OUT_FOLDER)/playground
