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

#ifndef _T_LIGHT_H
#define _T_LIGHT_H

/***************************** Include files *******************************/
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
void t_light_sm(void);


#endif  // _T_LIGHT_H
