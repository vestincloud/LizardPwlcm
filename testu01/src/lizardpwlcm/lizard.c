#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "lizard.h"
#include <time.h>

/*
 * Input formats must be 120 bit key as 30 hex values and 64 bit IV as 16 hex values.
 * The keystream output length can be chosen between 1 bit and 10000 bits.
 */


uint32_t K[120];
uint32_t IV[64];
uint32_t z=0;
uint8_t L=0;
uint8_t Q=0;
uint8_t T=0;
uint8_t Ttilde=0;
uint8_t B[2][90];
uint8_t S[2][31];
uint8_t a257 = 0;
int t = 0;
int t_next = 1;
uint8_t keystream[KEYSTREAM_SIZE];
char strkeystream[KEYSTREAM_SIZE+1];

uint8_t EXTRA_FB =0;

void _construct(uint8_t  *key, uint8_t *iv){
    strkeystream[KEYSTREAM_SIZE]=0;
    _initialization(key, iv);
}

void _initialization(uint8_t *key, uint8_t *iv){

    //Phase 1
    loadkey(key);
    loadIV(iv);
    initRegisters();

    //Phase 2
    for(int i=0;i<=127; i++){
        mixing();
	t_next =t;
	t = t^1;
    }

    //Phase 3
    keyadd();
    t_next = t;
    t = t^1;

    //Phase 4
    for(int i=0; i<128; i++){
        diffusion();
	t_next = t;
	t = t^1;
    }

}

void loadkey(uint8_t *key){

    for (int i = 0; i <= 119; ++i){
        K[i] = key[i];
    }
}

void loadIV(uint8_t *iv){
    for (int i = 0; i <= 63; ++i){
        IV[i] = iv[i];
    }
}

void initRegisters(){

    for(int i = 0; i <=63; ++i){
        B[0][i] = K[i]^IV[i];
    }

    for(int i = 64; i<=89; ++i){
        B[0][i] = K[i];
    }

    for(int i = 0; i <=28; ++i){
        S[0][i] = K[i+90];
    }

    S[0][29] = K[119] ^ (uint8_t )1;
    S[0][30] = 1;
}

void mixing(){

    z = a();
    for(int i = 0; i<=88; ++i) {
        B[t_next][i] = B[t][i + 1];
    }

    B[t_next][89] = z ^ NFSR2();

    for(int i = 0; i <= 29; ++i){
        S[t_next][i] = S[t][i+1];
    }
    S[t_next][30] = z ^ NFSR1();
}

uint8_t a(){

    L = B[t][7]  ^ B[t][11] ^ \
             B[t][30] ^ B[t][40] ^ \
             B[t][45] ^ B[t][54] ^ \
             B[t][71];

    Q = B[t][4]  * B[t][21] ^ \
           B[t][9]  * B[t][52] ^ \
           B[t][18] * B[t][37] ^ \
           B[t][44] * B[t][76];

    T = B[t][5]  ^ B[t][8]  * \
           B[t][82] ^ B[t][34] * \
           B[t][67] * B[t][73] ^ \
           B[t][2]  * B[t][28] * \
           B[t][41] * B[t][65] ^ \
           B[t][13] * B[t][29] * \
           B[t][50] * B[t][64] * \
           B[t][75] ^ B[t][6]  * \
           B[t][14] * B[t][26] * \
           B[t][32] * B[t][47] * \
           B[t][61] ^ B[t][1]  * \
           B[t][19] * B[t][27] * \
           B[t][43] * B[t][57] * \
           B[t][66] * B[t][78];

    Ttilde = S[t][23] ^ S[t][3]  * \
                S[t][16] ^ S[t][9]  * \
                S[t][13] * B[t][48] ^ \
                S[t][1]  * S[t][24] * \
                B[t][38] * B[t][63];

    return L ^ Q ^ T ^ Ttilde;
}

