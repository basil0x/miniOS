#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>

void kernel_main(void) {
	terminal_initialize();
	init_HAL();
	printf(" log: Kernel loaded!\n");
}
