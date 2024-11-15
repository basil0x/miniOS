#pragma once
#include <stdint.h>

typedef struct{
    uint32_t ds;
    uint32_t edi,esi,ebp,kern_esp,ebx,edx,ecx,eax;
    uint32_t interrupt,error;
    uint32_t eip,cs,eflags,esp,ss;
} __attribute__((packed)) Registers;

void __attribute__((cdecl)) ISR_Handler(Registers);

void ISR_Init(void);