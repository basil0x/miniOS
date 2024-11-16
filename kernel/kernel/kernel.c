#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>

void crash(void);

void kernel_main(void) {
	terminal_initialize();
	init_HAL();
	__asm("sti");
	__asm("int $1");
	//crash();
	printf(" log: Kernel loaded!\n");
	printf("\nshell: ");
}
