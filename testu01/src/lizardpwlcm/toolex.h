#ifndef __TOOLEX_H_
#define __TOOLEX_H_

#include <stdint.h>

void hex2binArray(char *hex, uint8_t *bin);
void dec2binArray(uint16_t x, uint8_t *bin,int length);
#endif
