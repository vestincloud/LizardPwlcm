#ifndef __PWLCM_H_
#define __PWLCM_H_

#include <inttypes.h>

#define NN 32

void init(uint32_t x0,uint32_t p0, uint32_t x1, uint32_t p1);
uint32_t pwlcm_cross(int S);

#endif
