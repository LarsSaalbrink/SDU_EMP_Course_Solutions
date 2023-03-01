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
* 230301  LS    Module created.
*
*****************************************************************************/

#ifndef _IO_H
#define _IO_H

/***************************** Include files *******************************/
#include <stdint.h>
#include <tm4c.h>
#include "emp_type.h"
/*****************************    Defines    *******************************/
/*****************************   Constants   *******************************/
/*****************************   Functions   *******************************/
void init_io(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the PORTF external interrupt and configure it
*              to trigger on PF4 rising edges
******************************************************************************/
void GPIOFHandler(void);
/***********************************
* Input :   -External interrupt triggered by PORTF
* Output :  -
* Function: Set "button_pressed" flag to true
***********************************/

#endif  // _IO_H

/***************** End of module **************/