uint8_t NFSR2(){

    return \
    S[t][0]  ^ B[t][0]  ^ \
    B[t][24] ^ B[t][49] ^ \
    B[t][79] ^ B[t][84] ^ \
    B[t][3]  * B[t][59] ^ \
    B[t][10] * B[t][12] ^ \
    B[t][15] * B[t][16] ^ \
    B[t][25] * B[t][53] ^ \
    B[t][35] * B[t][42] ^ \
    B[t][55] * B[t][58] ^ \
    B[t][60] * B[t][74] ^ \
    B[t][20] * B[t][22] * \
    B[t][23] ^ B[t][62] * \
    B[t][68] * B[t][72] ^ \
    B[t][77] * B[t][80] * \
    B[t][81] * B[t][83];
}

uint8_t NFSR1(){

    return \
    EXTRA_FB ^ \
    S[t][0]  ^ S[t][2]  ^ \
    S[t][5]  ^ S[t][6]  ^ \
    S[t][15] ^ S[t][17] ^ \
    S[t][18] ^ S[t][20] ^ \
    S[t][25] ^ S[t][8]  * \
    S[t][18] ^ S[t][8]  * \
    S[t][20] ^ S[t][12] * \
    S[t][21] ^ S[t][14] * \
    S[t][19] ^ S[t][17] * \
    S[t][21] ^ S[t][20] * \
    S[t][22] ^ S[t][4]  * \
    S[t][12] * S[t][22] ^ \
    S[t][4]  * S[t][19] * \
    S[t][22] ^ S[t][7]  * \
    S[t][20] * S[t][21] ^ \
    S[t][8]  * S[t][18] * \
    S[t][22] ^ S[t][8]  * \
    S[t][20] * S[t][22] ^ \
    S[t][12] * S[t][19] * \
    S[t][22] ^ S[t][20] * \
    S[t][21] * S[t][22] ^ \
    S[t][4]  * S[t][7]  * \
    S[t][12] * S[t][21] ^ \
    S[t][4]  * S[t][7]  * \
    S[t][19] * S[t][21] ^ \
    S[t][4]  * S[t][12] * \
    S[t][21] * S[t][22] ^ \
    S[t][4]  * S[t][19] * \
    S[t][21] * S[t][22] ^ \
    S[t][7]  * S[t][8]  * \
    S[t][18] * S[t][21] ^ \
    S[t][7]  * S[t][8]  * \
    S[t][20] * S[t][21] ^ \
    S[t][7]  * S[t][12] * \
    S[t][19] * S[t][21] ^ \
    S[t][8]  * S[t][18] * \
    S[t][21] * S[t][22] ^ \
    S[t][8]  * S[t][20] * \
    S[t][21] * S[t][22] ^ \
    S[t][12] * S[t][19] * \
    S[t][21] * S[t][22];
}


void keyadd(){

    for(int i = 0; i <= 89; ++i){
        B[t_next][i] = (uint8_t) (B[t][i] ^ K[i]);
    }

    for(int i = 0; i <= 29; ++i){
        S[t_next][i] = S[t][i] ^ K[i+90];
    }

    S[t_next][30] = 1;
}

void diffusion(){

    for(int i = 0; i <= 88; ++i){
        B[t_next][i] = B[t][i+1];
    }

    B[t_next][89] = NFSR2();

    for(int i = 0; i <= 29; ++i){
        S[t_next][i] = S[t][i+1];
    }

    S[t_next][30] = NFSR1();

}

uint8_t step(){
	uint8_t res = a();
	diffusion();
	t_next =t;
	t = t^1;
	return res;
}

void keysteamGeneration(int length){

    for(int i = 0 ; i <KEYSTREAM_SIZE; ++i){
        keystream[i] = 0;
    }

    for(int i = 0; i < length; ++i){
        keystream[i] = a();
        diffusion();
        t_next = t;
	t = t^1;
    }
}


uint8_t* getKeystream(){
    return keystream;
}

void extra_feedback(uint8_t value){
	EXTRA_FB = value;
}
