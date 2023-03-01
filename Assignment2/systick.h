/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: systick.h
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: Header for systick related components
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230301  LS    Module created.
*
*****************************************************************************/
#ifndef _SYSTICK_H
#define _SYSTICK_H
/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
#define SYSTICK_RELOAD_VALUE 16000              // 1 mS

// Missing definitions in tm4c123gh6pm.h file
#define NVIC_INT_CTRL_PEND_SYST   0x04000000    // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 0x02000000    // Unpend a systick int

#define SYSTICK_PRIORITY    0x7E
/*****************************   Functions   *******************************/
void systick_handler(void);
/*****************************************************************************
*   Input    : -Interrupt triggered by systick timer counter overflow
*   Output   : -
*   Function : Increment global variable "ticks" once every millisecond
******************************************************************************/
void init_systick();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the systick interrupt.
******************************************************************************/

#endif // _SYSTICK_H

/***************** End of module **************/
