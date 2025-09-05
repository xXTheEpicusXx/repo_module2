#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include "mychmod.h"

extern int errno;

uint16_t getBitMask(char *str)
{
    uint16_t mask = 0b0;
    if (str[0] >= '0' && str[0] <= '7' && str[1] >= '0' && str[1] <= '7' && str[2] >= '0' && str[2] <= '7')
    {
        mask = (str[0] - '0') * 64 + (str[1] - '0') * 8 + (str[2] - '0');
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (str[3 * i] == 'r')
            {
                mask |= 0b100;
            }
            if (str[3 * i + 1] == 'w')
            {
                mask |= 0b010;
            }
            if (str[3 * i + 2] == 'x')
            {
                mask |= 0b001;
            }
            if (i < 2)
            {
                mask = mask << 3;
            }
        }
    }
    return mask;
}

void getStat(char *str)
{
    struct stat fileStat;
    if (stat(str, &fileStat) == -1)
    {
        if (errno == ENOENT)
        {
            printf("No such file or directory\n");
        }
    }
    else
    {
        int mode = (int)(fileStat.st_mode & 0777);
        char letterMode[10], binMode[10];
        uint16_t b = 0b100000000;
        for (int i = 0; i < 9; i++)
        {
            binMode[i] = b & mode ? '1' : '0'; // 0 3 6 1 4 7 2 5 8 = 3n 3n+1 3n+2
            if (i % 3 == 0)
            {
                letterMode[i] = binMode[i] == '1' ? 'r' : '-';
            }
            else if ((i - 1) % 3 == 0)
            {
                letterMode[i] = binMode[i] == '1' ? 'w' : '-';
            }
            else if ((i - 2) % 3 == 0)
            {
                letterMode[i] = binMode[i] == '1' ? 'x' : '-';
            }
            b = b >> 1;
        }
        letterMode[9] = 0;
        binMode[9] = 0;
        printf("Права файла %s: -%s 0b%s %o\n", str, letterMode, binMode, mode);
    }
}

void myChmod(int mode, char *str)
{
    struct stat fileStat;
    if (stat(str, &fileStat) == -1)
    {
        if (errno == ENOENT)
        {
            printf("No such file or directory\n");
        }
        return;
    }

    int curMode = fileStat.st_mode & 0777;
    int finalMode = (fileStat.st_mode & ~0777) | (mode & 0777);

    printf("Текущие права: %o\n", curMode);
    printf("Новые права: %o\n", mode);
    printf("Итоговые права: %o\n", finalMode & 0777);
}
