	.cpu generic+fp+simd
	.file	"strp.c"
	.section	.rodata
	.align	3
.LC0:
	.string	"pSrc != ((void *)0)"
	.align	3
.LC1:
	.string	"strp.c"
	.text
	.align	2
	.global	Str_getLength
	.type	Str_getLength, %function
Str_getLength:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	x0, [x29,24]
	ldr	x0, [x29,24]
	cmp	x0, xzr
	bne	.L2
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2049
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2049
	mov	w2, 10
	bl	__assert_fail
.L2:
	ldr	x0, [x29,24]
	str	x0, [x29,40]
	b	.L3
.L4:
	ldr	x0, [x29,40]
	add	x0, x0, 1
	str	x0, [x29,40]
.L3:
	ldr	x0, [x29,40]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L4
	ldr	x1, [x29,40]
	ldr	x0, [x29,24]
	sub	x0, x1, x0
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE0:
	.size	Str_getLength, .-Str_getLength
	.section	.rodata
	.align	3
.LC2:
	.string	"pDest != ((void *)0)"
	.text
	.align	2
	.global	Str_copy
	.type	Str_copy, %function
Str_copy:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	x0, [x29,24]
	str	x1, [x29,16]
	ldr	x0, [x29,16]
	cmp	x0, xzr
	bne	.L7
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2059
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2059
	mov	w2, 23
	bl	__assert_fail
.L7:
	ldr	x0, [x29,24]
	cmp	x0, xzr
	bne	.L8
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2059
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2059
	mov	w2, 24
	bl	__assert_fail
.L8:
	ldr	x0, [x29,16]
	str	x0, [x29,40]
	ldr	x0, [x29,24]
	str	x0, [x29,32]
	b	.L9
.L10:
	ldr	x0, [x29,40]
	ldrb	w1, [x0]
	ldr	x0, [x29,32]
	strb	w1, [x0]
	ldr	x0, [x29,40]
	add	x0, x0, 1
	str	x0, [x29,40]
	ldr	x0, [x29,32]
	add	x0, x0, 1
	str	x0, [x29,32]
.L9:
	ldr	x0, [x29,40]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L10
	ldr	x0, [x29,32]
	strb	wzr, [x0]
	ldr	x0, [x29,24]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE1:
	.size	Str_copy, .-Str_copy
	.align	2
	.global	Str_concat
	.type	Str_concat, %function
Str_concat:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	x0, [x29,24]
	str	x1, [x29,16]
	ldr	x0, [x29,16]
	cmp	x0, xzr
	bne	.L13
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2069
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2069
	mov	w2, 42
	bl	__assert_fail
.L13:
	ldr	x0, [x29,24]
	cmp	x0, xzr
	bne	.L14
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2069
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2069
	mov	w2, 43
	bl	__assert_fail
.L14:
	ldr	x0, [x29,16]
	str	x0, [x29,40]
	ldr	x0, [x29,24]
	bl	Str_getLength
	ldr	x1, [x29,24]
	add	x0, x1, x0
	str	x0, [x29,32]
	b	.L15
.L16:
	ldr	x0, [x29,40]
	ldrb	w1, [x0]
	ldr	x0, [x29,32]
	strb	w1, [x0]
	ldr	x0, [x29,40]
	add	x0, x0, 1
	str	x0, [x29,40]
	ldr	x0, [x29,32]
	add	x0, x0, 1
	str	x0, [x29,32]
.L15:
	ldr	x0, [x29,40]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L16
	ldr	x0, [x29,32]
	strb	wzr, [x0]
	ldr	x0, [x29,24]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE2:
	.size	Str_concat, .-Str_concat
	.section	.rodata
	.align	3
.LC3:
	.string	"pStr1 != ((void *)0)"
	.align	3
.LC4:
	.string	"pStr2 != ((void *)0)"
	.text
	.align	2
	.global	Str_compare
	.type	Str_compare, %function
Str_compare:
.LFB3:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	x0, [x29,24]
	str	x1, [x29,16]
	ldr	x0, [x29,24]
	cmp	x0, xzr
	bne	.L19
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2079
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2079
	mov	w2, 61
	bl	__assert_fail
.L19:
	ldr	x0, [x29,16]
	cmp	x0, xzr
	bne	.L20
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2079
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2079
	mov	w2, 62
	bl	__assert_fail
.L20:
	ldr	x0, [x29,24]
	str	x0, [x29,40]
	ldr	x0, [x29,16]
	str	x0, [x29,32]
	b	.L21
