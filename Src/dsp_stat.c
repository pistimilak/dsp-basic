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

#include "dsp_stat.h"



/*
Signal mean
*/
dsp_val_t dsp_sig_mean(dsp_val_t *sig, dsp_size_t len)
{
	dsp_size_t i;
	dsp_val_t mean = 0;
	
	for (i = 0; i < len; i++) {
		mean += *(sig + i);
	}
	
	mean /= (dsp_val_t)len;
	return mean;
}


/*
Signal varriance
*/
dsp_val_t dsp_sig_variance(dsp_val_t *sig, dsp_val_t sig_mean, dsp_size_t len)
{
	dsp_size_t i;
	dsp_val_t variance = 0;
	
	for (i = 0; i < len; i++) {
		variance += pow(*(sig + i) - sig_mean, 2);
	}
	
	variance /= (dsp_val_t)(len - 1);
	return variance;
}


/*
Signal standard deviation
*/
dsp_val_t dsp_sig_std_dev(dsp_val_t sig_variance)
{
	return sqrt(sig_variance);
}
