/**
 * @file dsp_filter.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP filter function
 * @version 0.1
 * @date 2020-04-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DSP_FILTER_H__
#define __DSP_FILTER_H__

#include "dsp_common.h"

/**
 * @brief Create low-pass windowed sinc filter
 * Cutoff frequency must be between 0.0 and 0.5
 * sinc function:
 *      h[i] = sin(2 * PI * fc * i) / (i * PI)
 * After applying sinc function, window calculation is also applied. if the function pointer is NULL,
 * Hamming window is the default
 * 
 * 
 * Example calculation of cutoff:
 * You have to know the sample frequency of the input signal what you have to filter, for example 48kHz
 * Nyquist frequency is 24kHz.
 * 24kHz => 0.5
 * expcted 10kHz:
 * 10 kHz => (10kHz/ 24kHz) * 0.5
 * 
 * Filter len calculation:
 * M ~= 4 / BW => 
 * BW: is the transition band width, transition band is the frequencies between passband and stopband 
 * M: length of filer kernel, approximation
 * 
 * @param output_filter filter output result
 * @param input_sample_freq_khz known filterable signal sample frequency in kHz 
 * @param cutoff_freq_khz  cutoff frequency in kHz
 * @param window_calc window calculation function for given index. int argument: index of filter, dsp_size_t argument: size of filter
 * @param filter_len filter len
 */
void dsp_lp_win_sinc_filter(dsp_val_t *output_filter, dsp_val_t input_sample_freq_khz, dsp_val_t cutoff_freq_khz,
                            dsp_val_t (*window_calc)(int, dsp_size_t), dsp_size_t filter_len);



/**
 * @brief Create band-pass windowed sinc filter
 * Cutoff frequency must be between 0.0 and 0.5
 * sinc function:
 *      h[i] = sin(2 * PI * fc * i) / (i * PI)
 * After applying sinc function, window calculation is also applied. if the function pointer is NULL,
 * Hamming window is the default
 * 
 * 
 * Example calculation of cutoff:
 * You have to know the sample frequency of the input signal what you have to filter, for example 48kHz
 * Nyquist frequency is 24kHz.
 * 24kHz => 0.5
 * expcted 10kHz:
 * 10 kHz => (10kHz/ 24kHz) * 0.5
 * 
 * Filter len calculation:
 * M ~= 4 / BW => 
 * BW: is the transition band width, transition band is the frequencies between passband and stopband 
 * M: length of filer kernel, approximation
 * 
 * Steps:
 * 1. create lower cutoff filter
 * 2. create upper cutoff filter
 * 3. spectarl inversion of upper cutoff filter, transformed to high pass filter
 * 4. output filter creation with sum of upper and lower cutoff filter
 * 5. spectral inversion of ouput filter, transformed from band reject filter to band pass filter
 * 
 * @param output_filter filter output result
 * @param input_sample_freq_khz known filterable signal sample frequency in kHz 
 * @param lower_cutoff_freq_khz  lower_cutoff frequency in kHz
 * @param upper_cutoff_freq_khz  upper_cutoff frequency in kHz
 * @param window_calc window calculation function for given index. int argument: index of filter, dsp_size_t argument: size of filter
 * @param filter_len filter len
 */
void dsp_bp_win_sinc_filter(dsp_val_t *output_filter, dsp_val_t input_sample_freq_khz, 
                            dsp_val_t lower_cutoff_freq_khz, dsp_val_t upper_cutoff_freq_khz,
                            dsp_val_t (*window_calc)(int, dsp_size_t), dsp_size_t filter_len);


/**
 * @brief Calculate Hamming window
 * 
 * @param idx index of filter
 * @param filter_len filter len
 * @return dsp_val_t calculation result
 */
dsp_val_t dsp_hamming_window(int idx, dsp_size_t filter_len);

/**
 * @brief Calculate Blackman window
 * 
 * @param idx index of filter
 * @param filter_len filter len
 * @return dsp_val_t calculation result
 */
dsp_val_t dsp_blackman_window(int idx, dsp_size_t filter_len);

#endif 