#include <stdint.h>
#include <multiboot.h>
#include <block.h>
#include <drivers/block/ramdisk.h>

void * ramdisk1_addr; /*TODO FIXME this is a horrible ugly way of doing it*/

uint8_t ramdisk_read(unsigned long location)
{
	uint8_t * r = (ramdisk1_addr + location);
	return (uint8_t)(*r);
}

void ramdisk_write(unsigned long location,uint8_t value)
{
	uint8_t * r = (ramdisk1_addr + location);
	(*r) = value;
}

struct Block_Device init_ramdisk(void * mp)
{
	struct Multiboot_Module * mm = mp;
	struct Block_Device bd;
	ramdisk1_addr = (void *) mm->mod_start;
	bd.size = mm->mod_start - mm->mod_end;
	bd._read = ramdisk_read;
	bd._write = ramdisk_write;
	return bd;
}
