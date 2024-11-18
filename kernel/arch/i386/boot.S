    .section .multiboot
__multiboot_header_start:

    .align 4
    .long 0xe85250d6                # MULTIBOOT2_HEADER_MAGIC
    .long 0                         # MULTIBOOT2_ARCHITECTURE_I386
    .long __multiboot_header_end - __multiboot_header_start  # MULTIBOOT2_HEADER_LENGTH
    .long -(0xe85250d6 + 0 + (__multiboot_header_end - __multiboot_header_start))  # MULTIBOOT2_CHECKSUM

    # Header Tags

	# End tag
    .word 0                         # MULTIBOOT2_HEADER_TAG_END
    .word 0                         # padding
    .word 8                         # tag length (size)

__multiboot_header_end:


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
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
