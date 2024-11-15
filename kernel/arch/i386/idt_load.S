.intel_syntax noprefix
.section .text
	.global idt_load,crash

idt_load:
    enter 0,0
	# Copy the first argument in esp + 4 into eax
	mov eax, [esp + 8] # EAX is a gdtd_t
	
    cli # Clear the interrupt flag just incase

	# Load the new IDT by dereferencing the pointer contained
	lidt [eax]

	# Set the interrupt flag
	sti

	leave
	ret

crash:
	mov eax,0
	div	eax
	ret