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

    // calc re and im arrays as result
    for(k = 0, *(dest_rex + k) = *(dest_imx + k) = 0; 
        k < (input_sig_len / 2); k++) {
        
        for(i = 0; i < input_sig_len; i++) {
            *(dest_rex + k) += *(input_sig + i) * cos(2.0 * M_PI * k *i / input_sig_len);
            *(dest_imx + k) -= *(input_sig + i) * sin(2.0 * M_PI * k *i / input_sig_len);
        }
    }
}

/**
 * @brief Calculate the Inverse Discrete Fourier Transform
 * Synthesing sine and cosine waves to one signal
 * 		Re negX[k] = Re X[k] / N / 2 Except k = 0 then Re X[k] / N
 * 		Im negX[k] = Im X[k] / N / 2 Except k = 0 then Re X[k] / N
 * 
 * @param dest_sig destination output signal array
 * @param input_rex input rex signal array 
 * @param input_imx input imx signal array
 * @param idft_len length of original time domain signal length
 */
void dsp_idft(dsp_val_t *dest_sig, dsp_val_t *input_rex,  dsp_val_t *input_imx, dsp_size_t idft_len)
{
    dsp_size_t i, k;
    dsp_val_t div_rex, div_imx; // dividers
    dsp_val_t rex, imx;
 
    // reset destination array
    for(i = 0; i < idft_len; *(dest_sig + i) = 0.0, i++);

    // calc output signal
    for(k = 0, div_rex = ((dsp_val_t)idft_len / 2.0), div_imx = -1.0 * ((dsp_val_t)idft_len / 2.0); 
        k < idft_len / 2; k++) {
        
        // prepare input rex and imx
        rex = *(input_rex + k) / div_rex;
        imx = *(input_imx + k) / div_imx;

        // exception at zero index
        if(!k) {
            rex /= 2.0;
            imx /= -2.0;
        }

        // Calculate output signal
        for(i = 0; i < idft_len; i++) {
            *(dest_sig + i) += rex * cos(2.0 * M_PI * k * i / idft_len);
            *(dest_sig + i) += imx * sin(2.0 * M_PI * k * i / idft_len);
        }
    }
}


/**
 * @brief Calculate Discrete Fourier Transform magnitude signal from rex and imx
 * Absoulet value of complex number for each point.
 * 
 * @param dest_mag destination signal
 * @param rex real part array
 * @param imx imaginary part array
 * @param mag_len length of magnitude
 */
void dsp_dft_magnitude(dsp_val_t *dest_mag, dsp_val_t *rex, dsp_val_t *imx, dsp_size_t mag_len)
{
    dsp_size_t i;

    for(i = 0; i < mag_len; i++) {
        *(dest_mag + i) = sqrt( pow(*(rex + i), 2) + pow(*(imx + i), 2) );
    }
}

/**
 * @brief Convert Rectangle notation to Polar notation
 * Rectengular notation:
 * Re X[k] , Im X [k]
 * 
 * Polar Notation:
 * Mag X[k], Phase X[k]
 * M = sqrt( pow(A, 2), pow(B, 2) )
 * Theta = arctan(B/A)
 * 
 * Rectengular to Polar conversion
 * Mag[k] = sqrt( pow(ReX[k], 2), pow(ImX[k], 2) )
 * Phase[k] = arctan(ImX[k] / ReX[k])
 * 
 * ReX[k] = MagX[k] * cos(PhaseX[k])
 * ImX[k] = MagX[k] * sin(PhaseX[k])
 * 
 * @param mag_output magnitude output destination array
 * @param phase_output phase output destination array
 * @param rex_input ReX input signal array
 * @param imx_input ImX input signal arrau
 * @param sig_len Length of ReX and Imx
 */
void dsp_rect2polar(dsp_val_t *mag_output, dsp_val_t *phase_output,
                    dsp_val_t *rex_input, dsp_val_t *imx_input, 
                    dsp_size_t sig_len)
{
    dsp_size_t k;

    for(k = 0; k < sig_len; k++) {
        // magnitude
        *(mag_output + k) = sqrt( pow(*(rex_input + k), 2) + pow(*(imx_input + k), 2) );
        
        // phase rules
        if(*(rex_input + k) == 0) {
            *(rex_input + k) = pow(10, -20);
            *(phase_output +k) = atan(*(imx_input + k) / *(rex_input + k));
        }
        
        if(*(rex_input + k) < 0 && *(imx_input + k) < 0) {
            *(phase_output + k) -= M_PI;
        }

        if(*(rex_input + k) < 0 && *(imx_input + k) >= 0) {
            *(phase_output + k) += M_PI;
        }
    }
}