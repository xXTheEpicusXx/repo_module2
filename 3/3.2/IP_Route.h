#include <stdint.h>

uint32_t strTo_IP(char *str, int len);
uint32_t getMask(char *str, int len);
void generate_IPs(uint32_t gateway, uint32_t mask, uint32_t *IPs, int n);
void print_IPs(uint32_t gateway, uint32_t mask,uint32_t *IPs, int n);
void statistics(uint32_t gateway, uint32_t mask, uint32_t *IPs, int n);
