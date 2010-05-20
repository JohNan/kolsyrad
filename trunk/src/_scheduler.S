	.text

	.globl	readip
	.globl	jumpip

readip:
	add	$v0,$sp,$0
	jr	$ra

jumpip:
	jr	$a0
