/**
 * @file main.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief Test cases implementation. 
 * @version 0.1
 * @date 2020-03-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "dsp_common.h"
#include "dsp_stat.h"
#include "dsp_convolution.h"
#include "waveforms.h"

#define STR_BUFF_SIZE           1000

/* Test cases */
#define TEST_SIG_STATISTIC      1
#define TEST_CONVOLUTION        1
#define TEST_RUNING_SUM         1

int create_dat_file(const char *fname, const dsp_val_t *data_array, const dsp_size_t size);


int main(void)
{

    size_t full_path_len;
    
    /*Getting full path of executable*/
    char *full_path = (char *) malloc(STR_BUFF_SIZE);
    memset(full_path, 0, STR_BUFF_SIZE);

    full_path_len = readlink("/proc/self/exe", full_path, STR_BUFF_SIZE);
    printf("Full path of executable:\t%s (len: %d)\n", full_path, full_path_len);
    
    /*Getting executable absolut path*/
    char *exe_abs_path = (char *) malloc(full_path_len + 1);
    memset(exe_abs_path, 0, full_path_len + 1);
    char *res_p = realpath(full_path, exe_abs_path);

    free(full_path);

    if (res_p == NULL) {
        fprintf(stderr, "Absolute path of executable is not defined\n");
        free(exe_abs_path);
        return 1;
    } else {
        printf("Absolute path of executable:\t%s (len: %d)\n", exe_abs_path, strlen(exe_abs_path));
    }


#if TEST_SIG_STATISTIC
/**
 * @brief Testing Signal statistic
 * test signal: InputSignal_f32_1kHz_15kHz
 * 1. Calculating the mean value
 * 2. Calculating the variance
 * 3. Calculating the standard deviation
 */

    dsp_val_t mean = dsp_sig_mean((dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);
    dsp_val_t variance = dsp_sig_variance((dsp_val_t *)InputSignal_f32_1kHz_15kHz, mean, INP_SIG_F32_1K_15K_SIZE);
    dsp_val_t std_dev = dsp_sig_std_dev(variance);

    printf("Statistic of Input Signal (1kHz and 15 kHz sine components)\n");
    printf("-----------------------------------------------------------\n");
    printf("mean:          %lf\n", mean);
    printf("variance:      %lf\n", variance);
    printf("standard dev:  %lf\n\n", std_dev);

#endif

#if TEST_CONVOLUTION



    dsp_val_t conv_output_signal[IMPULSE_RESP_SIZE + INP_SIG_F32_1K_15K_SIZE];

    printf("Convolution test\n");
    printf("----------------\n\n");

    /*Convolution*/
    dsp_convolution(conv_output_signal, 
                    (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE, 
                    (dsp_val_t *)Impulse_response, IMPULSE_RESP_SIZE);

    
    /*Create convolution input signal dat file*/
    if(!create_dat_file("../dat/convolution/conv_input_signal.dat", (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE)) { 
        fprintf(stderr, "An error occured in ../dat/convolution/conv_input_signal.dat file creation\n");
        return 1;
    } else {
        printf("../dat/convolution/conv_input_signal.dat created\n");
    }


    /*Create convolution impulse response dat file*/
    if(!create_dat_file("../dat/convolution/conv_impulse_response.dat", (dsp_val_t *)Impulse_response, IMPULSE_RESP_SIZE)){ 
        fprintf(stderr, "An error occured in ../dat/convolution/conv_impulse_response.dat file creation\n");
        return 1;
    } else {
        printf("../dat/convolution/conv_impulse_response.dat created\n");
    }


    /*Create convolution output signal */
    if(!create_dat_file("../dat/convolution/conv_output_signal.dat", (dsp_val_t *)conv_output_signal, IMPULSE_RESP_SIZE + INP_SIG_F32_1K_15K_SIZE)) {
        fprintf(stderr, "An error occured in ../dat/convolution/conv_output_signal.dat file creation\n");
        return 1;
    } else {
        printf("../dat/convolution/conv_output_signal.dat created\n");
    }


    dsp_val_t running_sum_ouptut_signal[INP_SIG_F32_1K_15K_SIZE];

    /*Running sum algorithm*/
    dsp_running_sum(running_sum_ouptut_signal, (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);

    /*Cerate runing sum input signal*/
    if(!create_dat_file("../dat/convolution/rsum_input_signal.dat", (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE)) { 
        fprintf(stderr, "An error occured in ../dat/convolution/rsum_input_signal.dat file creation\n");
        return 1;
    } else {
        printf("../dat/convolution/rsum_input_signal.dat created\n");
    }

    /*Create running sum output signal*/
    if(!create_dat_file("../dat/convolution/rsum_output_signal.dat", running_sum_ouptut_signal, INP_SIG_F32_1K_15K_SIZE)){ 
        fprintf(stderr, "An error occured in ../dat/convolution/rsum_output_signal.dat file creation\n");
        return 1;
    } else {
        printf("../dat/convolution/rsum_output_signal.dat created\n");
    }

#endif


    return 0;
}


/**
 * @brief Create a dat file from array to test with GNU Plot
 * 
 * @param fname file name
 * @param data_array data array
 * @param size size of data array
 * @return int result of creation, 0 if an error, otherwise the size of array
 */
int create_dat_file(const char *fname, const dsp_val_t *data_array, const dsp_size_t size)
{
    FILE *fd =  fopen(fname, "w+");
    
    /*Error during opening the file*/
    if (fd == NULL)
        return 0;

    dsp_size_t i;
    for (i = 0; i < size; fprintf(fd, "\n%f", *(data_array + i)), i++);

    fclose(fd);
    // return with the printed data
    return size;
}