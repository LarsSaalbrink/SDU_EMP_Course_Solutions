/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: io.h
*
* PROJECT....: Assignment 1
*
* DESCRIPTION: Header for I/O related components
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230216  LS    Module created.
*
*****************************************************************************/

#ifndef _DRIVER_H
#define _DRIVER_H

/***************************** Include files *******************************/
#include "t_light.h"
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
void read_sw1(enum t_light_sm_state* t_light_state);


#endif  // _DRIVER_H
