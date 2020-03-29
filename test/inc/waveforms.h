/**
 * @file waveforms.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief Waveforms header
 * @version 0.1
 * @date 2020-03-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WAVEFORMS_H__
#define __WAVEFORMS_H__


/**
 * @brief Signal array sizes
 * 
 */
#define INP_SIG_F32_1K_15K_SIZE         (320UL)
#define IMPULSE_RESP_SIZE               (29UL)
#define ECG_SIGNAL_SIZE                 (640UL)
#define ECG_IMX_SIGNAL_SIZE             (320UL)
#define ECG_REX_SIGNAL_SIZE             (320UL)


/**
 * @brief Input signal with 1kHz and 15kHz sine components
 * 
 */
extern const double InputSignal_f32_1kHz_15kHz[INP_SIG_F32_1K_15K_SIZE];


/**
 * @brief Impulse response for convolution test
 * 
 */
extern const double  Impulse_response[IMPULSE_RESP_SIZE];


/**
 * @brief ECG signal
 * 
 */
extern const double ECG_signal[ECG_SIGNAL_SIZE];



/**
 * @brief ECG REX
 * 
 */
extern const double ECG_REX[ECG_REX_SIGNAL_SIZE];

/**
 * @brief ECG IMX
 * 
 */
extern const double ECG_IMX[ECG_IMX_SIGNAL_SIZE];


#endif