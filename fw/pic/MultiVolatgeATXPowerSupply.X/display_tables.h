/*
 * File:   display.h
 * Author: adur
 *
 * Created on March 04, 2015, 12:11 AM
 */

#ifndef DISPLAY_TABLES_H
#define	DISPLAY_TABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include <stdint.h>


    // 7 segment hexadecimal base representation. LITTLE ENDIAN (gfedcba) bits 7:0
    const uint8_t segment7_hexa_LE[16] = {
        0x3f,	// 0
        0x06,	// 1
        0x5b,	// 2
        0x4f,	// 3
        0x66,	// 4
        0x6d,	// 5
        0x7d,	// 6
        0x07,	// 7
        0x7f,	// 8
        0x6f,	// 9
        0x77,	// A
        0x7c,	// B
        0x39,	// C
        0x5e,	// D
        0x79,	// E
        0x71	// F
    };

    // 7 segment hexadecimal base representation. BIG ENDIAN (abcdefg) bits 7:0
    const uint8_t segment7_hexa_BE[16] = {
        0x7e,	// 0
        0x30,	// 1
        0x6d,	// 2
        0x79,	// 3
        0x33,	// 4
        0x5b,	// 5
        0x5f,	// 6
        0x70,	// 7
        0x7f,	// 8
        0x7b,	// 9
        0x77,	// A
        0x1f,	// B
        0x4e,	// C
        0x3d,	// D
        0x4f,	// E
        0x47	// F
    };


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_TABLES_H */

