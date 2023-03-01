/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: t_light.h
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: Header for traffic light state machine
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230301  LS    Module created.
*
*****************************************************************************/

#ifndef _T_LIGHT_H
#define _T_LIGHT_H

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
enum t_light_sm_state
{
    REGULAR,
    NOR_NIGHT,
    EMERGENCY
};

enum colorstate_t_light
{
    RED_STATE,
    RED_YELLOW_STATE,
    GREEN_STATE,
    YELLOW_STATE
};
/*****************************   Constants   *******************************/
/*****************************   Functions   *******************************/
void regular_sm(enum colorstate_t_light* colorstate,
                volatile INT32U* ticks,
                INT32U* delay_start);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the PORTF external interrupt and configure it
*              to trigger on PF4 rising edges
******************************************************************************/

void t_light_sm(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Main state machine to handle the 3 operating states:
*              -Regular traffic light
*              -Norwegian night mode (yellow blink)
*              -Emergency (permanent red)
******************************************************************************/

#endif  // _T_LIGHT_H

/***************** End of module **************/
