/**
 * @file signal_stat.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Signal statistic calculations
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "signal_stat.h"



/*
Signal mean
*/
sig_val_t signal_mean(sig_val_t *sig, sig_len_t len)
{
	sig_len_t i;
	sig_val_t mean = 0;
	
	for (i = 0; i < len; i++) {
		mean += *(sig + i);
	}
	
	mean /= (sig_val_t)len;
	return mean;
}


/*
Signal varriance
*/
sig_val_t signal_variance(sig_val_t *sig, sig_val_t sig_mean, sig_len_t len)
{
	sig_len_t i;
	sig_val_t variance = 0;
	
	for (i = 0; i < len; i++) {
		variance += pow(*(sig + i) - sig_mean, 2);
	}
	
	variance /= (sig_val_t)(len - 1);
	return variance;
}


/*
Signal standard deviation
*/
sig_val_t signal_std_dev(sig_val_t sig_variance)
{
	return sqrt(sig_variance);
}
