/*--------------------------------------------------------------------*/
/* testminiassembler.c                                                */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <stdio.h>

/*--------------------------------------------------------------------*/

/* Test the MiniAssembler module by calling its functions with a
   variety of arguments and writing the returned values to stdout.
   Return 0. */

int main(void)
{
   int i1;
   int i2;
   int i3;

   unsigned int auiRegisters[] = {0, 1, 15, 29, 30};
   unsigned long aulAddresses[] = {0x00000000UL, 0x00000001UL,
      0x001ffffeUL, 0x001fffffUL, 0x01234567UL, 0x76543210UL};
   /* instruction addresses must be multiples of 4 */
   unsigned long aulInstrAddr[] = {0x00000000UL, 0x00000004UL,
      0x001ffff0UL, 0x001ffffcUL, 0x01234568UL, 0x76543210UL};
   int aiImmeds[] = {0, 1, 32767, -1, -2, -32767, -32768};

   int iRegisterCount =(int)(sizeof(auiRegisters)/sizeof(unsigned int));
   int iAddressCount =
      (int)(sizeof(aulAddresses)/sizeof(unsigned long));
   int iInstrAddrCount =
      (int)(sizeof(aulInstrAddr)/sizeof(unsigned long));
   int iImmedCount = (int)(sizeof(aiImmeds)/sizeof(int));

   /* Test MiniAssembler_mov. */
   /* the negative values in the aiImmeds array are to                */
   /* make sure the mov masks the immediate value before shifting it  */

   for (i1 = 0; i1 < iRegisterCount; i1++)
      for (i2 = 0; i2 < iImmedCount; i2++)
      {
         unsigned int uiRegister = auiRegisters[i1];
         int iImmed = aiImmeds[i2];
         printf("MiniAssembler_mov(%u, %d): 0x%08x\n",
            uiRegister, iImmed,
            MiniAssembler_mov(uiRegister, iImmed));
      }


   /* Test MiniAssembler_adr. */

   for (i1 = 0; i1 < iRegisterCount; i1++)
      for (i2 = 0; i2 < iAddressCount; i2++)
         for (i3 = 0; i3 < iInstrAddrCount; i3++)
         {
            unsigned int uiRegister = auiRegisters[i1];
            unsigned long ulAddress1 = aulAddresses[i2];
            unsigned long ulAddress2 = aulInstrAddr[i3];
            printf("MiniAssembler_adr(%u, 0x%08lx, 0x%08lx): 0x%08x\n",
               uiRegister, ulAddress1, ulAddress2,
               MiniAssembler_adr(uiRegister, ulAddress1, ulAddress2));
         }

   /* Test MiniAssembler_strb. */

   for (i1 = 0; i1 < iRegisterCount; i1++)
      for (i2 = 0; i2 < iRegisterCount; i2++)
      {
         unsigned int uiRegister1 = auiRegisters[i1];
         unsigned int uiRegister2 = auiRegisters[i2];
         printf("MiniAssembler_strb(%u, %u): 0x%08x\n",
            uiRegister1, uiRegister2,
            MiniAssembler_strb(uiRegister1, uiRegister2));
      }

   /* Test MiniAssembler_b. */
   /* Do not use the largest instruction address as the
      difference will be too large to fit correctly in 26 bits */

   for (i1 = 0; i1 < iInstrAddrCount - 1; i1++)
      for (i2 = 0; i2 < iInstrAddrCount - 1; i2++)
      {
         unsigned long ulAddress1 = aulInstrAddr[i1];
         unsigned long ulAddress2 = aulInstrAddr[i2];
         printf("MiniAssembler_b(0x%08lx, 0x%08lx): 0x%08x\n",
            ulAddress1, ulAddress2,
            MiniAssembler_b(ulAddress1, ulAddress2));
      }

   return 0;
}
