/* 
 * File:   display.h
 * Author: adur
 *
 * Created on February 23, 2015, 12:11 AM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif


    void initDisplays( void );

    void displayOn( uint8_t displayId );

    void displayOff( uint8_t displayId );

    void displayShow( uint8_t num, uint8_t displayId );


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

