/**
 * @file convolution.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Convolution
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#ifndef __DSP_CONVOLUTION_H__
#define __DSP_CONVOLUTION_H__

#include "dsp_common.h"

/**
 * @brief DSP Convolution
 * 
 * @param dest_sig destination output array
 * @param input_sig input signal array
 * @param input_sig_len input signal length
 * @param impulse_resp impulse response signal array
 * @param impulse_resp_len impulse response signal length
 */
void dsp_convolution(dsp_val_t *dest_sig, dsp_val_t *input_sig, dsp_len_t input_sig_len, 
                dsp_val_t *impulse_resp, dsp_len_t impulse_resp_len);


#endif