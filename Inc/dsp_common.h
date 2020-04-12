/**
 * @file dsp_common.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief DSP Common definitions
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DSP_COMMON_H__
#define __DSP_COMMON_H__

#include <stdint.h>
#include <math.h>


#ifndef NULL
    #define NULL    ((void *)0)
#endif

#ifndef M_PI
    #define M_PI    3.14159265358979323846
#endif

typedef double dsp_val_t; 					// signal value typedef
typedef unsigned long dsp_size_t;			// signal length typedef

#endif