/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: driver.h
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: Header for driver interpreting input from switch 1
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230301  LS    Module created.
*
*****************************************************************************/

#ifndef _DRIVER_H
#define _DRIVER_H

/***************************** Include files *******************************/
#include "t_light.h"
#include "emp_type.h"
/*****************************    Defines    *******************************/
enum driver_sm_state
{
    FIRST_PRESS,
    CONTACT_BOUNCE,
    D_CLICK,
    LONG_WAIT
};
/*****************************   Constants   *******************************/
/*****************************   Functions   *******************************/
void start_t_light(INT32U* delay_start,
                   volatile BOOLEAN* sw1_pressed,
                   enum driver_sm_state* driver_state);
/*****************************************************************************
*   Input    : -Pointer to variable containing timestamp in milliseconds (for managing delay)
*              -Pointer to flag indicating if SW1 has been pressed
*              -Pointer to enum variable containing state of input analysis state machine
*   Output   : -
*   Function : Gets a timestamp for delay_start when the button is first pressed
******************************************************************************/
void wait_for_contact_bounce(volatile INT32U* ticks,
                             INT32U* delay_start,
                             volatile BOOLEAN* sw1_pressed,
                             enum driver_sm_state* driver_state);
/*****************************************************************************
*   Input    : -Pointer to clock variable counting milliseconds since program start
*              -Pointer to variable containing timestamp in milliseconds (for managing delay)
*              -Pointer to flag indicating if SW1 has been pressed
*              -Pointer to enum variable containing state of input analysis state machine
*   Output   : -
*   Function : Waits for a short while to avoid registering more
*              than one press at once due to contact bouncing
******************************************************************************/
void identify_press_type(volatile INT32U* ticks,
                         INT32U* delay_start,
                         volatile BOOLEAN* sw1_pressed,
                         enum driver_sm_state* driver_state,
                         enum t_light_sm_state* t_light_state);
/*****************************************************************************
*   Input    : -Pointer to clock variable counting milliseconds since program start
*              -Pointer to variable containing timestamp in milliseconds (for managing delay)
*              -Pointer to flag indicating if SW1 has been pressed
*              -Pointer to enum variable containing state of input analysis state machine
*              -Pointer to enum variable for the state of the traffic light state machine
*   Output   : -
*   Function : Waits for a short while to avoid registering more
*              than one press at once due to contact bouncing
******************************************************************************/
void did_longpress_complete(volatile INT32U* ticks,
                            INT32U* delay_start,
                            enum driver_sm_state* driver_state,
                            enum t_light_sm_state* t_light_state);
/*****************************************************************************
*   Input    : -Pointer to clock variable counting milliseconds since program start
*              -Pointer to variable containing timestamp in milliseconds (for managing delay)
*              -Pointer to enum variable containing state of input analysis state machine
*              -Pointer to enum variable for the state of the traffic light state machine
*   Output   : -
*   Function : Checks if a press longer than 200ms lasted for
*              the full 2 second duration required for it to register
******************************************************************************/
void read_sw1(enum t_light_sm_state* t_light_state);
/*****************************************************************************
*   Input    : -Pointer to enum variable for the state of the traffic light state machine
*   Output   : -
*   Function : State machine for handling analysis of user input
******************************************************************************/

#endif  // _DRIVER_H

/***************** End of module **************/
