/**
 * @file dsp_cdft.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief Complex Discrete Fourier Transform
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "dsp_cdft.h"

/**
 * @brief Complex Discrete Fourier Transform
 * 
 * Euler relations
 * exp(j * x) = cos(x) + j * sin(x)
 * cos(x) = (exp(j * x) + exp(-j * x)) / 2
 * sin(x) = (exp(j * x) + exp(-j * x)) / 2
 * 
 * cos(omega * t) = exp(-j * omega * t) / 2 + exp(j * omega * t) / 2
 * sin(omega * t) = exp(-j * omega * t) / 2 + exp(j * omega * t) / 2
 * 
 * Complex DFT
 * ------------
 * 
 * X[k] = 1/N * sum (x[n] * exp(-j * 2 * k * PI * n / N)) | from n = 0 to n = N - 1
 * 
 * X[k] = 1/N * sum (x[n] * (cos(2 * PI * k * n / N) - j * sin(2 * PI * k * n / N))) | from n = 0 to n = N - 1
 * 
 * Inverse Complex DFT
 * -------------------
 * X[k] = (1 / N) * sum (x[n] * exp(j * 2 * k * PI * n / N))
 * 
 * @param input_sig_tdomain_rex input time domain signal real part
 * @param input_sig_tdomain_imx input time domain signal imaginary part
 * @param output_sig_fdomain_rex output frequency domain signal real part
 * @param output_sig_fdomain_imx output frequency domain signal imaginary part
 * @param sig_len signal length
 */
void dsp_cdft(dsp_val_t *input_sig_tdomain_rex, dsp_val_t *input_sig_tdomain_imx, 
              dsp_val_t *output_sig_fdomain_rex, dsp_val_t *output_sig_fdomain_imx, dsp_size_t sig_len)
{
    dsp_size_t k, i;
    dsp_val_t SR, SI, sin_cos_arg;
    
    for(k = 0; k < sig_len, *(output_sig_fdomain_imx + k) = *(output_sig_fdomain_rex + k) = 0; k++) {
        
        for(i = 0; i < sig_len; i++) {

            // calculate common argument for sin and cos
            sin_cos_arg = 2 * M_PI * k * i / sig_len;

            // calculate real and imaginary coefficients
            SR = cos(sin_cos_arg);
            SI = -sin(sin_cos_arg);

            // calculate output
            *(output_sig_fdomain_rex + k) += *(input_sig_tdomain_rex + i) * SR - *(input_sig_tdomain_imx + i) * SI;
            *(output_sig_fdomain_imx + k) += *(input_sig_tdomain_imx + i) * SI - *(input_sig_tdomain_imx + i) * SR;
        }
    }
}