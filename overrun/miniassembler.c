/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Authors: Bob Dondero, Byron Zhang, Nicholas Padmanabhan            */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"

unsigned int MiniAssembler_mov(unsigned int uiReg,
                               unsigned int uiImmed) {
    unsigned int uiInstr;

    /* Set opcode and instruction width */
    uiInstr = 0x52800000;

    /* Set destination register */
    uiInstr |= uiReg;

    /* Prepare and set immediate value */
    uiImmed <<= 5;
    uiImmed &= 0x01ffffe0;
    uiInstr |= uiImmed;

    return uiInstr;
}

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
                               unsigned long ulAddrOfThisInstr) {
    unsigned int uiInstr;
    unsigned int uiDisp;
    unsigned int uiDispLo;
    unsigned int uiDispHi;

    /* Set opcode and instruction width */
    uiInstr = 0x10000000;

    /* Set destination register */
    uiInstr |= uiReg;

    /* Find relative offset between ulAddr and ulAddrOfThisInstr */
    uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

    /* Prepare and set low-order relative offset bits */
    uiDispLo = uiDisp & 0x3;
    uiDispLo = uiDispLo << 29;
    uiInstr |= uiDispLo;

    /* Prepare and set high-order relative offset bits */
    uiDispHi = uiDisp >> 2;
    uiDispHi = uiDispHi << 5;
    uiDispHi &= 0x00ffffe0;
    uiInstr |= uiDispHi;

    return uiInstr;
}

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg) {
    unsigned int uiInstr;

    /* Set opcode and instruction width */
    uiInstr = 0x39000000;

    /* Set "from" register */
    uiInstr |= uiFromReg;

    /* Prepare and set "to" register */
    uiToReg <<= 5;
    uiInstr |= uiToReg;

    return uiInstr;
}

unsigned int MiniAssembler_b(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr) {
    unsigned int uiInstr;
    unsigned int uiDisp;

    /* Set opcode and instruction width */
    uiInstr = 0x14000000;

    /* Prepare and set relative offset between ulAddr and
    ulAddrOfThisInstr */
    uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);
    uiDisp >>= 2;
    uiDisp &= 0x03ffffff;
    uiInstr |= uiDisp;

    return uiInstr;
}

unsigned int MiniAssembler_bl(unsigned long ulAddr,
                              unsigned long ulAddrOfThisInstr) {
    unsigned int uiInstr;
    unsigned int uiDisp;

    /* Set opcode and instruction width */
    uiInstr = 0x94000000;

    /* Prepare and set relative offset between ulAddr and
    ulAddrOfThisInstr */
    uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);
    uiDisp >>= 2;
    uiDisp &= 0x03ffffff;
    uiInstr |= uiDisp;

    return uiInstr;
}
