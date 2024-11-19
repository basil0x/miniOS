#define ASM_FILE        1
#include "multiboot2.h"

/*  C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

/*  The size of our stack (16KB). */
#define STACK_SIZE                      0x4000

/*  The flags for the Multiboot header. */
#ifdef __ELF__
# define AOUT_KLUDGE 0
#else
# define AOUT_KLUDGE MULTIBOOT_AOUT_KLUDGE
#endif
/*
    .section .multiboot
__multiboot_header_start:

    .align 4
    .long 0xe85250d6                # MULTIBOOT2_HEADER_MAGIC
    .long 0                         # MULTIBOOT2_ARCHITECTURE_I386
    .long __multiboot_header_end - __multiboot_header_start  # MULTIBOOT2_HEADER_LENGTH
    .long -(0xe85250d6 + 0 + (__multiboot_header_end - __multiboot_header_start))  # MULTIBOOT2_CHECKSUM

    # Header Tags

    framebuffer_tag_start:  
        .short 5
        .short 1
        .long framebuffer_tag_end - framebuffer_tag_start
        .long 1366
        .long 768
        .long 32
	framebuffer_tag_end:

	# End tag
    .word 0                         # MULTIBOOT2_HEADER_TAG_END
    .word 0                         # padding
    .word 8                         # tag length (size)

__multiboot_header_end:

*/

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	jmp     multiboot_entry

        /*  Align 64 bits boundary. */
        .align  8
        
        /*  Multiboot header. */
multiboot_header:
        /*  magic */
        .long   0xe85250d6
        /*  ISA: i386 */
        .long   0
        /*  Header length. */
        .long   multiboot_header_end - multiboot_header
        /*  checksum */
        .long   -(0xe85250d6 + 0 + (multiboot_header_end - multiboot_header))
#ifndef __ELF__
address_tag_start:      
        .short MULTIBOOT_HEADER_TAG_ADDRESS
        .short MULTIBOOT_HEADER_TAG_OPTIONAL
        .long address_tag_end - address_tag_start
        /*  header_addr */
        .long   multiboot_header
        /*  load_addr */
        .long   _start
        /*  load_end_addr */
        .long   _edata
        /*  bss_end_addr */
        .long   _end
address_tag_end:
.align 8
entry_address_tag_start:        
        .short MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
        .short MULTIBOOT_HEADER_TAG_OPTIONAL
        .long entry_address_tag_end - entry_address_tag_start
        /*  entry_addr */
        .long multiboot_entry
entry_address_tag_end:
#endif /*  __ELF__ */
#ifndef FALLBACK_VGA
.align 8
framebuffer_tag_start:  
        .short MULTIBOOT_HEADER_TAG_FRAMEBUFFER
        .short MULTIBOOT_HEADER_TAG_OPTIONAL
        .long framebuffer_tag_end - framebuffer_tag_start
        .long 1366
        .long 768
        .long 32
framebuffer_tag_end:
#endif
.align 8
        .short MULTIBOOT_HEADER_TAG_END
        .short 0
        .long 8
multiboot_header_end:
multiboot_entry:
        /*  Initialize the stack pointer. */
        
		movl $stack_top, %esp


        /*  Reset EFLAGS. */
        pushl   $0
        popf

        /*  Push the pointer to the Multiboot information structure. */
        pushl   %ebx
        /*  Push the magic value. */
        pushl   %eax

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
