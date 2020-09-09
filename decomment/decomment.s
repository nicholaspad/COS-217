	.cpu generic+fp+simd
	.file	"decomment.c"
	.text
	.align	2
	.global	handleNormal
	.type	handleNormal, %function
handleNormal:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	ldr	w0, [x29,28]
	cmp	w0, 39
	beq	.L3
	cmp	w0, 39
	bgt	.L4
	cmp	w0, 34
	beq	.L5
	b	.L2
.L4:
	cmp	w0, 47
	beq	.L6
	cmp	w0, 92
	beq	.L7
	b	.L2
.L6:
	mov	w0, 2
	str	w0, [x29,44]
	b	.L8
.L7:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 1
	str	w0, [x29,44]
	b	.L8
.L5:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 5
	str	w0, [x29,44]
	b	.L8
.L3:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 7
	str	w0, [x29,44]
	b	.L8
.L2:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
.L8:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE0:
	.size	handleNormal, .-handleNormal
	.align	2
	.global	handleNormalEsc
	.type	handleNormalEsc, %function
handleNormalEsc:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	wzr, [x29,44]
	ldr	w0, [x29,28]
	bl	putchar
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE1:
	.size	handleNormalEsc, .-handleNormalEsc
	.align	2
	.global	handleHalfOpenComment
	.type	handleHalfOpenComment, %function
handleHalfOpenComment:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	str	w1, [x29,24]
	str	x2, [x29,16]
	ldr	w0, [x29,28]
	cmp	w0, 42
	beq	.L14
	cmp	w0, 47
	bne	.L18
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 2
	str	w0, [x29,44]
	b	.L16
.L14:
	mov	w0, 32
	bl	putchar
	mov	w0, 3
	str	w0, [x29,44]
	ldr	x0, [x29,16]
	ldr	w1, [x29,24]
	str	w1, [x0]
	b	.L16
.L18:
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
.L16:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE2:
	.size	handleHalfOpenComment, .-handleHalfOpenComment
	.align	2
	.global	handleOpenComment
	.type	handleOpenComment, %function
handleOpenComment:
.LFB3:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	ldr	w0, [x29,28]
	cmp	w0, 42
	bne	.L25
	mov	w0, 4
	str	w0, [x29,44]
	b	.L22
.L25:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L23
	ldr	w0, [x29,28]
	bl	putchar
.L23:
	mov	w0, 3
	str	w0, [x29,44]
.L22:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE3:
	.size	handleOpenComment, .-handleOpenComment
	.align	2
	.global	handleHalfClosedComment
	.type	handleHalfClosedComment, %function
handleHalfClosedComment:
.LFB4:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	ldr	w0, [x29,28]
	cmp	w0, 42
	beq	.L28
	cmp	w0, 47
	beq	.L29
	b	.L33
.L28:
	mov	w0, 4
	str	w0, [x29,44]
	b	.L30
.L29:
	str	wzr, [x29,44]
	b	.L30
.L33:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L31
	ldr	w0, [x29,28]
	bl	putchar
.L31:
	mov	w0, 3
	str	w0, [x29,44]
.L30:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE4:
	.size	handleHalfClosedComment, .-handleHalfClosedComment
	.align	2
	.global	handleDoubleQuoteOpen
	.type	handleDoubleQuoteOpen, %function
handleDoubleQuoteOpen:
.LFB5:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	ldr	w0, [x29,28]
	cmp	w0, 34
	beq	.L36
	cmp	w0, 92
	bne	.L40
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	b	.L38
.L36:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L38
.L40:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 5
	str	w0, [x29,44]
.L38:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE5:
	.size	handleDoubleQuoteOpen, .-handleDoubleQuoteOpen
	.align	2
	.global	handleDoubleQuoteEsc
	.type	handleDoubleQuoteEsc, %function
handleDoubleQuoteEsc:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	mov	w0, 5
	str	w0, [x29,44]
	ldr	w0, [x29,28]
	bl	putchar
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE6:
	.size	handleDoubleQuoteEsc, .-handleDoubleQuoteEsc
	.align	2
	.global	handleSingleQuoteOpen
	.type	handleSingleQuoteOpen, %function
