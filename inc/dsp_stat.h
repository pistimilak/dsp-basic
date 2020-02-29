/**
 * @file signal_stat.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Signal statistic calculations
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DSP_STAT_H__
#define __DSP_STAT_H__

#include "dsp_common.h"

/**
 * @brief Signal mean calculation
 * equivalent DC signal
 * mu = 1/N * sum(xi)
 * @param sig signal array 
 * @param len lenght of array
 * @return dsp_val_t mean value
 */
dsp_val_t dsp_sig_mean(dsp_val_t *sig, dsp_len_t len);


/**
 * @brief Signal variance
 * pow(sigma, 2) = (1/(N-1)) * sum(pow(xi-u, 2))
 * @param sig signal array
 * @param sig_mean signal mean value
 * @param len length of signal
 * @return dsp_val_t variance value
 */
dsp_val_t dsp_sig_variance(dsp_val_t *sig, dsp_val_t sig_mean, dsp_len_t len);

/**
 * @brief Signal standard deviation
 * How far xi deviates from the mean:
 * sigma = sqrt((1/(N-1)) * sum(pow(xi-u, 2)))
 * @param sig_variance signal variance
 * @return dsp_val_t standard deviation value of the signal
 */
dsp_val_t dsp_sig_std_dev(dsp_val_t sig_variance);


#endif

