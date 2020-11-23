/*--------------------------------------------------------------------*/
/* bigintaddoptopt.s                                                  */
/* Authors: Byron Zhang and Nicholas Padmanabhan                      */
/*--------------------------------------------------------------------*/

    .equ    FALSE, 0
    .equ    TRUE, 1
    .equ    MAX_DIGITS, 32768

    // BigInt_add constants
    C_FLAG       .req x5
    LINDEX      .req x6
    OADDEND1    .req x19
    OADDEND2    .req x20
    OSUM        .req x21
    LSUMLENGTH  .req x22

    // struct BigInt constants
    .equ    AULDIGITS, 8
    .equ    LLENGTH, 0

/*--------------------------------------------------------------------*/

    .section .text

    .equ    BIGINT_ADD_STACK_BYTECOUNT, 48

    .global BigInt_add

// int BigInt_add(BigInt_T oAddend1, BigInt_T oAddend2, BigInt_T oSum)
BigInt_add:
    // Prolog
    sub     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    str     x30, [sp]
    str     x19, [sp, 8]
    str     x20, [sp, 16]
    str     x21, [sp, 24]
    str     x22, [sp, 32]
    mov     OADDEND1, x0
    mov     OADDEND2, x1
    mov     OSUM, x2

    // lLength1 = oAddend1->lLength;
    // lLength2 = oAddend2->lLength;
    ldr     x0, [OADDEND1, LLENGTH]
    ldr     x1, [OADDEND2, LLENGTH]

    // if (lLength1 <= lLength2) goto else1;
    cmp     x0, x1
    ble     else1

    // lSumLength = lLength1;
    mov     LSUMLENGTH, x0
    b       endif1
    
else1:
    // lSumLength = lLength2;
    mov     LSUMLENGTH, x1

endif1:
    // if (oSum->lLength <= lSumLength) goto endif2;
    ldr     x0, [OSUM, LLENGTH]
    cmp     x0, LSUMLENGTH
    ble     endif2

    // memset(oSum->aulDigits, 0, MAX_DIGITS * sizeof(unsigned long));
    add     x0, OSUM, AULDIGITS
    mov     x1, 0
    mov     x2, MAX_DIGITS
    lsl     x2, x2, 3
    bl      memset

endif2:
    // ulSum = 0;
    mov     C_FLAG, 0
    // lIndex = 0;
    mov     LINDEX, 0

    // if (lIndex >= lSumLength) goto endloop1;
    cmp     LINDEX, LSUMLENGTH
    bge     endif4

    add     x0, OADDEND1, AULDIGITS
    add     x1, OADDEND2, AULDIGITS
    add     x2, OSUM, AULDIGITS

loop1:    
    // ulSum += oAddend1->aulDigits[lIndex];
    ldr     x3, [x0, LINDEX, lsl 3]
    adcs    x7, x7, x3

    // Set C_FLAG to C
    adcs    C_FLAG, xzr, xzr

    // ulSum += oAddend2->aulDigits[lIndex];
    ldr     x4, [x1, LINDEX, lsl 3]
    adcs    x7, x7, x4

    // If C is 0, do not change C_FLAG; otherwise, set C_FLAG to 1
    bcc     endif3
    mov     C_FLAG, 1

endif3:
    // oSum->aulDigits[lIndex] = ulSum;
    str     x7, [x2, LINDEX, lsl 3]

    // lIndex++;
    add     LINDEX, LINDEX, 1

    // if (lIndex < lSumLength) goto loop1;
    cmp     LINDEX, LSUMLENGTH
    blt     loop1

endloop1:
    // if (C_FLAG != 1) goto endif4;
    cmp     C_FLAG, 1
    bne     endif4
    
    // if (lSumLength != MAX_DIGITS) goto endif5;
    cmp     LSUMLENGTH, MAX_DIGITS
    bne     endif5

    // Epilog and return FALSE
    mov     w0, FALSE
    ldr     x30, [sp]
    ldr     x19, [sp, 8]
    ldr     x20, [sp, 16]
    ldr     x21, [sp, 24]
    ldr     x22, [sp, 32]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret

endif5:
    // oSum->aulDigits[lSumLength] = 1;
    mov     x1, 1
    str     x1, [x2, LSUMLENGTH, lsl 3]

    // lSumLength++;
    add     LSUMLENGTH, LSUMLENGTH, 1

endif4:
    // oSum->lLength = lSumLength;
    str     LSUMLENGTH, [OSUM, LLENGTH]
    
    // Epilog and return TRUE
    mov     w0, TRUE
    ldr     x30, [sp]
    ldr     x19, [sp, 8]
    ldr     x20, [sp, 16]
    ldr     x21, [sp, 24]
    ldr     x22, [sp, 32]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret
