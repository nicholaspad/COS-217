#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int j;
    char k;

    j = 0;

    for (i = 0; i < 50000; i++) {
        k = (char)(((unsigned int)rand()) & 0x7f);
        if (k == 0x9 || k == 0x0A || (k <= 0x7E && k >= 0x20)) {
            putchar(k);
            if (k == '\n')
                j++;
            if (j == 999)
                break;
        } else {
            i--;
            continue;
        }
    }

    return 0;
}
