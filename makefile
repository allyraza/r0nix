CFLAGS=-ffreestanding -fbuiltin -Wall -Wextra -g
LIBS=-Iinclude -nostdlib  -lgcc 
CC=i686-elf-gcc
AS=i686-elf-as

MODULES=drivers/*.c block/*.c lib/*.c init/*.c arch/*.c fs/*.c fs/ext2/*.c kernel/*.c

#TODO this should place the .o files someplace else
all:
	$(AS) init/boot.s -o boot.o
	$(AS) arch/reload_segments.s -o reload_segments.o
	$(AS) arch/interrupt_handler.s -o interrupt_handler.o
	$(CC) -c $(MODULES) $(CFLAGS) $(LIBS)
	$(CC) -T misc/linker.ld -o r0nix $(CFLAGS) *.o $(LIBS)
clean:
	rm *.o
	rm r0nix
run:
	qemu-system-i386 -monitor stdio -kernel r0nix -no-reboot -initrd misc/initrd 
debug:
	qemu-system-i386 -s -S -kernel r0nix -initrd misc/initrd &
	gdb -s r0nix -ex "target remote localhost:1234"
	pkill qemu
