#include "pwlcm.h"
#include "lizard.h"

uint32_t P1;
uint32_t P2;
uint32_t X0;
uint32_t X1;

uint64_t M1;
uint64_t M2;
uint64_t R1;
uint64_t R2;
uint64_t R3;
uint64_t R4;

void init(uint32_t x0, uint32_t p0, uint32_t x1, uint32_t p1){
	X0 = x0;
	X1 = x1;
	P1 = p0;
	P2 = p1;

	M1 = ((uint64_t)1 << NN)-1;
	M2 = (uint64_t)1 << (NN-1);
	R1 = (M1 << NN)/P1;
	R2 = (M1 << NN)/(M2-P1);
	R3 = (M1 << NN)/P2;
	R4 = (M1 << NN)/(M2-P2);
}

uint32_t pwlcm(uint32_t X,uint32_t P,uint64_t r1, uint64_t r2){
	if(0 < X && X <= P)
		X = (uint32_t)((X*r1)>>NN);
	else if(P < X && X <= M2)
		X = (uint32_t)(((X-P)*r2)>>NN);
	else if(M2 < X && X <= M1-P)
		X = (uint32_t)(((M1-P-X)*r2)>>NN);
	else if(M1-P < X && X <=M1)
		X = (uint32_t)(((M1-X)*r1)>>NN);
	else
		X = (uint32_t)((M1-1));

	return X;
}

uint32_t pwlcm_cross(int S){
	uint32_t tmp;
	uint8_t r2;
	uint32_t S1 = ((uint32_t)S)<<(NN-1);

	X0 = pwlcm(X0, P1, R1,R2);
	X1 = pwlcm(X1, P2, R3,R4);
	tmp = X0 ^ X1;
	S &= 1;
	r2 = (X0 & S1) >> (NN-1);
	X0 <<= 1;
	X0 ^= (uint32_t)S;
	r2 ^= (X1 & 1);
	extra_feedback(r2);
	X1 >>= 1;
	X1 ^= S1;

	return tmp;
}
