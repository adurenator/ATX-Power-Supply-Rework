
#include "display.h"
#include "display_tables.h"
#include <stdint.h>
#include <stdlib.h>
#include "pic16f1615.h"


////////////////////////////////////////////////////////////////////////////////
//
// Macros
//
////////////////////////////////////////////////////////////////////////////////

#define ADD_LINE(ID, PORT, PIN)	\
    lines[ID].reg    = PORT; 	\
    lines[ID].pin    = PIN;

#define ADD_CONTROLLER(ID, CLK, LATCH, RST, TYPE) \
    controllers[ID].id               = ID; 	\
    controllers[ID].clk              = CLK;	\
    controllers[ID].latch            = LATCH; 	\
    controllers[ID].reset            = RST;	\
    controllers[ID].type             = TYPE;

#define ADD_CONTROLLER_LINE(INDEX, ID, LINE)	\
    controllers[INDEX].data[ID] = LINE;

#define ADD_CONTROLLER_FUNCTIONS(INDEX, CONFIG, ON, OFF) \
    controllers[INDEX].displayConfigure = CONFIG;   \
    controllers[INDEX].displayOn = ON;              \
    controllers[INDEX].displayOff = OFF;

#define ADD_DISPLAY(INDEX, INIT_VALUE, ONOFF, CONTROLLER) \
    displays[INDEX].currentValue = INIT_VALUE;  \
    displays[INDEX].sw = ONOFF;                 \
    displays[INDEX].controller = CONTROLLER;


////////////////////////////////////////////////////////////////////////////////
//
// Private Variables
//
////////////////////////////////////////////////////////////////////////////////

#define SEG7_NUM_LINES          12
#define SEG7_NUM_CONTROLLERS    1
#define SEG7_NUM_DISPLAYS       4
#define MAX_7SEGMENT_GPIO_NUM   8
#define MAX_7SEG_CTRL_LINE_NUM  8


typedef enum
{
    SEG7_CTRL_TYPE_SR_SERIAL,           // For serial shift reg (dat + clk + latch? + reset?)
    SEG7_CTRL_TYPE_SR_PARALLEL,         // For parallel shift reg (dat[8] + clk? + latch? + reset?)
    SEG7_CTRL_TYPE_HYBRID_SR_DECODER,   // For serial shift reg + 7seg decoder[4] on sr output
    SEG7_CTRL_TYPE_DECODER,             // Direct decoder access
    SEG7_CTRL_TYPE_DIRECT               // 7 segment configuration directly with gpios
} controller_type_t;

typedef struct
{
    //uint8_t             id;
    uint8_t             *reg;
    uint8_t             pin;
} data_line_t;

typedef struct
{
    uint8_t             id;
    data_line_t         *clk;
    data_line_t         *latch;
    data_line_t         *reset;
    data_line_t         *data[MAX_7SEG_CTRL_LINE_NUM];
    controller_type_t   type;
    void                (*displayConfigure)( uint8_t, uint8_t );
    void                (*displayOn)( uint8_t, uint8_t );
    void                (*displayOff)( uint8_t, uint8_t );
} seg7_controller_t;

typedef struct
{
    //uint8_t             id;
    uint8_t		currentValue;
    data_line_t         *sw;
    seg7_controller_t   *controller;
} segment7_t;


uint8_t currentActiveDisplay;

segment7_t displays[SEG7_NUM_DISPLAYS];

seg7_controller_t controllers[SEG7_NUM_CONTROLLERS];

data_line_t lines[SEG7_NUM_LINES];



////////////////////////////////////////////////////////////////////////////////
//
// Private Methods Prototypes
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegParallelConfig( uint8_t controllerId, uint8_t value );

void shiftRegSerialConfig( uint8_t controllerId, uint8_t value );

void decoderConfig( uint8_t controllerId, uint8_t value );

void shiftRegSerialDecoderConfig( uint8_t controllerId, uint8_t value );
void shiftRegSerialDecoderOn( uint8_t controllerId, uint8_t displayId );
void shiftRegSerialDecoderOff( uint8_t controllerId, uint8_t displayId );

void bitSet( uint8_t *reg, uint8_t bitNum );

void bitClear( uint8_t *reg, uint8_t bitNum );



////////////////////////////////////////////////////////////////////////////////
//
// Public Methods
//
////////////////////////////////////////////////////////////////////////////////

