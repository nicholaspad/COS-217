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
	cmp	w0, 47
	beq	.L4
	cmp	w0, 34
	beq	.L5
	b	.L8
.L4:
	mov	w0, 1
	str	w0, [x29,44]
	b	.L6
.L5:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
	b	.L6
.L3:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	b	.L6
.L8:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
.L6:
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
	.global	handleHalfOpenComment
	.type	handleHalfOpenComment, %function
handleHalfOpenComment:
.LFB1:
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
	sub	w0, w0, #34
	cmp	w0, 13
	bhi	.L10
	adrp	x1, .L12
	add	x1, x1, :lo12:.L12
	ldr	w2, [x1,w0,uxtw #2]
	adr	x3, .Lrtx12
	add	x2, x3, w2, sxtw #2
	br	x2
.Lrtx12:
	.section	.rodata
	.align	0
	.align	2
.L12:
	.word	(.L11 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L13 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L14 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L10 - .Lrtx12) / 4
	.word	(.L15 - .Lrtx12) / 4
	.text
.L15:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 1
	str	w0, [x29,44]
	b	.L16
.L14:
	mov	w0, 32
	bl	putchar
	mov	w0, 2
	str	w0, [x29,44]
	ldr	x0, [x29,16]
	ldr	w1, [x29,24]
	str	w1, [x0]
	b	.L16
.L11:
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
	b	.L16
.L13:
	mov	w0, 47
	bl	putchar
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
	b	.L16
.L10:
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
.LFE1:
	.size	handleHalfOpenComment, .-handleHalfOpenComment
	.align	2
	.global	handleOpenComment
	.type	handleOpenComment, %function
handleOpenComment:
.LFB2:
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
	bne	.L24
	mov	w0, 3
	str	w0, [x29,44]
	b	.L21
.L24:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L22
	ldr	w0, [x29,28]
	bl	putchar
.L22:
	mov	w0, 2
	str	w0, [x29,44]
.L21:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE2:
	.size	handleOpenComment, .-handleOpenComment
	.align	2
	.global	handleHalfClosedComment
	.type	handleHalfClosedComment, %function
handleHalfClosedComment:
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
	beq	.L27
	cmp	w0, 47
	beq	.L28
	b	.L32
.L27:
	mov	w0, 3
	str	w0, [x29,44]
	b	.L29
.L28:
	str	wzr, [x29,44]
	b	.L29
.L32:
	ldr	w0, [x29,28]
	cmp	w0, 10
	bne	.L30
	ldr	w0, [x29,28]
	bl	putchar
.L30:
	mov	w0, 2
	str	w0, [x29,44]
.L29:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE3:
	.size	handleHalfClosedComment, .-handleHalfClosedComment
	.align	2
	.global	handleDoubleQuoteOpen
	.type	handleDoubleQuoteOpen, %function
handleDoubleQuoteOpen:
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
	cmp	w0, 34
	beq	.L35
	cmp	w0, 92
	bne	.L39
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 5
	str	w0, [x29,44]
	b	.L37
.L35:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L37
.L39:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 4
	str	w0, [x29,44]
.L37:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE4:
	.size	handleDoubleQuoteOpen, .-handleDoubleQuoteOpen
	.align	2
	.global	handleDoubleQuoteEsc
	.type	handleDoubleQuoteEsc, %function
handleDoubleQuoteEsc:
.LFB5:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	mov	w0, 4
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
.LFE5:
	.size	handleDoubleQuoteEsc, .-handleDoubleQuoteEsc
	.align	2
	.global	handleSingleQuoteOpen
	.type	handleSingleQuoteOpen, %function
handleSingleQuoteOpen:
.LFB6:
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
	beq	.L44
	cmp	w0, 92
	bne	.L48
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 7
	str	w0, [x29,44]
	b	.L46
.L44:
	ldr	w0, [x29,28]
	bl	putchar
	str	wzr, [x29,44]
	b	.L46
.L48:
	ldr	w0, [x29,28]
	bl	putchar
	mov	w0, 6
	str	w0, [x29,44]
.L46:
	ldr	w0, [x29,44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE6:
	.size	handleSingleQuoteOpen, .-handleSingleQuoteOpen
	.align	2
	.global	handleSingleQuoteEsc
	.type	handleSingleQuoteEsc, %function
handleSingleQuoteEsc:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29,28]
	mov	w0, 6
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
.LFE7:
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
.LFB8:
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
	b	.L52
.L63:
	ldr	w0, [x29,20]
	cmp	w0, 10
	bne	.L53
	ldr	w0, [x29,28]
	add	w0, w0, 1
	str	w0, [x29,28]
.L53:
	ldr	w0, [x29,24]
	cmp	w0, 7
	bhi	.L52
	adrp	x1, .L55
	add	x1, x1, :lo12:.L55
	ldr	w2, [x1,w0,uxtw #2]
	adr	x3, .Lrtx55
	add	x2, x3, w2, sxtw #2
	br	x2
.Lrtx55:
	.section	.rodata
	.align	0
	.align	2
.L55:
	.word	(.L54 - .Lrtx55) / 4
	.word	(.L56 - .Lrtx55) / 4
	.word	(.L57 - .Lrtx55) / 4
	.word	(.L58 - .Lrtx55) / 4
	.word	(.L59 - .Lrtx55) / 4
	.word	(.L60 - .Lrtx55) / 4
	.word	(.L61 - .Lrtx55) / 4
	.word	(.L62 - .Lrtx55) / 4
	.text
.L54:
	ldr	w0, [x29,20]
	bl	handleNormal
	str	w0, [x29,24]
	b	.L52
.L56:
	add	x2, x29, 16
	ldr	w0, [x29,20]
	ldr	w1, [x29,28]
	bl	handleHalfOpenComment
	str	w0, [x29,24]
	b	.L52
.L57:
	ldr	w0, [x29,20]
	bl	handleOpenComment
	str	w0, [x29,24]
	b	.L52
.L58:
	ldr	w0, [x29,20]
	bl	handleHalfClosedComment
	str	w0, [x29,24]
	b	.L52
.L59:
	ldr	w0, [x29,20]
	bl	handleDoubleQuoteOpen
	str	w0, [x29,24]
	b	.L52
.L60:
	ldr	w0, [x29,20]
	bl	handleDoubleQuoteEsc
	str	w0, [x29,24]
	b	.L52
.L61:
	ldr	w0, [x29,20]
	bl	handleSingleQuoteOpen
	str	w0, [x29,24]
	b	.L52
.L62:
	ldr	w0, [x29,20]
	bl	handleSingleQuoteEsc
	str	w0, [x29,24]
	nop
.L52:
	bl	getchar
	str	w0, [x29,20]
	ldr	w0, [x29,20]
	cmn	w0, #1
	bne	.L63
	ldr	w0, [x29,24]
	cmp	w0, 1
	bne	.L64
	mov	w0, 47
	bl	putchar
.L64:
	ldr	w0, [x29,24]
	cmp	w0, 2
	beq	.L65
	ldr	w0, [x29,24]
	cmp	w0, 3
	bne	.L66
.L65:
	adrp	x0, stderr
	add	x0, x0, :lo12:stderr
	ldr	x0, [x0]
	ldr	w2, [x29,16]
	adrp	x1, .LC0
	add	x1, x1, :lo12:.LC0
	bl	fprintf
	mov	w0, 1
	b	.L68
.L66:
	mov	w0, 0
.L68:
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",%progbits
