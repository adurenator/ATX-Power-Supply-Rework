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


    void initADC( void );

    uint16_t readAdcChannel( uint8_t channel );


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_ADC_H */

