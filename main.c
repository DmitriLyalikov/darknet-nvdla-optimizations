#include "converter_layer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void printBufferContents(const int *out_int, size_t bufsize) {
    for (size_t i = 0; i < bufsize; i++) {
        printf("%d ", out_int[i]);
    }
    printf("\n");
}

void printBufferContentsFloat(const float *out_int, size_t bufsize) {
    for (size_t i = 0; i < bufsize; i++) {
        printf("%f ", out_int[i]);
    }
    printf("\n");
}


void initializeBuffer(float *buffer, size_t bufsize) {
    // You can put your desired initialization logic here.
    // For example, filling the buffer with consecutive numbers:
    for (size_t i = 0; i < bufsize; i++) {
        buffer[i] = (float)i;
    }
}

int main(void)
{
    int bufsize = 416 * 416 * roundup_and_align(32, 32);
    printf("%d\n\r", bufsize);
    float *in_fp32 = calloc(bufsize, sizeof(float));
    initializeBuffer(in_fp32, bufsize);
    // printBufferContentsFloat(in_fp32, bufsize);
    int *in_int = calloc(bufsize, sizeof(int));
    float *out_fp32 = calloc(bufsize, sizeof(float));
    int *out_int = calloc(bufsize, sizeof(int));

    int fp_conv = 1;

    forward_converter_layer(fp_conv, in_int, in_fp32, out_fp32, out_int);
    printBufferContents(out_int, bufsize);
    printf("We got here\n\r");
    return 0;
}