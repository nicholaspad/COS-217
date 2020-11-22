/*--------------------------------------------------------------------*/
/* bigintaddopt.s                                                     */
/* Authors: Byron Zhang and Nicholas Padmanabhan                      */
/*--------------------------------------------------------------------*/

    .equ    FALSE, 0
    .equ    TRUE, 1
    .equ    MAX_DIGITS, 32768
    .equ    SIZEOF_UL, 8

    // BigInt_add constants
    OADDEND1    .req x19
    OADDEND2    .req x20
    OSUM        .req x21
    ULCARRY     .req x22
    ULSUM       .req x23
    LINDEX      .req x24
    LSUMLENGTH  .req x25

    // struct BigInt constants
    .equ    AULDIGITS, 8
    .equ    LLENGTH, 0

    // BigInt_larger constants
    LLENGTH1    .req x26
    LLENGTH2    .req x27
    LLARGER     .req x28

/*--------------------------------------------------------------------*/

    .section .text

    .equ    BIGINT_ADD_STACK_BYTECOUNT, 96
    .equ    BIGINT_LARGER_STACK_BYTECOUNT, 16

    .global BigInt_add

// static long BigInt_larger(long lLength1, long lLength2)
BigInt_larger:
    // Prolog
    sub     sp, sp, BIGINT_LARGER_STACK_BYTECOUNT
    str     x30, [sp]
    mov     LLENGTH1, x0
    mov     LLENGTH2, x1

    // if (lLength1 <= lLength2) goto else1;
    cmp     LLENGTH1, LLENGTH2
    ble     else1

    // lLarger = lLength1;
    mov     LLARGER, LLENGTH1
    b       endif1
    
else1:
    // lLarger = lLength2;
    mov     LLARGER, LLENGTH2

endif1:
    // Epilog and return lLarger
    mov     x0, LLARGER
    ldr     x30, [sp]
    add     sp, sp, BIGINT_LARGER_STACK_BYTECOUNT
    ret

// int BigInt_add(BigInt_T oAddend1, BigInt_T oAddend2, BigInt_T oSum)
BigInt_add:
    // Prolog
    sub     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    str     x30, [sp]
    str     x19, [sp, 8]
    str     x20, [sp, 16]
    str     x21, [sp, 24]
    str     x22, [sp, 32]
    str     x23, [sp, 40]
    str     x24, [sp, 48]
    str     x25, [sp, 56]
    str     x26, [sp, 64]
    str     x27, [sp, 72]
    str     x28, [sp, 80]
    mov     OADDEND1, x0
    mov     OADDEND2, x1
    mov     OSUM, x2

    // lSumLength = BigInt_larger(oAddend1->lLength, oAddend2->lLength);
    ldr     x0, [OADDEND1, LLENGTH]
    ldr     x1, [OADDEND2, LLENGTH]
    bl      BigInt_larger
    mov     LSUMLENGTH, x0

    // if (oSum->lLength <= lSumLength) goto endif2;
    ldr     x0, [OSUM, LLENGTH]
    cmp     x0, LSUMLENGTH
    ble     endif2

    // memset(oSum->aulDigits, 0, MAX_DIGITS * sizeof(unsigned long));
    add     x0, OSUM, AULDIGITS
    mov     x1, xzr
    mov     x2, MAX_DIGITS
    mov     x3, SIZEOF_UL
    mul     x2, x2, x3
    bl      memset

endif2:
    // ulCarry = 0;
    mov     ULCARRY, xzr
    // lIndex = 0;
    mov     LINDEX, xzr

loop1:
    // if (lIndex >= lSumLength) goto endloop1;
    cmp     LINDEX, LSUMLENGTH
    bge     endloop1

    // ulSum = ulCarry;
    mov     ULSUM, ULCARRY
    // ulCarry = 0;
    mov     ULCARRY, xzr
    
    // ulSum += oAddend1->aulDigits[lIndex];
    add     x0, OADDEND1, AULDIGITS
    ldr     x0, [x0, LINDEX, lsl 3]
    add     ULSUM, ULSUM, x0

    // if (ulSum >= oAddend1->aulDigits[lIndex]) goto endif3;
    cmp     ULSUM, x0
    bhs     endif3

    // ulCarry = 1;
    mov     ULCARRY, 1

endif3:
    // ulSum += oAddend2->aulDigits[lIndex];
    add     x0, OADDEND2, AULDIGITS
    ldr     x0, [x0, LINDEX, lsl 3]
    add     ULSUM, ULSUM, x0

    // if (ulSum >= oAddend2->aulDigits[lIndex]) goto endif3;
    cmp     ULSUM, x0
    bhs     endif4

    // ulCarry = 1;
    mov     ULCARRY, 1

endif4:
    // oSum->aulDigits[lIndex] = ulSum;
    add     x0, OSUM, AULDIGITS
    str     ULSUM, [x0, LINDEX, lsl 3]

    // lIndex++;
    add     LINDEX, LINDEX, 1
    b       loop1

endloop1:
    // if (ulCarry != 1) goto endif5;
    cmp     ULCARRY, 1
    bne     endif5
    
    // if (lSumLength != MAX_DIGITS) goto endif6;
    cmp     LSUMLENGTH, MAX_DIGITS
    bne     endif6

    // Epilog and return FALSE
    mov     w0, FALSE
    ldr     x30, [sp]
    ldr     x19, [sp, 8]
    ldr     x20, [sp, 16]
    ldr     x21, [sp, 24]
    ldr     x22, [sp, 32]
    ldr     x23, [sp, 40]
    ldr     x24, [sp, 48]
    ldr     x25, [sp, 56]
    ldr     x26, [sp, 64]
    ldr     x27, [sp, 72]
    ldr     x28, [sp, 80]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret

endif6:
    // oSum->aulDigits[lSumLength] = 1;
    add     x0, OSUM, AULDIGITS
    mov     x1, 1
    str     x1, [x0, LSUMLENGTH, lsl 3]

    // lSumLength++;
    add     LSUMLENGTH, LSUMLENGTH, 1

endif5:
    // oSum->lLength = lSumLength;
    str     LSUMLENGTH, [OSUM, LLENGTH]
    
    // Epilog and return TRUE
    mov     w0, TRUE
    ldr     x30, [sp]
    ldr     x19, [sp, 8]
    ldr     x20, [sp, 16]
    ldr     x21, [sp, 24]
    ldr     x22, [sp, 32]
    ldr     x23, [sp, 40]
    ldr     x24, [sp, 48]
    ldr     x25, [sp, 56]
    ldr     x26, [sp, 64]
    ldr     x27, [sp, 72]
    ldr     x28, [sp, 80]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret
