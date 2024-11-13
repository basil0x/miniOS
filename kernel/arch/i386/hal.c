#include <stdio.h>
#include <kernel/hal.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void init_HAL()
{
    printf("Opening Hardware Abstraction Layer...\n");
    init_gdt();
    init_idt();
}