.L24:
	ldr	x0, [x29,40]
	ldrb	w1, [x0]
	ldr	x0, [x29,32]
	ldrb	w0, [x0]
	cmp	w1, w0
	beq	.L22
	b	.L23
.L22:
	ldr	x0, [x29,40]
	add	x0, x0, 1
	str	x0, [x29,40]
	ldr	x0, [x29,32]
	add	x0, x0, 1
	str	x0, [x29,32]
.L21:
	ldr	x0, [x29,40]
	ldrb	w0, [x0]
	cmp	w0, wzr
	beq	.L23
	ldr	x0, [x29,32]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L24
.L23:
	ldr	x0, [x29,40]
	ldrb	w0, [x0]
	mov	w1, w0
	ldr	x0, [x29,32]
	ldrb	w0, [x0]
	sub	w0, w1, w0
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE3:
	.size	Str_compare, .-Str_compare
	.section	.rodata
	.align	3
.LC5:
	.string	"pHaystack != ((void *)0)"
	.align	3
.LC6:
	.string	"pNeedle != ((void *)0)"
	.text
	.align	2
	.global	Str_search
	.type	Str_search, %function
Str_search:
.LFB4:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	x0, [x29,24]
	str	x1, [x29,16]
	ldr	x0, [x29,24]
	cmp	x0, xzr
	bne	.L27
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2091
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2091
	mov	w2, 97
	bl	__assert_fail
.L27:
	ldr	x0, [x29,16]
	cmp	x0, xzr
	bne	.L28
	adrp	x0, .LC6
	add	x0, x0, :lo12:.LC6
	adrp	x1, .LC1
	add	x1, x1, :lo12:.LC1
	adrp	x2, __PRETTY_FUNCTION__.2091
	add	x3, x2, :lo12:__PRETTY_FUNCTION__.2091
	mov	w2, 98
	bl	__assert_fail
.L28:
	ldr	x0, [x29,16]
	bl	Str_getLength
	str	x0, [x29,32]
	ldr	x0, [x29,24]
	str	x0, [x29,56]
	ldr	x0, [x29,16]
	str	x0, [x29,48]
	ldr	x0, [x29,16]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L29
	ldr	x0, [x29,24]
	b	.L30
.L29:
	b	.L31
.L37:
	ldr	x0, [x29,56]
	str	x0, [x29,40]
	ldr	x0, [x29,16]
	str	x0, [x29,48]
	b	.L32
.L36:
	ldr	x0, [x29,40]
	ldrb	w1, [x0]
	ldr	x0, [x29,48]
	ldrb	w0, [x0]
	cmp	w1, w0
	beq	.L33
	b	.L34
.L33:
	ldr	x1, [x29,48]
	ldr	x0, [x29,16]
	sub	x1, x1, x0
	ldr	x0, [x29,32]
	sub	x0, x0, #1
	cmp	x1, x0
	bne	.L35
	ldr	x0, [x29,56]
	b	.L30
.L35:
	ldr	x0, [x29,40]
	add	x0, x0, 1
	str	x0, [x29,40]
	ldr	x0, [x29,48]
	add	x0, x0, 1
	str	x0, [x29,48]
.L32:
	ldr	x0, [x29,48]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L36
.L34:
	ldr	x0, [x29,56]
	add	x0, x0, 1
	str	x0, [x29,56]
.L31:
	ldr	x0, [x29,56]
	ldrb	w0, [x0]
	cmp	w0, wzr
	bne	.L37
	mov	x0, 0
.L30:
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE4:
	.size	Str_search, .-Str_search
	.section	.rodata
	.align	3
	.type	__PRETTY_FUNCTION__.2049, %object
	.size	__PRETTY_FUNCTION__.2049, 14
__PRETTY_FUNCTION__.2049:
	.string	"Str_getLength"
	.align	3
	.type	__PRETTY_FUNCTION__.2059, %object
	.size	__PRETTY_FUNCTION__.2059, 9
__PRETTY_FUNCTION__.2059:
	.string	"Str_copy"
	.align	3
	.type	__PRETTY_FUNCTION__.2069, %object
	.size	__PRETTY_FUNCTION__.2069, 11
__PRETTY_FUNCTION__.2069:
	.string	"Str_concat"
	.align	3
	.type	__PRETTY_FUNCTION__.2079, %object
	.size	__PRETTY_FUNCTION__.2079, 12
__PRETTY_FUNCTION__.2079:
	.string	"Str_compare"
	.align	3
	.type	__PRETTY_FUNCTION__.2091, %object
	.size	__PRETTY_FUNCTION__.2091, 11
__PRETTY_FUNCTION__.2091:
	.string	"Str_search"
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",%progbits
