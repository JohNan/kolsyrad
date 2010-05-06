
	.text

_readip:
	mov	-4(sp),ip
	ret

_jumpip:
	j (sp)
