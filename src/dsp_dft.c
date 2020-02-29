/**
 * @file dsp_dft.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Discrete Fourier Transform
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "dsp_dft.h"


/**
 * @brief Calculate Discrete Fourier transform
 * Decomposing singnal to sine and cosin waves
 *                        
 *                              Re X[]
 *                        +---> N/2 + 1 cosine wave amplitudes
 *                        |
 * N point input -> DFT ->+ 
 *                        |     Im X[]
 *                        +---> N/2 + 1 sine wave amplitudes
 * 
 *    (Time domain)                    (Frequency domain)
 * 
 * A set of sine and cosine waves with unity amplitude
 * 		ck[i] = cos((2 * PI * k *i) / N)
 * 		sk[i] = sin((2 * PI * k *i) / N)
 * 
 * @param input_sig input signal source array
 * @param dest_rex destination rex array
 * @param dest_imx destination imx array
 * @param input_sig_len length of input signal
 */
void dsp_dft(dsp_val_t *input_sig, dsp_val_t *dest_rex,  dsp_val_t *dest_imx, dsp_size_t input_sig_len)
{
    dsp_size_t i, j, k;

    // rest dest arrays
    for(j = 0; j < (input_sig_len / 2); *(dest_rex + j) = *(dest_imx + j) = 0.0, j++);

    // calc re and im arrays as result
    for(k = 0; k < (input_sig_len / 2); k++) {
        for(i = 0; i < input_sig_len; i++) {
            *(dest_rex + k) += *(input_sig + i) * cos(2 * M_PI * k *i / input_sig_len);
            *(dest_imx + k) -= *(input_sig + i) * sin(2 * M_PI * k *i / input_sig_len);
        }
    }
}

/**
 * @brief Calculate the Inverse Discrete Fourier Transform
 * Synthesing sine and cosine waves to one signal
 * 		Re negX[k] = Re X[k] / N / 2 Except k = 0 then Re X[k] / N
 * 		Im negX[k] = Im X[k] / N / 2 Except k = 0 then Re X[k] / N
 * @param dest_sig destination output signal array
 * @param input_rex input rex signal array 
 * @param input_imx input imx signal array
 * @param idft_len length of original time domain signal length
 */
void dsp_idft(dsp_val_t *dest_sig, dsp_val_t *input_rex,  dsp_val_t *input_imx, dsp_size_t idft_len)
{
    dsp_size_t i, k;
     
    // prepare input rex and imx
    // exception at zero index
    *input_rex /=  2.0;
    *input_imx /= -2.0; 

    for(k = 1; k < idft_len / 2; k++) {
        *(input_rex + k) /= ((dsp_val_t)idft_len / 2.0);
        *(input_imx + k) /= -1.0 * ((dsp_val_t)idft_len / 2.0);
    }

    // reset destination array
    for(i = 0; i < idft_len; *(dest_sig + i) = 0.0, i++);

    // calc output signal
    for(k = 0; k < idft_len; k++) {
        for(i = 0; i < idft_len; i++) {
            *(dest_sig + i) += input_rex[k] * cos(2 * M_PI * k * i / idft_len);
            *(dest_sig + i) += input_imx[k] * sin(2 * M_PI * k * i / idft_len);
        }
    }
}