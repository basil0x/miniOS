#pragma once
#include <stdint.h>

typedef struct {
	uint16_t    BaseLow;      		// The lower 16 bits of the ISR's address
	uint16_t    SegmentSelector;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     Reserved;     		// Set to zero
	uint8_t     Flags;      		// Type and attributes; see the IDT page
	uint16_t    BaseHigh;     		// The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t		Limit;
	uint32_t		Base; 
} __attribute__((packed)) idtd_t;   // Idt descriptor type

 __attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance

static idtd_t idtd = { sizeof(idt)-1,  idt}; // Create a descriptor 

typedef enum {
	IDT_FLAG_GATE_TASK			=0x5,
	IDT_FLAG_GATE_16BIT_INT		=0x6,
	IDT_FLAG_GATE_16BIT_TRAP	=0x7,
	IDT_FLAG_GATE_32BIT_INT		=0xE,
	IDT_FLAG_GATE_32BIT_TRAP	=0xF,

	IDT_FLAG_RING0				= (0 << 5),
	IDT_FLAG_RING1				= (1 << 5),
	IDT_FLAG_RING2				= (2 << 5),
	IDT_FLAG_RING3				= (3 << 5),

	IDT_FLAG_PRESENT			=0x80,
};

void idt_SetGate(int, void*, uint16_t, uint8_t);

void idt_EnableGate(int);
void idt_DisableGate(int);

extern void idt_load(idtd_t*);

void init_idt(void);