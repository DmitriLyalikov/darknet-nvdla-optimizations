#include "converter_layer.h"
#include "converter.h"
#include <stdlib.h>
#include <stdio.h>


unsigned int roundup_and_align(unsigned int val, unsigned int round_to)
{
    unsigned int rounded;

    if (val % round_to != 0) {
        rounded = val + round_to - (val % round_to);
    } else {
        rounded = val;
    }

    return rounded;
}

void convert_nchw_to_nhwc(int *in, int w, int h, int c, int *out)
{
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                out[j*w*c + c*k + i] = in[w*h*i + w*j + k];
            }
        }
    }
}

void convert_fd_to_nchw(float *in, int w, int h, int c, float *out)
{
    unsigned int line_stride = w * 32;
    unsigned int surface_stride = line_stride * h;

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                int surface_index = i/32;
                out[w*h*i + w*j + k] = in[surface_stride*surface_index + line_stride*j + 32*k + i%32];
            }
        }
    }
}


void forward_converter_layer(int conv_type, int *in_int8, float *in_fp32, int *out_int, float *out_fp32)
{
    /* Make a call to precision converter */
    unsigned count = 416*416*32;
    unsigned int bufsize = 416 * 416 * roundup_and_align(32, 32);

    if (conv_type == 1) {
#if 1
        int *temp = calloc(bufsize, sizeof(int));
        printf("Got here/n/r");
        fp32_to_uint8(in_fp32, temp, count);
        //odla_dump_image_data(temp, l.w, l.h, l.c);
        convert_nchw_to_nhwc(temp, 416, 416, 3, (int*)out_int);
        free(temp);
#endif
        //reference data for validation
//        memcpy((uint8_t *)l.output_i8, reshaped_data, 692224);
    } else 
    {
        float *temp = calloc(bufsize, sizeof(float));
        int8_to_fp32(in_int8, temp, count);
        convert_fd_to_nchw(temp, 416, 416, 3, out_fp32);
        free(temp);
    }
}