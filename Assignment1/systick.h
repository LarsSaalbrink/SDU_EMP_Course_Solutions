/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: systick.h
*
* PROJECT....: Assignment 1
*
* DESCRIPTION: Header for systick related components
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230216  LS    Module created.
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
*   Function : Handle systick interrupt
******************************************************************************/

void init_systick();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the systick interrupt.
******************************************************************************/

void delay(INT32U duration);
/*****************************************************************************
*   Input    : -Duration of delay in milliseconds
*   Output   : -
*   Function : Wait for given amount of milliseconds
******************************************************************************/

#endif // _SYSTICK_H

/***************** End of module **************/

