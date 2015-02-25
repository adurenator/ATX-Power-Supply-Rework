/* 
 * File:   main.c
 * Author: adur
 *
 * Created on February 23, 2015, 12:06 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pic16f1615.h"
#include "16F1615_config.h"

#include "hal_gpios.h"
#include "hal_adc.h"
#include "display.h"
#include "tasks.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    // Initialize gpios with proper configuration
    initGpios();

    // Init the adc module to read voltage and current measures
    initADC();

    // Initialize 7segment displays
    initDisplay();

    // Start infinite loop.
    // TODO: Some scheduler that executes tasks periodically ?
    while (1)
    {
        // Measure Voltage
        voltageMeasureTask();

        // Measure Current
        currentMeasureTask();

        // Displaying task
        displayRefreshTask();
    }

    return (EXIT_SUCCESS);
}

