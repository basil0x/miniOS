#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/hal.h>

void crash(void);

void kernel_main(void) {
	terminal_initialize();
	init_HAL();
	__asm("sti");

	//crash();
	printf(" log: Kernel loaded!\n");
	__asm("int $1");
	printf("---[VGA FALLBACK MODE]---\n");
	scprintf("\n[lain]> ",0);
	__asm("sti");
	for(;;) {
    //__asm("sti");
 }
}
