#include <kernel/gdt.h>
#include <stdint.h>
#include <stdio.h>

struct gdt_ptr GDTStruct;

__attribute__((aligned(0x1000))) struct GDT defaultGDT = {
	{0, 0, 0, 0x00, 0x00, 0}, // null segment
	{0, 0, 0, 0x9a, 0xcf, 0}, // kernel code
	{0, 0, 0, 0x92, 0xcf, 0}, // kernel data
};


void get_gdt(uint16_t* limit, uint32_t* base) {
    __asm__ (
        "sgdt %0"        // SGDT stores the GDTR in memory location pointed to by %0
        : "=m" (*limit)   // Output operand for the GDT limit
        : "m" (*base)     // Output operand for the GDT base
    );
}


void init_gdt(){
	uint16_t gdt_limit;
    uint32_t gdt_base;

	get_gdt(&gdt_limit, &gdt_base);
	scprintf(" test: GRUB's GDT Limit and Base: %x , %x\n",gdt_limit,gdt_base);

	// GDTStruct.Limit = (sizeof(struct GDT)) - 1;
	// GDTStruct.Base = (uint32_t) &defaultGDT;
	GDTStruct.Limit = (sizeof(struct GDT)) - 1;
	GDTStruct.Base = (uint32_t) &defaultGDT;
	gdt_load(&GDTStruct);

	printf(" log: Finished initializing the GDT. \n");
	
	get_gdt(&gdt_limit, &gdt_base);
	scprintf(" test: New GDT Limit and Base: %x , %x\n",gdt_limit,gdt_base);
	scprintf(" test: Struct GDT Limit and Base: %x , %x\n",GDTStruct.Limit,GDTStruct.Base);
}