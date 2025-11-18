TARGET = fenestra

CXXC = i686-elf-g++
CXXFLAGS = -ffreestanding -m32 -g -I include 
LD = i686-elf-ld
LDFLAGS = -nostartfiles -nostdlib -nolibc -LE:\msys64\usr\lib\gcc\i386-elf\12.2.0 E:\msys64\usr\lib\gcc\i386-elf\12.2.0\crtbegin.o E:\msys64\usr\lib\gcc\i386-elf\12.2.0\crtend.o
AC = nasm
AFLAGS = -felf32 -i src/

SRC = src

CSRCS = $(wildcard $(SRC)/*.cpp) #C source files
CSRCS := $(CSRCS) $(wildcard $(SRC)/kernel/*.cpp)
CSRCS := $(CSRCS) $(wildcard $(SRC)/drivers/*.cpp)
COBJS := $(patsubst %.cpp, %.o, $(CSRCS)) #C object files

ASRCS = $(wildcard $(SRC)/*.asm) #Assembly source files
ASRCS := $(ASRCS) $(wildcard $(SRC)/kernel/*.asm)
ASRCS := $(ASRCS) $(wildcard $(SRC)/drivers/*.asm)
ASRCS := $(ASRCS) $(wildcard $(SRC)/kernel/*.S)
AOBJS := $(patsubst %.asm, %.o, $(ASRCS)) #Assembly object files
AOBJS := $(patsubst %.S, %.o, $(AOBJS))

BSRC = src/boot/boot.asm #Boot source file
ZSRC = src/boot/zeroes.asm #Zeroes source file

$(TARGET): clear debug boot.bin kernel.bin zeroes.bin
	cat "boot.bin" "kernel.bin" > "full.bin"
	cat "full.bin" "zeroes.bin" > "$(TARGET).img"

	@echo ====================================================================
	@echo KERNEL REQUIERS $$(( ($(shell wc -c < boot.bin) + $(shell wc -c < kernel.bin)) / 512 + 1)) SECTORS
	@echo MAKE SURE YOUR BOOTLOADER LOADS THIS NUMBER OF SECTORS OR MORE
	@echo ====================================================================

	rm -f $(COBJS) $(AOBJS) boot.bin kernel.bin zeroes.bin full.bin

boot.bin: $(BSRC)
	$(AC) -f bin -i src/boot $(BSRC) -o $@

kernel.bin: $(COBJS) $(AOBJS)
	$(LD) $(LDFLAGS) $(AOBJS) $(COBJS) -lgcc -Tlinker/kernel.ld --oformat binary -o $@

%.o: %.cpp
	$(CXXC) $(CXXFLAGS) -c $< -o $@

%.o: %.asm
	$(AC) $(AFLAGS) $< -o $@

%.o: %.S
	$(CXXC) $(CXXFLAGS) -c $< -o $@

kernel_entry.o:

zeroes.bin: $(ZSRC)
	$(AC) $(AFLAGS) $< -o $@

clear:
	rm -f $(COBJS) $(AOBJS) boot.bin kernel.bin zeroes.bin

debug:
	@echo C kernel files $(CSRCS)
	@echo asm kernel files $(ASRCS)
	@echo boot source file $(BSRC)
	@echo zeroes source file $(ZSRC)

run: $(TARGET)
	qemu-system-i386 $(TARGET).img