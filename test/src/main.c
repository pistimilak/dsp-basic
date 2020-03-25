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
#include "dsp_dft.h"
#include "waveforms.h"

#define STR_BUFF_SIZE           1000

/* Test cases */
#define TEST_SIG_STATISTIC      1
#define TEST_CONVOLUTION        1
#define TEST_DFT                1

#define MEM_SLOTS_NUM           6


static inline void check_mem_alloc(void *mem);
void create_dat_file(const char *test_path, const char *rel_path, const dsp_val_t *data_array, const dsp_size_t size);
char *prepare_path(const char *test_path, const char *rel_path);

int main(void)
{

    size_t full_path_len;

    printf("Testing DSP library\n");
    printf("===================\n");
    printf("Developer: Istvan Milak\n\n");
    printf("The software generate the calculation result *.dat files\n");
    printf("You can find the correspondig dat files in test/dat/* dirs with html output and gnuplot scripts\n");
    printf("\n");

    /*Getting full path of executable*/
    char *full_path = (char *) malloc(STR_BUFF_SIZE);
    memset(full_path, 0, STR_BUFF_SIZE);

    full_path_len = readlink("/proc/self/exe", full_path, STR_BUFF_SIZE);
    printf("Full path of executable:\t%s\n", full_path, full_path_len);
    
    /*Getting executable absolut path*/
    char *test_abs_path = (char *) malloc(full_path_len + 1);
    memcpy(test_abs_path, full_path, full_path_len);
    *(test_abs_path + full_path_len) = 0; //terminate

    /*skip the exe file name from string*/
    char *endp = (test_abs_path + full_path_len);
    
    /*step back 2 dir level*/
    int i;
    for(i = 0; i < 2; i++, (i <= 1) ? endp-- : (void)0) 
        while(*endp != '/') endp--; 
    *endp = 0; //terminate

    free(full_path);
    printf("Absolute path of test directory:\t%s\n\n", test_abs_path, strlen(test_abs_path));

//////////////////////////////////////////////////////////////////////////////
#if TEST_SIG_STATISTIC
//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////
#if TEST_CONVOLUTION
//////////////////////////////////////////////////////////////////////////////

    dsp_val_t *conv_output_signal;

    printf("Convolution test\n");
    printf("----------------\n");

    conv_output_signal = (dsp_val_t *)calloc((IMPULSE_RESP_SIZE + INP_SIG_F32_1K_15K_SIZE), sizeof(dsp_val_t));
    check_mem_alloc(conv_output_signal);

    /*Convolution*/
    dsp_convolution(conv_output_signal, (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE, 
                    (dsp_val_t *)Impulse_response, IMPULSE_RESP_SIZE);

    
    /*Create convolution input signal dat file*/
    create_dat_file(test_abs_path, "dat/convolution/conv_input_signal.dat", 
                    (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);


    /*Create convolution impulse response dat file*/
    create_dat_file(test_abs_path, "dat/convolution/conv_impulse_response.dat", 
                    (dsp_val_t *)Impulse_response, IMPULSE_RESP_SIZE);


    /*Create convolution output signal */
    create_dat_file(test_abs_path, "dat/convolution/conv_output_signal.dat", 
                    conv_output_signal, IMPULSE_RESP_SIZE + INP_SIG_F32_1K_15K_SIZE);

    /*Running su*/
    dsp_val_t *running_sum_ouptut_signal = (dsp_val_t *) calloc(INP_SIG_F32_1K_15K_SIZE, sizeof(dsp_val_t));

    check_mem_alloc(running_sum_ouptut_signal);

    /*Running sum algorithm*/
    dsp_running_sum(running_sum_ouptut_signal, (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);

    /*Cerate runing sum input signal*/
    create_dat_file(test_abs_path, "dat/convolution/rsum_input_signal.dat", 
                    (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);


    /*Create running sum output signal*/
    create_dat_file(test_abs_path, "dat/convolution/rsum_output_signal.dat", 
                    (dsp_val_t *)running_sum_ouptut_signal, INP_SIG_F32_1K_15K_SIZE);

    free(running_sum_ouptut_signal);
    
    printf("\n");

#endif

//////////////////////////////////////////////////////////////////////////////
#if TEST_DFT
//////////////////////////////////////////////////////////////////////////////
    printf("Discrete Fourier transformation test\n");
    printf("------------------------------------\n");

    /*dft_output_rex*/
    dsp_val_t *dft_output_rex = (dsp_val_t *) calloc(INP_SIG_F32_1K_15K_SIZE / 2, sizeof(dsp_val_t));
    check_mem_alloc(dft_output_rex);

    /*dft_output_imx*/
    dsp_val_t *dft_output_imx = (dsp_val_t *) calloc(INP_SIG_F32_1K_15K_SIZE / 2, sizeof(dsp_val_t));
    check_mem_alloc(dft_output_imx);


    /*idft output signal*/
    dsp_val_t *idft_output_signal = (dsp_val_t *) calloc(INP_SIG_F32_1K_15K_SIZE, sizeof(dsp_val_t));
    check_mem_alloc(idft_output_signal);

    /*Discrete fourier transform*/
    dsp_dft((dsp_val_t *)InputSignal_f32_1kHz_15kHz, dft_output_rex, dft_output_imx, INP_SIG_F32_1K_15K_SIZE);
    

    /*Cerate  DFT input signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_input_signal.dat", 
                    (dsp_val_t *)InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);

    /*Cerate  DFT output rex signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_output_rex.dat", 
                    dft_output_rex, INP_SIG_F32_1K_15K_SIZE / 2);

    /*Cerate  DFT output imx signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_output_imx.dat", 
                    dft_output_imx, INP_SIG_F32_1K_15K_SIZE / 2);

    /*Regenerate the original signal with IDFT*/
    dsp_idft(idft_output_signal, dft_output_rex, dft_output_imx, INP_SIG_F32_1K_15K_SIZE);

    /*Cerate  DFT input signal*/
    create_dat_file(test_abs_path, "/dat/dft/idft_output_signal.dat", 
                    idft_output_signal, INP_SIG_F32_1K_15K_SIZE);

    printf("\n");
    free(dft_output_rex);
    free(dft_output_imx);
    free(idft_output_signal);

    /*ECG signal*/
    /*dft_ecg_output_rex*/
    dsp_val_t *dft_ecg_output_rex = (dsp_val_t *) calloc(ECG_SIGNAL_SIZE / 2, sizeof(dsp_val_t));
    check_mem_alloc(dft_ecg_output_rex);

    /*dft_output_imx*/
    dsp_val_t *dft_ecg_output_imx = (dsp_val_t *) calloc(ECG_SIGNAL_SIZE / 2, sizeof(dsp_val_t));
    check_mem_alloc(dft_ecg_output_imx);


    /*idft output signal*/
    dsp_val_t *idft_ecg_output_signal = (dsp_val_t *) calloc(ECG_SIGNAL_SIZE, sizeof(dsp_val_t));
    check_mem_alloc(idft_ecg_output_signal);

    /*Discrete fourier transform*/
    dsp_dft((dsp_val_t *)ECG_signal, dft_ecg_output_rex, dft_ecg_output_imx, ECG_SIGNAL_SIZE);
    

    /*Cerate  DFT input signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_ecg_input_signal.dat", 
                    (dsp_val_t *)ECG_signal, ECG_SIGNAL_SIZE);

    /*Cerate  DFT output rex signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_ecg_output_rex.dat", 
                    dft_ecg_output_rex, ECG_SIGNAL_SIZE / 2);

    /*Cerate  DFT output imx signal*/
    create_dat_file(test_abs_path, "dat/dft/dft_ecg_output_imx.dat", 
                    dft_ecg_output_imx, ECG_SIGNAL_SIZE / 2);

    /*Regenerate the original signal with IDFT*/
    dsp_idft(idft_ecg_output_signal, dft_ecg_output_rex, dft_ecg_output_imx, ECG_SIGNAL_SIZE);

    /*Cerate  DFT input signal*/
    create_dat_file(test_abs_path, "/dat/dft/idft_ecg_output_signal.dat", 
                    idft_ecg_output_signal, ECG_SIGNAL_SIZE);

    free(dft_ecg_output_rex);
    free(dft_ecg_output_imx);
    free(idft_ecg_output_signal);

#endif

    return 0;
}


/**
 * @brief Create a dat file from array to test with GNU Plot
 * 
 * @param test_path test absoulute path
 * @param rel_path relative path in test directory
 * @param data_array data array
 * @param size size of data array
 */
void create_dat_file(const char *test_path, const char *rel_path, const dsp_val_t *data_array, const dsp_size_t size)
{
    FILE *fd;
    
    char *path = prepare_path(test_path, rel_path);
    

    check_mem_alloc(path);

    fd = fopen(path, "w+");

    /*Error during opening the file*/
    if (fd == NULL) {
        fprintf(stderr, "An error occured in file creation: %s\n", path);
        exit(EXIT_FAILURE);
    }
        
    dsp_size_t i;
    for (i = 0; i < size; fprintf(fd, "\n%f", *(data_array + i)), i++);

    fprintf(stdout, "%s created. (%d elements)\n", path, size);
    
    fclose(fd);
    free(path);
}

static inline void check_mem_alloc(void *mem) 
{
    if(mem == NULL) {
        fprintf(stderr, "Memmory allocation error!\n");
        exit(EXIT_FAILURE);
    }
}

char *prepare_path(const char *test_path, const char *rel_path)
{
    int len_test_path = strlen(test_path);
    int len_rel_path = strlen(rel_path); 
    
    char *path = malloc(len_test_path + len_rel_path + 2);
    
    strcpy(path, test_path);
    *(path + len_test_path) = '/';
    strcpy(path + len_test_path + 1, rel_path);
    
    return path;
}