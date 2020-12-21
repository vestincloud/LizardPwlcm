#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "toolex.h"
/*
 * Input formats must be 120 bit key as 30 hex values and 64 bit IV as 16 hex values.
 * The keystream output length can be chosen between 1 bit and 10000 bits.
 */

uint8_t hex2int(char ch){
	if (ch >= '0' && ch <= '9')
		return (uint8_t)(ch - '0');
	if (ch >= 'A' && ch <='F')
		return (uint8_t)(ch-'A' + 10);
	if (ch >= 'a' && ch <= 'f')
		return (uint8_t)(ch - 'a' +10);
	return (uint8_t) -1;
}

void hex2binArray(char* hex, uint8_t * bin) {
    for (uint8_t i = 0; i < strlen(hex); ++i){
        uint16_t val = hex2int(hex[i]);

        bin[i*4 + 3] = (uint8_t) (val & 1);
        bin[i*4 + 2] = (uint8_t) ((val >> 1) & 1);
        bin[i*4 + 1] = (uint8_t) ((val >> 2) & 1);
        bin[i*4 + 0] = (uint8_t) ((val >> 3) & 1);

    }
}
void dec2binArray(uint16_t  x, uint8_t *bin, int length){
	for(int i=length-1; i>=0; i--){
		bin[i]= (uint8_t)(x & 1);
		x >>= 1;
	}
}

