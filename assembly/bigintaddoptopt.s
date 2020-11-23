/*--------------------------------------------------------------------*/
/* bigintaddoptopt.s                                                  */
/* Authors: Byron Zhang and Nicholas Padmanabhan                      */
/*--------------------------------------------------------------------*/

    .equ    FALSE, 0
    .equ    TRUE, 1
    .equ    MAX_DIGITS, 32768

    // BigInt_add constants
    ULSUM       .req x5
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
    mov     ULSUM, 0
    // lIndex = 0;
    mov     LINDEX, 0

    // if (lIndex >= lSumLength) goto endloop1;
    cmp     LINDEX, LSUMLENGTH
    bge     endif6

    add     x0, OADDEND1, AULDIGITS
    add     x1, OADDEND2, AULDIGITS
    add     x2, OSUM, AULDIGITS

loop1:    
    // ulSum += oAddend1->aulDigits[lIndex];
    ldr     x3, [x0, LINDEX, lsl 3]
    adcs    x7, ULSUM, x3

    // if carry occurred, normal-add the second addend and set ULSUM = 1
    bcs     endif3

    // ulSum += oAddend2->aulDigits[lIndex];
    ldr     x4, [x1, LINDEX, lsl 3]
    adcs    ULSUM, x7, x4

    // if a carry occurred, set ULSUM = 1
    bcs     endif4

    // oSum->aulDigits[lIndex] = ulSum;
    str     ULSUM, [x2, LINDEX, lsl 3]

    // ulSum = 0;
    adcs    ULSUM, xzr, xzr
    b       endif5

endif3:
    // ulSum += oAddend2->aulDigits[lIndex];
    ldr     x4, [x1, LINDEX, lsl 3]
    add     ULSUM, x7, x4

endif4:
    // oSum->aulDigits[lIndex] = ulSum;
    str     ULSUM, [x2, LINDEX, lsl 3]

    // ulSum = 1;
    adcs    ULSUM, xzr, xzr

endif5:
    // lIndex++;
    add     LINDEX, LINDEX, 1

    // if (lIndex < lSumLength) goto loop1;
    cmp     LINDEX, LSUMLENGTH
    blt     loop1

endloop1:
    // if (ulSum != 1) goto endif6;
    cmp     ULSUM, 1
    bne     endif6
    
    // if (lSumLength != MAX_DIGITS) goto endif7;
    cmp     LSUMLENGTH, MAX_DIGITS
    bne     endif7

    // Epilog and return FALSE
    mov     w0, FALSE
    ldr     x30, [sp]
    ldr     x19, [sp, 8]
    ldr     x20, [sp, 16]
    ldr     x21, [sp, 24]
    ldr     x22, [sp, 32]
    add     sp, sp, BIGINT_ADD_STACK_BYTECOUNT
    ret

endif7:
    // oSum->aulDigits[lSumLength] = 1;
    mov     x1, 1
    str     x1, [x2, LSUMLENGTH, lsl 3]

    // lSumLength++;
    add     LSUMLENGTH, LSUMLENGTH, 1

endif6:
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
