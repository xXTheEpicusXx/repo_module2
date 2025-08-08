#include "mychmod.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
// printf("%s", argv[1]);
#ifdef MASK
    uint16_t mask = getBitMask(argv[1]);
    printf("0b");
    uint16_t b = 0b100000000;
    for (int i = 0; i < 9; i++)
    {
        printf("%d", b & mask ? 1 : 0);
        b = b >> 1;
    }
    printf("\n");
#elif STAT
    getStat(argv[1]);
#elif CHMOD
    myChmod(getBitMask(argv[1]), argv[2]);
#endif
    return 0;
}
