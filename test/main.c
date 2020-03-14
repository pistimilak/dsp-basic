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
#include "dsp_common.h"
#include "dsp_stat.h"


/* Test cases */
#define TEST_SIG_STATISTIC      1


#define INP_SIG_F32_1K_15K_SIZE         320
extern double InputSignal_f32_1kHz_15kHz[INP_SIG_F32_1K_15K_SIZE];


int create_dat_file(const char *fname, dsp_val_t *data_array, const dsp_size_t size);


int main(void)
{

#if TEST_SIG_STATISTIC
/**
 * @brief Testing Signal statistic
 * test signal: InputSignal_f32_1kHz_15kHz
 * 1. Calculating the mean value
 * 2. Calculating the variance
 * 3. Calculating the standard deviation
 */

dsp_val_t mean = dsp_sig_mean(InputSignal_f32_1kHz_15kHz, INP_SIG_F32_1K_15K_SIZE);
dsp_val_t variance = dsp_sig_variance(InputSignal_f32_1kHz_15kHz, mean, INP_SIG_F32_1K_15K_SIZE);
dsp_val_t std_dev = dsp_sig_std_dev(variance);

printf("Statistic of Input Signal (1kHz and 15 kHz sine components)\n");
printf("-----------------------------------------------------------\n\n");
printf("mean:\t\t%lf\n", mean);
printf("variance:\t\t%lf\n", variance);
printf("standard dev:\t\t%lf\n", std_dev);

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
int create_dat_file(const char *fname, dsp_val_t *data_array, const dsp_size_t size)
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