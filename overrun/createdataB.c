/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Authors: Byron Zhang & Nicholas Padmanabhan                        */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Takes no command-line or function arguments and does not read from
    any input stream. Writes to a file stream, creating a text file
    called dataB. Returns EXIT_SUCCESS.
*/
int main(void) {
    const char *name = "Nick Zhang";
    const size_t BUFSIZE = 48;
    FILE *psFile;
    size_t i;
    unsigned long ulData = 0x400858;

    /* Creates empty dataB text file */
    psFile = fopen("dataB", "w");

    /* Writes each char from *name into psFile */
    for (i = 0; i < strlen(name); i++) putc(name[i], psFile);

    /* Writes null bytes until there are BUFSIZE bytes in psFile */
    for (i = strlen(name); i < BUFSIZE; i++) putc(0, psFile);

    /* Writes the address of the first instruction of grade = 'B' */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);

    /* Closes the dataB text file */
    fclose(psFile);

    return EXIT_SUCCESS;
}