void initDisplays( void )
{
    uint8_t i;


    // TODO basic initialization
    

    // Initialize lines
    ADD_LINE( 0, (uint8_t*)PORTA, 0 ); // RA0
    ADD_LINE( 1, (uint8_t*)PORTA, 1 ); // RA1
    ADD_LINE( 2, (uint8_t*)PORTA, 2 ); // RA2
    ADD_LINE( 3, (uint8_t*)PORTA, 3 ); // RA3
    ADD_LINE( 4, (uint8_t*)PORTA, 4 ); // RA4
    ADD_LINE( 5, (uint8_t*)PORTA, 5 ); // RA5

    ADD_LINE( 6, (uint8_t*)PORTA, 0 ); // RC0
    ADD_LINE( 7, (uint8_t*)PORTC, 1 ); // RC1
    ADD_LINE( 8, (uint8_t*)PORTC, 2 ); // RC2
    ADD_LINE( 9, (uint8_t*)PORTC, 3 ); // RC3
    ADD_LINE( 10, (uint8_t*)PORTC, 4 ); // RC4
    ADD_LINE( 11, (uint8_t*)PORTC, 5 ); // RC5


    // Initialize controllers
    /*
     * Controller 0:
     *      clk     -> RA2
     *      latch   -> RA3
     *      reset   ->  -
     *      data    -> RA4
     */
    ADD_CONTROLLER( 0, &lines[2], &lines[3], NULL, SEG7_CTRL_TYPE_HYBRID_SR_DECODER );
    ADD_CONTROLLER_FUNCTIONS( 0, &shiftRegSerialDecoderConfig, &shiftRegSerialDecoderOn, &shiftRegSerialDecoderOff );
    ADD_CONTROLLER_LINE( 0, 0, &lines[4] );


    // Initialize displays
    ADD_DISPLAY( 0, 0, NULL, &controllers[0] );
    ADD_DISPLAY( 1, 0, NULL, &controllers[0] );
    ADD_DISPLAY( 2, 0, NULL, &controllers[0] );
    ADD_DISPLAY( 3, 0, NULL, &controllers[0] );


    // TODO init display with all segments off
    for ( i = 0; i < SEG7_NUM_DISPLAYS; i++ )
    {
        displays[i].controller->displayConfigure( displays[i].controller->id, 0 );
    }
}


void displayOn( uint8_t displayId )
{
    bitSet( displays[displayId].sw->reg, displays[displayId].sw->pin );
}


void displayOff( uint8_t displayId )
{
    bitClear( displays[displayId].sw->reg, displays[displayId].sw->pin );
}


void displayShow( uint8_t num, uint8_t displayId )
{
    // Sanity check
    if ( displayId < SEG7_NUM_DISPLAYS )
    {
        displayOff( currentActiveDisplay );

        displays[displayId].controller->displayConfigure( displays[displayId].controller->id, num );
        displays[displayId].currentValue = num;

        displayOn( displayId );

        currentActiveDisplay = displayId;
    }
}



////////////////////////////////////////////////////////////////////////////////
//
// Private Methods
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegParallelConfig( uint8_t controllerId, uint8_t value )
{
    // Sanity check
    if ( controllerId < SEG7_NUM_CONTROLLERS )
    {
        // TODO
    }
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegSerialConfig( uint8_t controllerId, uint8_t value )
{
    // Sanity check
    if ( controllerId < SEG7_NUM_CONTROLLERS )
    {
        // TODO
    }
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void decoderConfig( uint8_t controllerId, uint8_t value )
{
    // Sanity check
    if ( controllerId < SEG7_NUM_CONTROLLERS )
    {
        // TODO
    }
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegSerialDecoderConfig( uint8_t controllerId, uint8_t value )
{
    // Sanity check
    if ( controllerId < SEG7_NUM_CONTROLLERS )
    {
        // TODO
    }
}


void shiftRegSerialDecoderOn( uint8_t controllerId, uint8_t displayId )
{
    // TODO
}


void shiftRegSerialDecoderOff( uint8_t controllerId, uint8_t displayId )
{
    // TODO
}


void bitSet( uint8_t *reg, uint8_t bitNum )
{
    *reg |= (1 << bitNum);
}


void bitClear( uint8_t *reg, uint8_t bitNum )
{
    *reg &= ~(1 << bitNum);
}
