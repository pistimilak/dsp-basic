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

#ifndef __SIGNAL_STAT_H__
#define __SIGNAL_STAT_H__

#include "dsp_common.h"

/**
 * @brief Signal mean calculation
 * equivalent DC signal
 * mu = 1/N * sum(xi)
 * @param sig signal array 
 * @param len lenght of array
 * @return sig_val_t mean value
 */
sig_val_t signal_mean(sig_val_t *sig, sig_len_t len);


/**
 * @brief Signal variance
 * pow(sigma, 2) = (1/(N-1)) * sum(pow(xi-u, 2))
 * @param sig signal array
 * @param sig_mean signal mean value
 * @param len length of signal
 * @return sig_val_t variance value
 */
sig_val_t signal_variance(sig_val_t *sig, sig_val_t sig_mean, sig_len_t len);

/**
 * @brief Signal standard deviation
 * 
 * @param sig_variance signal variance
 * @return sig_val_t standard deviation value of the signal
 */
sig_val_t signal_std_dev(sig_val_t sig_variance);


#endif