handleSingleQuoteOpen:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	ldr	w0, [x29,28]
	cmp	w0, 39
	beq	.L45
	cmp	w0, 92
	bne	.L49
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 8
	str	w0, [x29,44]
	b	.L47
.L45:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L47
.L49:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 7
	str	w0, [x29,44]
.L47:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE7:
	.size	handleSingleQuoteOpen, .-handleSingleQuoteOpen
	.align	2
	.global	handleSingleQuoteEsc
	.type	handleSingleQuoteEsc, %function
handleSingleQuoteEsc:
.LFB8:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	mov	w0, 7
	str	w0, [x29,44]
	ldr	w0, [x29,28]
	bl	putchar
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE8:
	.size	handleSingleQuoteEsc, .-handleSingleQuoteEsc
	.section	.rodata
	.align	3
.LC0:
	.string	"Error: line %d: unterminated comment\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB9:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	mov	w0, 1
	str	w0, [x29,28]
	str	wzr, [x29,24]
	b	.L53
.L65:
	ldr	w0, [x29,20]
	cmp	w0, 10
	bne	.L54
	ldr	w0, [x29,28]
	add	w0, w0, 1
	str	w0, [x29,28]
.L54:
	ldr	w0, [x29,24]
	cmp	w0, 8
	bhi	.L53
	adrp	x1, .L56
	add	x1, x1, :lo12:.L56
	ldr	w2, [x1,w0,uxtw #2]
	adr	x3, .Lrtx56
	add	x2, x3, w2, sxtw #2
	br	x2
.Lrtx56:
	.section	.rodata
	.align	0
	.align	2
.L56:
	.word	(.L55 - .Lrtx56) / 4
	.word	(.L57 - .Lrtx56) / 4
	.word	(.L58 - .Lrtx56) / 4
	.word	(.L59 - .Lrtx56) / 4
	.word	(.L60 - .Lrtx56) / 4
	.word	(.L61 - .Lrtx56) / 4
	.word	(.L62 - .Lrtx56) / 4
	.word	(.L63 - .Lrtx56) / 4
	.word	(.L64 - .Lrtx56) / 4
	.text
.L55:
	ldr	w0, [x29,20]
	bl	handleNormal
	str	w0, [x29,24]
	b	.L53
.L57:
	ldr	w0, [x29,20]
	bl	handleNormalEsc
	str	w0, [x29,24]
	b	.L53
.L58:
	add	x2, x29, 16
	ldr	w0, [x29,20]
	ldr	w1, [x29,28]
	bl	handleHalfOpenComment
	str	w0, [x29,24]
	b	.L53
.L59:
	ldr	w0, [x29,20]
	bl	handleOpenComment
	str	w0, [x29,24]
	b	.L53
.L60:
	ldr	w0, [x29,20]
	bl	handleHalfClosedComment
	str	w0, [x29,24]
	b	.L53
.L61:
	ldr	w0, [x29,20]
	bl	handleDoubleQuoteOpen
	str	w0, [x29,24]
	b	.L53
.L62:
	ldr	w0, [x29,20]
	bl	handleDoubleQuoteEsc
	str	w0, [x29,24]
	b	.L53
.L63:
	ldr	w0, [x29,20]
	bl	handleSingleQuoteOpen
	str	w0, [x29,24]
	b	.L53
.L64:
	ldr	w0, [x29,20]
	bl	handleSingleQuoteEsc
	str	w0, [x29,24]
	nop
.L53:
	bl	getchar
	str	w0, [x29,20]
	ldr	w0, [x29,20]
	cmn	w0, #1
	bne	.L65
	ldr	w0, [x29,24]
	cmp	w0, 3
	beq	.L66
	ldr	w0, [x29,24]
	cmp	w0, 4
	bne	.L67
.L66:
	adrp	x0, stderr
	add	x0, x0, :lo12:stderr
	ldr	x0, [x0]
	ldr	w2, [x29,16]
	adrp	x1, .LC0
	add	x1, x1, :lo12:.LC0
	bl	fprintf
	mov	w0, 1
	b	.L69
.L67:
	mov	w0, 0
.L69:
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",%progbits
