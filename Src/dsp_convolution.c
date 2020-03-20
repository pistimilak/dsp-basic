/**
 * @file convolution.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Convolution
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "dsp_convolution.h"

/**
 * @brief DSP Convolution
 * 
 * @param dest_sig destination output array
 * @param input_sig input signal array
 * @param input_sig_len input signal length
 * @param impulse_resp impulse response signal array
 * @param impulse_resp_len impulse response signal length
 */
void dsp_convolution(dsp_val_t *dest_sig, dsp_val_t *input_sig, dsp_size_t input_sig_len, 
                dsp_val_t *impulse_resp, dsp_size_t impulse_resp_len)
{
    dsp_size_t i, j;

    // reset destination array
    for(i = 0; i < (input_sig_len + impulse_resp_len); *(dest_sig + i) = 0.0, i++);

    // calc convolution sum
    for(i = 0; i < input_sig_len; i++) {
        for(j = 0; j < impulse_resp_len; j++) {
            *(dest_sig + i + j) += *(input_sig + i) * *(impulse_resp + j); 
        }
    }
}

/**
 * @brief Calculate running sum
 * 
 * @param dest_sig destination signal array
 * @param input_sig input source signal array
 * @param input_sig_len input signal length
 */
void dsp_running_sum(dsp_val_t *dest_sig,  dsp_val_t *input_sig, dsp_size_t input_sig_len)
{
    dsp_size_t i;

    for(i = 1, *dest_sig = *input_sig; i < input_sig_len; i++) {
        *(dest_sig + i) += *(input_sig + i - 1);
    }
}