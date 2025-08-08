#define USR_MASK 0b111000000
#define GRP_MASK 0b000111000
#define OTH_MASK 0b000000111

#include <stdint.h>

uint16_t getBitMask(char *str);
void getStat(char *str);
void myChmod(int mode, char *str);
