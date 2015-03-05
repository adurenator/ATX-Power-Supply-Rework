
#include "display.h"
#include "display_tables.h"
#include <stdint.h>
#include "pic16f1615.h"


////////////////////////////////////////////////////////////////////////////////
//
// Private Variables
//
////////////////////////////////////////////////////////////////////////////////

#define SEG7_NUM_LINES          5
#define SEG7_NUM_CONTROLLERS    1
#define SEG7_NUM_DISPLAYS       4
#define MAX_7SEGMENT_GPIO_NUM   8
#define MAX_7SEG_CTRL_LINE_NUM  8

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
} reg_bit_t;

typedef enum
{
    SEG7_CTRL_TYPE_SHIFT_REG,
    SEG7_CTRL_TYPE_ENCODER,
    SEG7_CTRL_TYPE_DIRECT
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
    void (*displayConfigure)( uint8_t, uint8_t );
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

void encoderConfig( uint8_t controllerId, uint8_t value );

void bitSet( uint8_t *reg, uint8_t bitNum );

void bitClear( uint8_t *reg, uint8_t bitNum );



////////////////////////////////////////////////////////////////////////////////
//
// Public Methods
//
////////////////////////////////////////////////////////////////////////////////

void initDisplays( void )
{
    // TODO init lines
    // RA0
    lines[0].reg    = &PORTA;
    lines[0].pin    = 0;

    // TODO init controllers
    controllers[0].displayConfigure = shiftRegSerialConfig;

    // TODO init displays

    // TODO init display with all segments off
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
    displayOff( currentActiveDisplay );

    displays[displayId].controller->displayConfigure( displays[displayId].controller->id, num );
    displays[displayId].currentValue = num;

    displayOn( displayId );

    currentActiveDisplay = displayId;
}



////////////////////////////////////////////////////////////////////////////////
//
// Private Methods
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegParallelConfig( uint8_t controllerId, uint8_t value )
{

}


void shiftRegSerialConfig( uint8_t controllerId, uint8_t value )
{

}


void encoderConfig( uint8_t controllerId, uint8_t value )
{

}


void bitSet( uint8_t *reg, uint8_t bitNum )
{
    *reg |= (1 << bitNum);
}


void bitClear( uint8_t *reg, uint8_t bitNum )
{
    *reg &= ~(1 << bitNum);
}
