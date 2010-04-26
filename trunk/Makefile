# Makefile

# Path to Simics installation

SIMICS=/home/jone4151/simics-workspace 

# Object files for the examples
OBJS_TIMER=boot_malta.o asm.o

# Project directory
PROJECT_DIR=/home/jone4151/OS/Proj/Ex

# GCC prefix
MIPS_PREFIX=/it/sw/cross/mips-idt/bin/mips-idt-elf

# gcc flags for the MIPS architecture:
#  -EL     : Little endian
#  -G0     : Always use small data (using register gp)
#  -mips32 : Compile for a 32-bit MIPS architecture
#
ARCH=-EL -G0 -mips32

# Other gcc flags
CFLAGS	+= -ggdb -Wall -Werror -I include

# Compiler and linker commands
CC=$(MIPS_PREFIX)-gcc
LD=$(MIPS_PREFIX)-ld -Ttext 80020000

do_boot_malta: bin/boot_malta 
	./scripts/run.sh $(SIMICS) $<

# Defines how object files (*.o) are created from C files (*.c)
build/%.o: src/%.c
	$(CC) $(ARCH) $(CFLAGS) -o $@ -c $<

# Defines how object files (*.o) are created from assembler files (*.S)
build/%.o: src/%.S
	$(CC) $(ARCH) $(CFLAGS) -o $@ -c $<

# Default: build all examples
all: boot_all

# Build all examples
boot_all: boot_malta

# Build the timer example
bin/boot_malta: build/$(OBJS_MALTA)
	$(LD) $(ARCH) -o $@ $^

# clean: remove object files and emacs backup files
clean:
	rm -f *.o *~
