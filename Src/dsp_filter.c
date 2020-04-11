/**
 * @file dsp_filter.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP filter function
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "dsp_filter.h"

void dsp_lp_win_sinc_filter(dsp_val_t *output_filter, dsp_val_t cutoff_freq, dsp_size_t filter_len)
{
    dsp_size_t i;
    dsp_val_t tmp1;
    for(i = 0; i < filter_len; i++) {
        if(i == filter_len / 2) {
            *(output_filter + i)  = 2 * M_PI * cutoff_freq; 
        } else {
            tmp1 = (i - filter_len / 2);
            *(output_filter + i) = sin(2 * M_PI * cutoff_freq * tmp1) / tmp1;
            *(output_filter + i) *= 0.54 - 0.46 * cos(2 * M_PI * i / filter_len);
        }
    }

}dsp