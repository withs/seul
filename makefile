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

CC = clang-16
CFLAGS = -g --target=${TARGET_TRIPLE}

all: pre $(OUT_FOLDER)/$(TARGET_OUT)

$(OUT_FOLDER)/$(TARGET_OUT): $(OBJ_FOLDER)/arch.o $(OBJ_FOLDER)/platform.o
	$(AR) -rcs $@ $^
$(OBJ_FOLDER)/arch.o: src/arch/arch_none.c src/arch/arch_internal.h
$(OBJ_FOLDER)/platform.o: src/platform/platform_none.c

%.o %.c:
	 $(CC) $(CFLAGS) -c $(filter %.c,$^) -o $@
	
clean:
	rm -rf $(BUILD_FOLDER)

pre:
	mkdir -p ${OBJ_FOLDER}
	mkdir -p $(OUT_FOLDER)

playground: all 
	$(CC) $(CFLAGS) -L $(OUT_FOLDER) -l seul -I include/ research/playground.c -o $(OUT_FOLDER)/playground