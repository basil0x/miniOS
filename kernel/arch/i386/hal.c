#include <stdio.h>
#include <kernel/hal.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <io/keyboard.h>
#include <io/kcoms.h>
#include <util/common.h>


void irq1_handler() {

    outb(PIC1_COMMAND, PIC_EOI); /* Acknowledge the interrupt on the master PIC */
    unsigned char scan_code = inb(0x60);

    /* Process the keyboard interrupt */
    kb_scancode = scan_code;

    //printf("stat %x\n",kb_stat);

    //if(IS_PRESSED) printf("pressed");
    //if(IS_RELEASED) printf("released");

    kb_up_flags();

    if(IS_PRESSED && IS_ENTER) process_kcom();

    else 
    {
    /* JUST DEMO */
    if(kbdmix[scan_code] && IS_PRESSED)
    {
        if((!STAT_CAPS)&&(!STAT_LSHIFT))
        {printf("%c",kbdmix[scan_code]);kcom_buff[kcom_indx++]=kbdmix[scan_code];}
        else printf("%c",kbdse_shift[scan_code]);
        
    } 
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