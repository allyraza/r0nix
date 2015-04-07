#include <syscalls.h>
#include <desc.h>
#include <kprint.h>
#include <cpu.h>
#include <panic.h>
#include <fs.h>
#include <fork.h>

void system_call(struct cpu_state *s)
{
	switch(s->eax){
		case SYSCALL_OPEN:
			s->eax = open((void *)s->ebx);
			break;
		case SYSCALL_CLOSE:
			s->eax = close(s->ebx);
			break;
		case SYSCALL_READ:
			s->eax = read(s->ebx,(void *)s->ecx,s->edi);
			break;
		case SYSCALL_WRITE:
			s->eax = write(s->ebx,(void *)s->ecx,s->edi);
			break;
		case SYSCALL_FORK:
			s->eax = fork();
			break;
		case SYSCALL_EXEC:
			panic("nyi exec system called");
			break;
		case SYSCALL_REBOOT:
			/*hack, causes a triple fault, which causes reboot*/
			load_idt(0);
			asm("int3");
			break;
	}
}
