# Makefile

# Path to Simics installation

SIMICS_J=/home/jone4151/simics-workspace 
SIMICS_P=/home/pebo6223/simics-workspace 
SIMICS_S=/home/stri1033/simics-workspace 
SIMICS_K=/home/krem7521/simics-workspace 

EXECUTABLES=$(addprefix bin/, boot_malta)

# Object files for the examples
OBJS_MALTA=boot_malta.o asm.o

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
CFLAGS	+= -ggdb -Wall -fno-builtin -I include/

# Compiler and linker commands
CC=$(MIPS_PREFIX)-gcc
LD=$(MIPS_PREFIX)-ld -Ttext 80020000

boot_j: bin/boot 
	./scripts/run.sh $(SIMICS_J) $<

boot_p: bin/boot 
	./scripts/run.sh $(SIMICS_P) $<

boot_s: bin/boot 
	./scripts/run.sh $(SIMICS_S) $<

boot_k: bin/boot 
	./scripts/run.sh $(SIMICS_K) $<

# Defines how object files (*.o) are created from C files (*.c)
build/%.o: src/%.c
	$(CC) $(ARCH) $(CFLAGS) -o $@ -c $<

# Defines how object files (*.o) are created from assembler files (*.S)
build/%.o: src/%.S
	$(CC) $(ARCH) $(CFLAGS) -o $@ -c $<

# Default: build all examples
all: boot_all

# Build all examples
boot_all: bin/boot

# Build the timer example
bin/boot:  $(addprefix build/, kjell.o init.o stdlib.o debug.o user_prog.o interrupt_handler.o device_handler.o process_handler.o scheduler.o _boot.o api.o)
	$(LD) $(ARCH) -o $@ $^

#### Add dependency on headerfile of various tty.o files

build/%.o: %.c include/%.h
	$(CC) $(ARCH) $(CFLAGS)  -c $< -o $@	

# clean: remove object files and emacs backup files
clean: 
	pwd
	rm -f build/*.o
	rm -f include/*~ include/#* include/*#
	rm -f src/*~ src/#* src/*#
	rm -f scripts/*~ scripts/#* scripts/*#
	rm -f ${EXECUTABLES}
