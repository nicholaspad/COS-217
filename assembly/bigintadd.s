/*--------------------------------------------------------------------*/
/* bigintadd.s                                                        */
/* Authors: Byron Zhang and Nicholas Padmanabhan                      */
/*--------------------------------------------------------------------*/

    .equ    FALSE, 0
    .equ    TRUE, 1
    .equ    MAX_DIGITS, 32768
    .equ    SIZEOF_UL, 8

    // BigInt_add constants
    .equ    OADDEND1, 56
    .equ    OADDEND2, 48
    .equ    OSUM, 40
    .equ    ULCARRY, 32
    .equ    ULSUM, 24
    .equ    LINDEX, 16
    .equ    LSUMLENGTH, 8

    // struct BigInt constants
    .equ    AULDIGITS, 8
    .equ    LLENGTH, 0

    // BigInt_larger constants
    .equ    LLENGTH1, 24
    .equ    LLENGTH2, 16
    .equ    LLARGER, 8

/*--------------------------------------------------------------------*/

    .section .text

    .equ    BIGINT_ADD_STACK_BYTECOUNT, 64
    .equ    BIGINT_LARGER_STACK_BYTECOUNT, 32

    .global BigInt_add

// static long BigInt_larger(long lLength1, long lLength2)
BigInt_larger:
    // Prolog
    sub     sp, sp, BIGINT_LARGER_STACK_BYTECOUNT
    str     x30, [sp]
    str     x0, [sp, LLENGTH1]
    str     x1, [sp, LLENGTH2]

    // if (lLength1 <= lLength2) goto else1;
    ldr     x0, [sp, LLENGTH1]
    ldr     x1, [sp, LLENGTH2]
    cmp     x0, x1
    ble     else1

    // lLarger = lLength1;
    str     x0, [sp, LLARGER]
    b       endif1
    
else1:
    // lLarger = lLength2;
    str     x1, [sp, LLARGER]

endif1:
    // Epilog and return lLarger
    ldr     x0, [sp, LLARGER]
    ldr     x30, [sp]
    add     sp, sp, BIGINT_LARGER_STACK_BYTECOUNT
    ret

// int BigInt_add(BigInt_T oAddend1, BigInt_T oAddend2, BigInt_T oSum)
BigInt_add:
    // Prolog
    sub     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    str     x30, [sp]
    str     x0, [sp, OADDEND1]
    str     x1, [sp, OADDEND2]
    str     x2, [sp, OSUM]

    
    // lSumLength = BigInt_larger(oAddend1->lLength, oAddend2->lLength);
    ldr     x0, [sp, OADDEND1]
    ldr     x1, [sp, OADDEND2]
    ldr     x0, [x0, LLENGTH]
    ldr     x1, [x1, LLENGTH]
    bl      BigInt_larger
    str     x0, [sp, LSUMLENGTH]

    // if (oSum->lLength <= lSumLength) goto endif2;
    ldr     x0, [sp, OSUM]
    ldr     x1, [sp, LSUMLENGTH]
    ldr     x0, [x0, LLENGTH]
    cmp     x0, x1
    ble     endif2

    // memset(oSum->aulDigits, 0, MAX_DIGITS * sizeof(unsigned long));
    ldr     x0, [sp, OSUM]
    add     x0, x0, AULDIGITS
    mov     x1, xzr
    mov     x2, MAX_DIGITS
    mov     x3, SIZEOF_UL
    mul     x2, x2, x3
    bl      memset

endif2:
    // ulCarry = 0;
    str     xzr, [sp, ULCARRY]
    // lIndex = 0;
    str     xzr, [sp, LINDEX]

loop1:
    // if (lIndex >= lSumLength) goto endloop1;
    ldr     x0, [sp, LINDEX]
    ldr     x1, [sp, LSUMLENGTH]
    cmp     x0, x1
    bge     endloop1

    // ulSum = ulCarry;
    ldr     x0, [sp, ULCARRY]
    str     x0, [sp, ULSUM]
    // ulCarry = 0;
    str     xzr, [sp, ULCARRY]
    
    // ulSum += oAddend1->aulDigits[lIndex];
    ldr     x0, [sp, ULSUM]
    ldr     x1, [sp, OADDEND1]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LINDEX]
    ldr     x1, [x1, x2, lsl 3]
    add     x0, x0, x1
    str     x0, [sp, ULSUM]
    
    // if (ulSum >= oAddend1->aulDigits[lIndex]) goto endif3;
    ldr     x0, [sp, ULSUM]
    ldr     x1, [sp, OADDEND1]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LINDEX]
    ldr     x1, [x1, x2, lsl 3]
    cmp     x0, x1
    bhs     endif3

    // ulCarry = 1;
    mov     x0, 1
    str     x0, [sp, ULCARRY]

endif3:
    // ulSum += oAddend2->aulDigits[lIndex];
    ldr     x0, [sp, ULSUM]
    ldr     x1, [sp, OADDEND2]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LINDEX]
    ldr     x1, [x1, x2, lsl 3]
    add     x0, x0, x1
    str     x0, [sp, ULSUM]

    // if (ulSum >= oAddend2->aulDigits[lIndex]) goto endif3;
    ldr     x0, [sp, ULSUM]
    ldr     x1, [sp, OADDEND2]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LINDEX]
    ldr     x1, [x1, x2, lsl 3]
    cmp     x0, x1
    bhs     endif4

    // ulCarry = 1;
    mov     x0, 1
    str     x0, [sp, ULCARRY]

endif4:
    // oSum->aulDigits[lIndex] = ulSum;
    ldr     x0, [sp, ULSUM]
    ldr     x1, [sp, OSUM]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LINDEX]
    str     x0, [x1, x2, lsl 3]

    // lIndex++;
    ldr     x0, [sp, LINDEX]
    add     x0, x0, 1
    str     x0, [sp, LINDEX]

    b       loop1

endloop1:
    // if (ulCarry != 1) goto endif5;
    ldr     x0, [sp, ULCARRY]
    cmp     x0, 1
    bne     endif5
    
    // if (lSumLength != MAX_DIGITS) goto endif6;
    ldr     x0, [sp, LSUMLENGTH]
    mov     x1, MAX_DIGITS
    cmp     x0, x1
    bne     endif6

    // Epilog and return FALSE
    mov     w0, FALSE
    ldr     x30, [sp]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret

endif6:
    // oSum->aulDigits[lSumLength] = 1;
    mov     x0, 1
    ldr     x1, [sp, OSUM]
    add     x1, x1, AULDIGITS
    ldr     x2, [sp, LSUMLENGTH]
    str     x0, [x1, x2, lsl 3]

    // lSumLength++;
    ldr     x0, [sp, LSUMLENGTH]
    add     x0, x0, 1
    str     x0, [sp, LSUMLENGTH]

endif5:
    // oSum->lLength = lSumLength;
    ldr     x0, [sp, OSUM]
    add     x0, x0, LLENGTH
    ldr     x1, [sp, LSUMLENGTH]
    str     x1, [x0]
    
    // Epilog and return TRUE
    mov     w0, TRUE
    ldr     x30, [sp]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret
