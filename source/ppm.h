#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef __uint128_t uint128;
typedef __uint32_t uint32;

const int N =32;
const int NF =62;
uint128 R=1;
uint128 M = 1;
uint128 M2 =1;
uint32 x0 =283929;

#define ppm_l  1
#define  ppm_m 31
uint32_t ppm_low_mask = (1 << ppm_m )-1;
uint32_t ppm_register =0;
uint16_t ppm_D = 0;
uint16_t ppm_counter = 0;


int print_uint128(uint128 n){
	if(n==0)
		return printf("0\n");
	char str[40] = {0};
	char *s = str + sizeof(str) -1;
	while(n != 0){
		if (s ==str)
			return -1;
		*--s ="0123456789"[n%10];
		n /= 10;
	}
	return printf("%s\n",s);
}

int itob(uint32 number, char ret[], int ret_len){
	unsigned int index;
	int i=0;
	if(ret_len < N)
		return 0;
	index = 1 << (N-1);
	for(i =0; i < N; i++){
		ret[i] = ((number & index) ==0)? '0':'1';
		index >>=1;
	}
	return 1;
}

void PPM_seed(uint64_t seed){
	R <<= N;
	printf("R: ");
	R -= 33243289;
	print_uint128(R);

	M  <<=  N; 
	M2 <<= NF;

	printf("M:");
	print_uint128(M);
}

uint32_t PPM( )
{
	x0 = (uint32)((R*(M-x0)*x0) >> NF);

	printf("%u\n",x0);

	return x0;

	ppm_register >>= 1;
	ppm_register |= (x0 & 1) << (ppm_m-1);

	if(++ppm_counter > ppm_D){
		ppm_D = ppm_register >> (ppm_m - 6);
		ppm_counter =0;
		//uint32_t ppm_S1 = tmp >> ppm_m;
		//uint32_t ppm_S2 = tmp & ppm_low_mask;
		//ppm_S2 ^= ppm_register;
		x0 ^= ppm_register;
	}
	
	return x0;
}

/*
int generate_binary(){
	uint32 x = x0;
	char buffer[33] = {0};
	FILE *hf = fopen("./nst.dat","w+");
	if(!hf){
		printf("Failed to open file nst.dat.\n");
		return -1;
	}
	init();
	for(int i=0; i< 100; i++)
		x = chaos(x);
	for(int i=0; i < 1050000; i++){
		x = chaos(x);
		if(!itob(x,buffer,N)){
			printf("Bad data.\n");
		}
		fwrite(buffer,N,1,hf);
	}
	fclose(hf);
}

int main(int argc, char **argv){
	/*uint32 x = x0;
	FILE *hf = fopen("./chao.txt","w+");
	if(!hf){
		printf("Failed to open file.\n");
		return -1;
	}
	printf("x0: %u\n", x0);
	init();
	for(int i =0; i< 3000; i++){
		x = chaos(x);
		fprintf(hf,"%u\n",x);
	}

	fclose(hf);
	return 0;*/
//	return generate_binary();
//}
