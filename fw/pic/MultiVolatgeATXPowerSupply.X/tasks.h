/* 
 * File:   tasks.h
 * Author: adur
 *
 * Created on February 25, 2015, 12:00 AM
 */

#ifndef TASKS_H
#define	TASKS_H

#ifdef	__cplusplus
extern "C" {
#endif


    void voltageMeasureTask( void );

    void currentMeasureTask( void );

    void displayRefreshTask( void );


#ifdef	__cplusplus
}
#endif

#endif	/* TASKS_H */

