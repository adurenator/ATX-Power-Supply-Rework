
#include "hal_adc.h"
#include <xc.h>
#include "pic16f1615.h"


void initADC( void )
{
    // Set AN0 and AN1 as inputs
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;


    // Set AN0 and AN1 as analog
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;


    // ADCON0 register initial config
    ADCON0bits.CHS        = ADC_CH0;  // CH0 selected by default
    ADCON0bits.GO_nDONE   = 0;        // Forcing ADC to idle status


    // ADCON1 register initial config
    ADCON1bits.ADFM   = 1;                  // Right justified. 16 bits operation mode.
    ADCON1bits.ADCS   = ADC_CLK_FOSC_64;    // Fosc/64
    ADCON1bits.ADPREF = ADC_VREF_VDD;       // Connected to Vdd


    // ADCON2 register initial config
    ADCON2bits.TRIGSEL = 0;   // No auto-conversion trigger selected


    // Swtich ADC module ON
    ADC_ON();
}


void configAdcChannel( uint8_t channel )
{
    // Configure channel
    ADCON0bits.CHS = channel;
}


uint16_t readAdcSample( void )
{
    // In case an operation is already in progress do nothing
    if ( ADCON0bits.GO_nDONE == 0 )
    {
        ADCON0bits.GO_nDONE = 1;
    }

    // Wait until operation is finised
    while ( ADCON0bits.GO_nDONE == 1 );

    return ADRES;
}


uint16_t readAdcChannel( uint8_t channel )
{
    configAdcChannel( channel );

    return readAdcSample();
}
