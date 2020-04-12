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
                            dsp_val_t (*window_calc)(int, dsp_size_t), dsp_size_t filter_len)
{
    dsp_size_t i;
    
    /*calculate cutoff*/
    dsp_val_t c = (cutoff_freq_khz / input_sample_freq_khz);
    
    /*calculate index, which can be negative*/
    int offset;
    for(i = 0; i < filter_len; i++) {

        /*index ofset calculation*/
        offset = (int)i - (filter_len / 2); 

        /*special rules for center*/
        if(offset == 0) {
            *(output_filter + i)  = 2.0 * M_PI * c;
        } else {
            
            /*Sinc calculation*/
            *(output_filter + i) = sin(2.0 * M_PI * c * offset) / offset;
            
            /*Window calculation*/
            if(window_calc == NULL) {
                /*Default is the Hamming window*/
                *(output_filter + i) *= dsp_hamming_window(i, filter_len);    
            } else {
                *(output_filter + i) *= window_calc(i, filter_len);
            }
             
        }
    }
}


/**
 * @brief Calculate Hamming window
 * 
 * @param idx index of filter
 * @param filter_len filter len
 * @return dsp_val_t calculation result
 */
dsp_val_t dsp_hamming_window(int idx, dsp_size_t filter_len)
{
    return (0.54 - 0.46 * cos(2.0 * M_PI * idx / filter_len));
}

/**
 * @brief Calculate Blackman window
 * 
 * @param idx index of filter
 * @param filter_len filter len
 * @return dsp_val_t calculation result
 */
dsp_val_t dsp_blackman_window(int idx, dsp_size_t filter_len)
{
    return (0.42 - 0.5 * cos((2.0 * M_PI * idx) / filter_len) + 
            0.08 * cos((4.0 * M_PI * idx) / filter_len));
}