.globl _start
_start:
# Clear BSS
	ldr	r4, =__bss_start
	ldr	r5, =__bss_end
	
	cmp	r4, r5
	beq boot

	mov	r6, #0x0

loop:
	str	r6, [r4]
	add	r4, r4, #4
	cmp	r4, r5
	bne	loop

boot:

# Jump to entrypoint
	bl  bl1_entry
	b .