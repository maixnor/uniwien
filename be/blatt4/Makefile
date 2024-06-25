PROGS=client server

# For compiling .S (assembly) files
AS=gcc
AFLAGS=-s -Wall -Wextra -Werror -static -Os -m64 -nostartfiles \
       -nostdlib -masm=intel -Wl,--build-id=none -Wl,--nmagic

# For compiling .asm (NASM) files
NYA=nasm
NYAFLAGS=-f elf64

# For compiling .rs (Rust) files
RC=rustc
RFLAGS=--edition=2021 --extern libc=/libc.rlib -D warnings

# For compiling .c files
CC=gcc
CFLAGS=-std=gnu11 -Os -pedantic -Wall -Wextra -Werror -D_GNU_SOURCE

# For compiling .cpp files
CXX=g++
CXXFLAGS=-std=gnu++20 -Os -pedantic -Wall -Wextra -Werror

all: $(PROGS)

%: %.S
	$(AS) $(AFLAGS) -o $@ $<

%: %.asm
	$(NYA) $(NYAFLAGS) -o tmp.o $<
	ld -o $@ tmp.o
	rm tmp.o

%: %.rs
	$(RC) $(RFLAGS) --crate-name $@ $<

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(PROGS)

.PHONY: all clean
