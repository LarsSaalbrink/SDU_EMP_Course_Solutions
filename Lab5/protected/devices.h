/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: devices.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: "Driver" function for operating single LEDS's
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef DEVICES_H_
#define DEVICES_H_

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
// Device Types
// ------------
//
// LED devices
// -----------
//
#define LED_STATUS 	11
#define LED_RED		21
#define LED_YELLOW	22
#define LED_GREEN	23
//
//
// Device actions
// --------------
//
// LED actions
// ----------
//
#define TURN_LED_ON		1
#define TURN_LED_OFF	2
#define TOGGLE_LED		3

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

BOOLEAN turn_led( INT8U, INT8U );
/*****************************************************************************
*   Input    -LED to operate on
*            -What action to perform
*   Output   -Was operation successful (TRUE/FALSE)
*   Function -Driver function for operating the 3 LEDS connected to PORTF
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*DEVICES_H_*/
