TARGET := 
TARGET := riscv64-unknown-linux-gnu-
CC := $(TARGET)gcc
LD := $(TARGET)gcc

CFLAGS := -fPIC -O3 -fno-builtin-printf -fno-builtin-memcmp -nostdinc -nostartfiles -fvisibility=hidden -fdata-sections -ffunction-sections
LDFLAGS := -fdata-sections -ffunction-sections

ifneq ($(TARGET), )
	CFLAGS := $(CFLAGS) -nostdlib
else
	CFLAGS := -fsanitize=address -fsanitize=undefined
endif

# CFLAGS := $(CFLAGS) -Wall -Werror -Wno-nonnull -Wno-nonnull-compare -Wno-unused-function -g
# LDFLAGS := $(LDFLAGS) -Wl,-static -Wl,--gc-sections


CFLAGS := $(CFLAGS) -I c -I deps/ckb-c-stdlib/libc -I deps/ckb-c-stdlib

PARAMS = sphincs-shake-256f
THASH = robust

SOURCES = c/address.c c/merkle.c c/wots.c c/wotsx1.c c/utils.c c/utilsx1.c c/fors.c c/sign.c c/randombytes.c
HEADERS = c/params.h c/address.h c/merkle.h c/wots.h c/wotsx1.h c/utils.h c/utilsx1.h c/fors.h c/api.h c/hash.h c/thash.h c/randombytes.h

CFLAGS := $(CFLAGS) -DPARAMS=$(PARAMS) -DCKB_DECLARATION_ONLY -DCKB_C_STDLIB_PRINTF

SOURCES += c/fips202.c c/hash_shake.c c/thash_shake_$(THASH).c
HEADERS += c/fips202.h

# SOURCES += deps/ckb-c-stdlib/libc/src/impl.c

ifeq ($(TARGET), )
run_test: build/sphincsplus_example
		./build/sphincsplus_example
else
run_test: build/sphincsplus_example
		ckb-debugger --bin ./build/sphincsplus_example
endif

build/sphincsplus_example: c/ckb-sphincsplus-example.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $<

clean:
	rm -rf build/sphincsplus_example