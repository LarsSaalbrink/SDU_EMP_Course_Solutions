/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: swtimers.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Initialize the systick interrupt
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef _SWTIMERS_H
  #define _SWTIMERS_H

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void delay_ms_systick(INT32U delayDuration);
/*****************************************************************************
*   Input    : -Duration to delay for
*   Output   : -
*   Function : Function for inserting time delays
******************************************************************************/

void enable_global_int();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Enable global interrupts.
******************************************************************************/

void disable_global_int();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt.
******************************************************************************/

void init_systick();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the systick interrupt.
******************************************************************************/

/****************************** End Of Module *******************************/
#endif  /* _SWTIMERS_H */
