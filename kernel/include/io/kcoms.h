#pragma once

#include <stdio.h>
#include <util/common.h>
#include <kernel/tty.h>
#define KCOM_LIMIT 20

char kcom_buff[KCOM_LIMIT];
char kcom_indx = 0;
void print_cpu_info() {
    uint32_t eax, edx;

    // Get the vendor string (CPUID with code 0)
    cpuid(0, &eax, &edx);  // `eax` will contain the maximum function number, `edx` will contain part of the vendor string

    // Extract the 12-byte vendor string from eax and edx
    char vendor[13];
    vendor[0] = (eax & 0xFF);
    vendor[1] = (eax >> 8) & 0xFF;
    vendor[2] = (eax >> 16) & 0xFF;
    vendor[3] = (eax >> 24) & 0xFF;
    vendor[4] = (edx & 0xFF);
    vendor[5] = (edx >> 8) & 0xFF;
    vendor[6] = (edx >> 16) & 0xFF;
    vendor[7] = (edx >> 24) & 0xFF;
    vendor[8] = '\0';  // Null-terminate the string

    // Print the CPU vendor string
    printf("\nCPU Vendor: %x\n", vendor);

    // Get the processor signature (CPUID with code 1)
    cpuid(1, &eax, &edx);  // `eax` will contain the processor signature, `edx` contains flags

    // Extract family, model, and stepping from the processor signature
    uint32_t family = (eax >> 8) & 0x0F;
    uint32_t model = (eax >> 4) & 0x0F;
    uint32_t stepping = eax & 0x0F;

    // Print the processor details
    printf("Processor: Family %x, Model %x, Stepping %x\n", family, model, stepping);
}
void prompt(void)
{
    scprintf("\n[lain]> ",0);
}

int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

/* Sould add hashed switch */
void run_cmd(void)
{
    if(strcmp(kcom_buff,"test\0") == 0) printf("\nLet's All Love Lain!\n");
    if(strcmp(kcom_buff,"clear\0") == 0) terminal_initialize();
    if(strcmp(kcom_buff,"lscpu\0") == 0) print_cpu_info();
    if(strcmp(kcom_buff,"lsp\0") == 0) printf("\nPROCESS NAME | PID | START TIME | THREADS\nKERNEL       | 000 | 0000000000 | 0000000");
    kcom_buff[0] = '\0';
}


/* Commands should be hashed this is just testing */
void process_kcom(void)
{
    if(kcom_indx)
    { 
    kcom_buff[kcom_indx] = '\0';
    kcom_indx = 0;
    run_cmd();
    prompt();
    }
}

