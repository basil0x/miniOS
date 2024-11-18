#pragma once
#include <stdint.h>

// Magic fix. Needs to be changed.
typedef struct{
    uint32_t esp_junk;
    uint32_t ds;
    uint32_t edi,esi,ebp,kern_esp,ebx,edx,ecx,eax;
    uint32_t interrupt,error;
    uint32_t eip,cs,eflags,esp,ss;
} __attribute__((packed)) Registers;

static char* exceptions [31] = {
"Division Error",
"Debug",
"Non-maskable Interrupt",
"Breakpoint",
"Overflow", 	 
"Bound Range Exceeded",
"Invalid Opcode", 
"Device Not Available", 
"Double Fault",
"Coprocessor Segment Overrun",
"Invalid TSS",
"Segment Not Present",
"Stack-Segment Fault",
"General Protection Fault",
"Page Fault",
"Reserved",
"x87 Floating-Point Exception",
"Alignment Check",
"Machine Check",
"SIMD Floating-Point Exception",
"Virtualization Exception",
"Control Protection Exception",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Hypervisor Injection Exception",
"VMM_Communication_Exception",
"Security_Exception",
"Reserved",
};

void __attribute__((cdecl)) ISR_Handler(Registers);

void ISR_Init(void);