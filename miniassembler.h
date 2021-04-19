/*--------------------------------------------------------------------*/
/* miniassembler.h                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#ifndef MINIASSEMBLER_INCLUDED
#define MINIASSEMBLER_INCLUDED

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "mov reg, immed" where
   reg is a W register.

   Parameters:
      uiReg: the number of reg.  0 <= uiReg <= 31.
      iImmed: the immed value. -32768 <= iImmed <= 32767      */

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed);

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "adr reg, addr".

   Parameters:
      uiReg: the number of reg. 0 <= uiReg <= 31.
      ulAddr: the address denoted by addr.
      ulAddrOfThisInstr: the address of the adr instruction itself
                         (must be a multiple of 4).                   */

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr);

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "strb fromreg,[toreg]",
   where fromreg is a W register and toreg is a X register.

   Parameters:
      uiFromReg: the number of fromreg. 0 <= uiFromReg <= 31.
      uiToReg: the number of toreg.     0 <= uiToReg <= 31.           */

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg);

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "b addr".

   Parameters:
      ulAddr: the address denoted by addr, that is, the address to
         which the branch should occur (must be a multiple of 4).
      ulAddrOfThisInstr: the address of the b instruction itself
         (must be a multiple of 4).                                   */

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr);



#endif
