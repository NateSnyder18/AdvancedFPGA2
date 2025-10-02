#include "stdio.h"
#include "block_fir.h"

const int SIZE = 256;

void block_fir(int input[256], int output[256], int taps[NUM_TAPS], int delay_line[NUM_TAPS]){
    #pragma HLS ARRAY_PARTITION variable=taps complete dim=1
    #pragma HLS ARRAY_PARTITION variable=delay_line complete dim=1
    int i, j;
    for (j=0; j<256; j++){
        int result = 0;
        for (i=NUM_TAPS-1; i>0; i--){
            #pragma HLS PIPELINE
            //#pragma HLS UNROLL
            delay_line[i] = delay_line[i-1];
        }
        delay_line[0] = input[j];

        for (i=0; i<NUM_TAPS; i++){
            #pragma HLS PIPELINE
            //#pragma HLS UNROLL
            result += delay_line[i] * taps[i];
        }
        output[j] = result;
    }
}