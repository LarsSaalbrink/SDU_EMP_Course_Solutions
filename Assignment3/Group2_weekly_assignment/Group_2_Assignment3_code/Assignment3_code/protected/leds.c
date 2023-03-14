/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: leds.c
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "devices.h"
#include "gpio.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void set_leds( red, yellow, green )
BOOLEAN red, yellow, green;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  turn_led( LED_RED,    red    );
  turn_led( LED_YELLOW, yellow );
  turn_led( LED_GREEN,  green  );
}

/****************************** End Of Module *******************************/
