# -------------------------------------------------------------------------
#  asm.S
# -------------------------------------------------------------------------

#include <regdef.h>
	
# -------------------------------------------------------------------------
# Data segment
# -------------------------------------------------------------------------

#define	KERNEL_BOOT_STACK_SIZE		0x4000

		.data

STR:
	.asciiz "Aloha!"
	
kernel_boot_stack_low_limit:
	# MUST ALIGN THE STACK on a 2^2 = 4 byte word bondary!	
	.align 2
        .space  KERNEL_BOOT_STACK_SIZE
kernel_boot_stack_high_limit:


			
# -------------------------------------------------------------------------
# Code segment
# -------------------------------------------------------------------------

	.text
	.set nomove

	.globl	_start

			

		
# -------------------------------------------------------------------------
# Startup code
	#    This is where the system boots from
#     1. Load the stackpointer 'sp' with top of initial stack.
# -------------------------------------------------------------------------
_start:

	la	sp, kernel_boot_stack_high_limit

	j	init
	
	

