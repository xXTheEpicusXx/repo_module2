#include "IP_Route.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

uint32_t strTo_IP(char *str, int len)
{
    uint32_t IP = 0;
    char *token = strtok(str, ".");
    for (int i = 0; i < 4; i++)
    {
        if (token != NULL)
        {
            uint32_t tmp = atoi(token);
            printf("%d\n", tmp);
            IP |= tmp;
            if (i < 3)
            {
                IP = IP << 8;
            }
        }
        token = strtok(NULL, ".");
    }
    return IP;
}

uint32_t getMask(char *str, int len)
{
    // ввод маски подсети в формате /n
    uint32_t mask = (uint32_t)(uint64_t)pow(2, atoi(&str[1])) - 1 << (32 - atoi(&str[1]));
    return mask;
}

void generate_IPs(uint32_t gateway, uint32_t mask, uint32_t *IPs, int n)
{
    srand(time(NULL));
    uint32_t network = gateway & mask;
    uint32_t host_mask = ~mask;

    for (int i = 0; i < n; i++)
    {
        if (rand() % 100 < 50)
        {

            IPs[i] = network | (rand() & host_mask);
        }
        else
        {
            IPs[i] = (rand() % 256) << 24 | (rand() % 256) << 16 |
                     (rand() % 256) << 8 | (rand() % 256);
        }
    }
}

void print_IPs(uint32_t gateway, uint32_t mask, uint32_t *IPs, int n)
{
    for (int i = 0; i < n; i++)
    {
        if ((gateway & mask) == (IPs[i] & mask))
        {
            printf("\e[32m%d.%d.%d.%d\e[0m\n", (IPs[i] >> 24) & 255, (IPs[i] >> 16) & 255, (IPs[i] >> 8) & 255, (IPs[i]) & 255);
        }
        else
        {
            printf("\e[31m%d.%d.%d.%d\e[0m\n", (IPs[i] >> 24) & 255, (IPs[i] >> 16) & 255, (IPs[i] >> 8) & 255, (IPs[i]) & 255);
        }
    }
}

void statistics(uint32_t gateway, uint32_t mask, uint32_t *IPs, int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if ((gateway & mask) == (IPs[i] & mask))
        {
            cnt++;
        }
    }
    printf("Принято сетью: %d  Не принято: %d\n", cnt, n - cnt);
}
