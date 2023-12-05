/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits) {
    unsigned int i;

    assert(puiDest != NULL);

    i = 0;
    while (i < uiNumBits) {
        unsigned int uiSrcBitValue = (uiSrc >> (uiSrcStartBit + i)) & 1;
        *puiDest |= uiSrcBitValue << (uiDestStartBit + i);
        i++;
    }
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed) {
    unsigned int uiInstr;

    assert(uiReg <= 31);
    assert(iImmed >= -32768);
    assert(iImmed <= 32767);

    /* Base Instruction Code for mov */
    uiInstr = 0x52800000;

    /* destination register */
    setField(uiReg, 0, &uiInstr, 0, 5);

    /* immediate value */
    setField((unsigned int)iImmed, 0, &uiInstr, 5, 16);

    return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
                               unsigned long ulAddrOfThisInstr) {
    unsigned int uiInstr;
    unsigned int uiDisp;

    assert(uiReg <= 31);
    assert(ulAddrOfThisInstr % 4 == 0);

    /* Base Instruction Code for adr */
    uiInstr = 0x10000000;

    /* register to be inserted in instruction */
    setField(uiReg, 0, &uiInstr, 0, 5);

    /* displacement to be split into immlo and immhi and inserted */
    uiDisp = (unsigned int) (ulAddr - ulAddrOfThisInstr);

    setField(uiDisp, 0, &uiInstr, 29, 2);
    setField(uiDisp, 2, &uiInstr, 5, 19);

    return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg) {
    unsigned int uiInstr;

    assert(uiFromReg <= 31);
    assert(uiToReg <= 31);

    /* Base Instruction Code for strb */
    uiInstr = 0x39000000;

    /* source register */
    setField(uiFromReg, 0, &uiInstr, 0, 5);

    /* destination register */
    setField(uiToReg, 0, &uiInstr, 5, 5);

    return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr) {
    unsigned int uiInstr;
    unsigned long relativeAddr;

    assert(ulAddr % 4 == 0);
    assert(ulAddrOfThisInstr % 4 == 0);

    /* Base Instruction Code for b */
    uiInstr = 0x14000000;

    /* Calculate the relative displacement */
    relativeAddr = (ulAddr - ulAddrOfThisInstr) >> 2;

    /* Set displacement */
    setField((unsigned int) relativeAddr, 0, &uiInstr, 0, 26);

    return uiInstr;

}

unsigned int MiniAssembler_bl(unsigned long ulAddr, unsigned long ulAddrOfThisInstr)
{
    unsigned int uiInstr;
    unsigned long relativeAddr;

    assert(ulAddr % 4 == 0);
    assert(ulAddrOfThisInstr % 4 == 0);

    /* Base Instruction Code for bl (branch with link) */
    uiInstr = 0x94000000;

    /* Calculate the relative displacement */
    relativeAddr = (ulAddr - ulAddrOfThisInstr) >> 2;

    /* Set displacement */
    setField((unsigned int)relativeAddr, 0, &uiInstr, 0, 26);

    return uiInstr;
}
