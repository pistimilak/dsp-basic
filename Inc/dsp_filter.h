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

void dsp_lp_win_sinc_filter(dsp_val_t *output_filter, dsp_val_t cutoff_freq, dsp_size_t filter_len);



#endif 