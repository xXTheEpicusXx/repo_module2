#include "IP_Route.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    uint32_t gateway = strTo_IP(argv[1], strlen(argv[1]));
    uint32_t mask = getMask(argv[2], strlen(argv[2]));
    int n = atoi(argv[3]);
    uint32_t *IPs;
    IPs = (uint32_t *)malloc(n * sizeof(uint32_t));
    generate_IPs(gateway, mask, IPs, n);
    print_IPs(gateway, mask, IPs, n);
    statistics(gateway, mask, IPs, n);
    free(IPs);
    return 0;
}
