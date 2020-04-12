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


static void _dsp_filter_kernel(dsp_val_t *output_filter, 
                                dsp_val_t input_sample_freq_khz, 
                                dsp_val_t cutoff_freq_khz,
                                dsp_val_t (*window_calc)(int, dsp_size_t),
                                void (*spectral_op)(dsp_val_t*, int, dsp_size_t), 
                                dsp_size_t filter_len);



/**
 * @brief Filter kernel function to create common interface for different types
 * Cutoff frequency must be between 0.0 and 0.5
 * sinc function:
 *      h[i] = sin(2 * PI * fc * i) / (i * PI)
 * After applying sinc function, window calculation is also applied. if the function pointer is NULL,
 * Hamming window is the default
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
 * Additional spectral operation support with function pointer
 * Args: filter array pointer, index of element, filter len
 * @param output_filter filter output result
 * @param input_sample_freq_khz known filterable signal sample frequency in kHz 
 * @param cutoff_freq_khz cutoff frequency in kHz
 * @param window_calc window calculation function for given index. int argument: index of filter, dsp_size_t argument: size of filter
 * @param spectral_op additional spectral operation function pointer
 * @param filter_len filter len
 */
static void _dsp_filter_kernel(dsp_val_t *output_filter, 
                                dsp_val_t input_sample_freq_khz, 
                                dsp_val_t cutoff_freq_khz,
                                dsp_val_t (*window_calc)(int, dsp_size_t),
                                void (*spectral_op)(dsp_val_t*, int, dsp_size_t), 
                                dsp_size_t filter_len)
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

        /*do spectral inversion or other further operation, if function pointer is set*/
        if (spectral_op != NULL) {
            spectral_op(output_filter, i, filter_len);
        }
    }
}


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
    /*create simple lowpass filter*/
    _dsp_filter_kernel(output_filter, input_sample_freq_khz, 
                        cutoff_freq_khz, window_calc, NULL, filter_len);
}


/**
 * @brief Create high-pass windowed sinc filter
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
 * 1. create cutoff low pas filter
 * 2. spectral inversion transforms to high pass filter
 *  
 * @param output_filter filter output result
 * @param input_sample_freq_khz known filterable signal sample frequency in kHz 
 * @param cutoff_freq_khz  cutoff frequency in kHz
 * @param window_calc window calculation function for given index. int argument: index of filter, dsp_size_t argument: size of filter
 * @param filter_len filter len
 */
void dsp_hp_win_sinc_filter(dsp_val_t *output_filter, dsp_val_t input_sample_freq_khz, dsp_val_t cutoff_freq_khz,
                            dsp_val_t (*window_calc)(int, dsp_size_t), dsp_size_t filter_len)
{
    /*Create low-pass filter with spectral inversion*/
    _dsp_filter_kernel(output_filter, input_sample_freq_khz, 
                    cutoff_freq_khz, window_calc, dsp_specteral_inversion, filter_len);
}


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
                            dsp_val_t (*window_calc)(int, dsp_size_t), dsp_size_t filter_len)
{

    dsp_size_t i;
    
    /*filter values*/
    dsp_val_t l_filter, u_filter;

    /*calculate lower cutoff*/
    dsp_val_t lc = (lower_cutoff_freq_khz / input_sample_freq_khz);
    
    /*calculate upper cutoff*/
    dsp_val_t uc = (upper_cutoff_freq_khz / input_sample_freq_khz);
    
    /*calculate index, which can be negative*/
    int offset;
    for(i = 0; i < filter_len; i++) {

        /*index ofset calculation*/
        offset = (int)i - (filter_len / 2); 

        /*special rules for center*/
        if(offset == 0) {
            l_filter = 2.0 * M_PI * lc;
            u_filter = 2.0 * M_PI * uc;

        } else {
            
            /*Sinc calculation*/
            l_filter = sin(2.0 * M_PI * lc * offset) / offset;
            u_filter = sin(2.0 * M_PI * uc * offset) / offset;


            /*Window calculation*/
            if(window_calc == NULL) {
                /*Default is the Hamming window*/
                l_filter *= dsp_hamming_window(i, filter_len);
                u_filter *= dsp_hamming_window(i, filter_len);    
            } else {
                l_filter *= window_calc(i, filter_len);
                u_filter *= window_calc(i, filter_len);
            }
             
        }

        /*change low pass filter to high pass filter using spectral inversion*/
        u_filter *= -1.0;
        if (i == filter_len / 2) {
            u_filter += 1.0;
        }

        /*calculate output destination filter*/
        *(output_filter + i) = l_filter + u_filter;

        /*change band reject filter into bandpass filter using spectral inversion*/
        *(output_filter + i) *= -1.0;
        if (i == filter_len / 2) {
            *(output_filter + i) += 1.0;
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

/**
 * @brief Calculate spectral inversion for given index
 * 
 * @param filter filter memory storage
 * @param idx index of expected element
 * @param filter_len filter length
 */
void dsp_specteral_inversion(dsp_val_t *filter, int idx, dsp_size_t filter_len)
{
        *(filter + idx) *= -1.0;
        if (idx == filter_len / 2) {
            *(filter + idx) += 1.0;
        }
}