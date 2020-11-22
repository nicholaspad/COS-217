/*--------------------------------------------------------------------*/
/* mywc.s                                                             */
/* Authors: Byron Zhang and Nicholas Padmanabhan                      */
/*--------------------------------------------------------------------*/

    .equ    FALSE, 0
    .equ    TRUE, 1
    .equ    EOF, -1
    .equ    NEW_LINE, 10

/*--------------------------------------------------------------------*/

    .section .rodata

printfFormatStr:
    .string "%7ld %7ld %7ld\n"

/*--------------------------------------------------------------------*/

    .section .data

lLineCount:
    .quad   0
lWordCount:
    .quad   0
lCharCount:
    .quad   0
iInWord:
    .word   FALSE

/*--------------------------------------------------------------------*/

    .section .bss

iChar:
    .skip   4

/*--------------------------------------------------------------------*/

    .section .text

    .equ    MAIN_STACK_BYTECOUNT, 16

    .global main

main:
    // Prolog
    sub     sp, sp, MAIN_STACK_BYTECOUNT
    str     x30, [sp]

readLoop:
    // while ((iChar = getchar()) != EOF)
    bl      getchar
    adr     x1, iChar
    str     w0, [x1]
    cmp     w0, EOF
    beq     endReadLoop

    // lCharCount++;
    adr     x0, lCharCount
    ldr     x1, [x0]
    add     x1, x1, 1
    str     x1, [x0]

    // if (isspace(iChar))
    //     if (iInWord)
    adr     x0, iChar
    ldr     w0, [x0]
    bl      isspace
    cmp     w0, FALSE
    beq     else1
    
    adr     x0, iInWord
    ldr     w0, [x0]
    cmp     w0, FALSE
    beq     endif1

    // lWordCount++;
    adr     x0, lWordCount
    ldr     x1, [x0]
    add     x1, x1, 1
    str     x1, [x0]

    // iInWord = FALSE;
    adr     x0, iInWord
    mov     w1, FALSE
    str     w1, [x0]

    b       endif1

else1:
    // else
    //     if (!iInWord)
    adr     x0, iInWord
    ldr     w0, [x0]
    cmp     w0, TRUE
    beq     endif1

    // iInWord = TRUE;
    adr     x0, iInWord
    mov     w1, TRUE
    str     w1, [x0]

endif1:
    // if (iChar == '\n')
    adr     x0, iChar
    ldr     w0, [x0]
    cmp     w0, NEW_LINE
    bne     endif2
    
    // lLineCount++;
    adr     x0, lLineCount
    ldr     x1, [x0]
    add     x1, x1, 1
    str     x1, [x0]

endif2:
    b       readLoop

endReadLoop:
    // if (iInWord)
    adr     x0, iInWord
    ldr     w0, [x0]
    cmp     w0, FALSE
    beq     endif3

    // lWordCount++;
    adr     x0, lWordCount
    ldr     x1, [x0]
    add     x1, x1, 1
    str     x1, [x0]

endif3:
    // printf("%7ld %7ld %7ld\n", lLineCount, lWordCount, lCharCount);
    adr     x0, printfFormatStr
    adr     x1, lLineCount
    ldr     x1, [x1]
    adr     x2, lWordCount
    ldr     x2, [x2]
    adr     x3, lCharCount
    ldr     x3, [x3]
    bl      printf

    // Epilog and return 0
    mov     w0, 0
    ldr     x30, [sp]
    add     sp, sp, MAIN_STACK_BYTECOUNT
    ret
