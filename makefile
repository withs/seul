.POSIX:

#TARGET_TRIPLET = x86_64-unknown-openbsd
TARGET_TRIPLET = aarch64-unknown-openbsd
#TARGET_TRIPLET = x86_64-windows-msvc

#CC = clang-16
CC = clang
LD = lld
AR = ar

BUILD_FOLDER = target
BUILD_OBJS = $(BUILD_FOLDER)/$(TARGET_TRIPLET)/objs
BUILD_OUT = $(BUILD_FOLDER)/$(TARGET_TRIPLET)

include make/$(TARGET_TRIPLET).mk

# FIXME: fix unused flag warnings
# shared flags
CFLAGS += -g3 -nostdlib -ffreestanding -fuse-ld=$(LD) -fcolor-diagnostics
CFLAGS += $(foreach inc, $(INCLUDES), -I $(inc)) 
CFLAGS += $(foreach lib_search, $(LIBS_SEARCH), -L $(lib_search)) 
CFLAGS += $(foreach lib, $(LIBS), -l $(lib)) --target=$(TARGET_TRIPLET)
	
SRCS = src/platform/platform_none.c src/platform/platform_windows.c \
		src/platform/platform_openbsd.c src/platform/platform_generic.c \
		src/arch/arch_none.c src/arch/arch_x64.c \
		src/data_structures/array_view.c src/data_structures/string_view.c \
		src/mem.c src/io/stdout.c
		
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: build_setup $(BUILD_OUT)/libseul$(LIB_EXT)
playground: all platform_deps $(BUILD_OUT)/playground$(EXE_EXT)

$(BUILD_OUT)/playground$(EXE_EXT): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) research/generic_playground.c $(BUILD_OBJS)/*.o -o $@

$(BUILD_OUT)/libseul$(LIB_EXT): $(OBJS)
	$(AR) -rcs $@ $(BUILD_OBJS)/*.o

build_setup:
	mkdir -p $(BUILD_OBJS)

clean:
	rm -rf target

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_OBJS)/$(notdir $@)

.PHONY: all build_setup clean playground