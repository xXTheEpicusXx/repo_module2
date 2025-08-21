#include "checknum.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void argsHandler(int start, int end, char *argv[])
{
    for (int i = start; i < end; i++)
    {
        int isNumber = checkNumber(argv[i], strlen(argv[i]));
        printf("pid: %d |", getpid());
        if (isNumber)
        {
            char *endptr;
            double num = strtod(argv[i], &endptr);

            printf("число из %s x2 = %lf\n", argv[i], num * 2);
        }
        else
        {
            printf("строка %s\n", argv[i]);
        }
    }
}

int checkNumber(char *str, int strlen)
{
    int isNum = 0;
    char numbersStr[] = "0123456789";
    int pointCnt = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '-')
        {
            if (strlen == 1)
            {
                isNum = 0;
                break;
            }
            if (i == 0)
            {
                continue;
            }
            else
            {
                isNum = 0;
                break;
            }
        }
        else if (str[i] == '.')
        {
            pointCnt++;
            if (i == 0 || ((i == 1) && str[0] == '-'))
            {
                isNum = 0;
                break;
            }
            if (i == strlen - 1)
            {
                isNum = 0;
                break;
            }
            if (pointCnt > 1)
            {
                isNum = 0;
                break;
            }
        }
        else if (strchr(numbersStr, str[i]) != NULL)
        {
            isNum = 1;
        }
        else
        {
            isNum = 0;
            break;
        }
    }
    return isNum;
}
