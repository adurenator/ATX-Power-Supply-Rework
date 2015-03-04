
#include "display.h"
#include "display_tables.h"
#include <xc.h>
#include "pic16f1615.h"


////////////////////////////////////////////////////////////////////////////////
//
// Private Variables
//
////////////////////////////////////////////////////////////////////////////////

#define 7SEG_NUM_LINES 5
#define 7SEG_NUM_CONTROLLERS 1
#define 7SEG_NUM_DISPLAYS 4
#define MAX_7SEGMENT_GPIO_NUM 8
#define MAX_7SEG_CTRL_LINE_NUM 8

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
	7SEG_CTRL_TYPE_SHIFT_REG,
	7SEG_CTRL_TYPE_ENCODER,
	7SEG_CTRL_TYPE_DIRECT
} controller_type_t;

typedef struct
{
	uint8_t				id;
	uint8_t 			*reg;
	uint8_t				pin;
} data_line_t;

typedef struct
{
	uint8_t				id;
	data_line_t			*clk;
	data_line_t			*latch;
	data_line_t			*reset;
	data_line_t			*data[MAX_7SEG_CTRL_LINE_NUM];
	controller_type_t	type;
	void (*displayConfigure)( 7seg_controller_t *controller, uint8_t value );
} 7seg_controller_t;

typedef struct
{
	uint8_t 			id;
	uint8_t				currentValue;
	data_line_t			*sw;
	7seg_controller_t	*controller;
} 7segment_t;


uint8_t currentActiveDisplay;

7segment_t displays[7SEG_NUM_DISPLAYS];

controller_type_t controllers[7SEG_NUM_CONTROLLERS];

data_line_t LINES[7SEG_NUM_LINES];



////////////////////////////////////////////////////////////////////////////////
//
// Private Methods Prototypes
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegParallelConfig( 7seg_controller_t *controller, uint8_t value );

void shiftRegSerialConfig( 7seg_controller_t *controller, uint8_t value );

void encoderConfig( 7seg_controller_t *controller, uint8_t value );

void bitSet( uint8_t *reg, uint8_t bit );

void bitClear( uint8_t *reg, uint8_t bit );



////////////////////////////////////////////////////////////////////////////////
//
// Public Methods
//
////////////////////////////////////////////////////////////////////////////////

void initDisplays( void )
{
    // TODO init lines

	// TODO init controllers

	// TODO init displays

	// TODO init display with all segments off
}


void displayOn( uint8_t displayId )
{
	bitSet( displays[displayId].sw.reg, displays[displayId].sw.pin );
}


void displayOff( uint8_t displayId )
{
	bitClear( displays[displayId].sw.reg, displays[displayId].sw.pin );
}


void displayShow( uint8_t num, uint8_t displayId )
{
	displayOff( currentActiveDisplay );

	shiftRegConfig( num );

	displayOn( displayId );

	currentActiveDisplay = displayId;
}



////////////////////////////////////////////////////////////////////////////////
//
// Private Methods
//
////////////////////////////////////////////////////////////////////////////////

void shiftRegParallelConfig( 7seg_controller_t *controller, uint8_t value )
{

}


void shiftRegSerialConfig( 7seg_controller_t *controller, uint8_t value )
{

}


void encoderConfig( 7seg_controller_t *controller, uint8_t value )
{

}


void bitSet( uint8_t *reg, uint8_t bit )
{
	*reg |= (1 << bit);
}


void bitClear( uint8_t *reg, uint8_t bit )
{
	*reg &= ~(1 << bit)
}
