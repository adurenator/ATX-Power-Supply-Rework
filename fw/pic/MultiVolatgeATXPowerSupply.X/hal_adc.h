/* 
 * File:   hal_adc.h
 * Author: adur
 *
 * Created on February 23, 2015, 12:10 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include <stdint.h>


    #define ADC_CH0 0
    #define ADC_CH1 0x01
    #define ADC_CH2 0x02
    #define ADC_CH3 0x03
    #define ADC_TMP 0x1D

    #define ADC_MODE_10b 0
    #define ADC_MODE_8b  1

    #define ADC_CLK_FOSC_2  0
    #define ADC_CLK_FOSC_8  1
    #define ADC_CLK_FOSC_32 2
    #define ADC_CLK_INT_RC  3
    #define ADC_CLK_FOSC_4  4
    #define ADC_CLK_FOSC_16 5
    #define ADC_CLK_FOSC_64 6

    #define ADC_VREF_VDD        0
    #define ADC_VREF_EXT_PIN    2
    #define ADC_VREF_INT_REF    3

    #define ADC_ON() ADCON0bits.ADON = 1
    #define ADC_OFF() ADCON0bits.ADON = 0


    void initADC( void );

    void configAdcChannel( uint8_t channel );

    uint16_t readAdcSample( void );

    uint16_t readAdcChannel( uint8_t channel );


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_ADC_H */

