#include <util/binary.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <stdint.h>
#include <stdio.h>

void idt_SetGate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
{
	idt[interrupt].BaseLow = ((uint32_t)base & 0xFFFF);
	idt[interrupt].SegmentSelector = segmentDescriptor;
	idt[interrupt].Reserved = 0;
	idt[interrupt].Flags = flags;
	idt[interrupt].BaseHigh = (((uint32_t)base >> 16) & 0xFFFF);

}

void get_idt(uint16_t* limit, uint32_t* base) {
    __asm__ (
        "sidt %0"        // SGDT stores the IDTR in memory location pointed to by %0
        : "=m" (*limit)   // Output operand for the GDT limit
        : "m" (*base)     // Output operand for the GDT base
    );
}

void init_idt()
{
	uint16_t idt_limit;
    uint32_t idt_base;

	get_idt(&idt_limit, &idt_base);
	scprintf(" test: GRUB's IDT Limit and Base: %x , %x\n",idt_limit,idt_base);
	ISR_Init();

    idt_load(&idtd);
	get_idt(&idt_limit, &idt_base);
	scprintf(" test: New IDT Limit and Base: %x , %x \n",idt_limit,idt_base);
	scprintf(" test: Struct IDT Limit and Base: %x , %x\n",idtd.Limit,idtd.Base);
    printf(" log: Finished initializing the IDT. \n");
	
}

void idt_EnableGate(int interrupt)
{
    FLAG_SET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void idt_DisableGate(int interrupt)
{
    FLAG_UNSET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}