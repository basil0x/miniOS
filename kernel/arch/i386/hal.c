#include <stdio.h>
#include <kernel/hal.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <io/keyboard.h>
#include <util/common.h>


void irq1_handler() {

    outb(PIC1_COMMAND, PIC_EOI); /* Acknowledge the interrupt on the master PIC */
    unsigned char scan_code = inb(0x60);

    /* Process the keyboard interrupt */
    kb_scancode = scan_code;

    //printf("stat %x\n",kb_stat);

    //if(IS_PRESSED) printf("pressed");
    //if(IS_RELEASED) printf("released");

    /* JUST DEMO */
    /* Should be replaced with a switch */
    if(IS_PRESSED && IS_SUPER)  kb_stat^= 0x01;
    if(IS_PRESSED && IS_LCTRL)  kb_stat^= 0x02;
    if(IS_PRESSED && IS_RCTRL)  kb_stat^= 0x04;
    if(IS_PRESSED && IS_LSHIFT) kb_stat^= 0x08;
    if(IS_PRESSED && IS_RSHIFT) kb_stat^= 0x10;
    if(IS_PRESSED && IS_LALT)   kb_stat^= 0x20;
    if(IS_PRESSED && IS_RALT)   kb_stat^= 0x40;
    if(IS_RELEASED && IS_CAPS)  kb_stat^= 0x80;

    /* JUST DEMO */
    if(kbdmix[scan_code] && IS_PRESSED)
    {
        if((!STAT_CAPS)&&(!STAT_LSHIFT))
        printf("%c",kbdmix[scan_code]);
        else printf("%c",kbdse_shift[scan_code]);
        
    }

    __asm("sti");
    return;
}

/* PIC remapping goes on before IDT setup to avoid Double Fault */
void init_HAL()
{
    printf("Opening Hardware Abstraction Layer...\n");
    init_gdt();
    PIC_remap(0x20, 0x28);
    kb_init();
    init_idt();
    idt_SetGate(33, irq1_handler, 0x08, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    idt_EnableGate(33);
    //set_irq_handler(33, irq1_handler); /* Depricated */
    IRQ_set_mask(0);
    //mask the system clock;
    IRQ_clear_mask(1);
    
}