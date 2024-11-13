#include <util/binary.h>
#include <kernel/idt.h>
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

void init_idt()
{
    idt_load(&idtd);
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