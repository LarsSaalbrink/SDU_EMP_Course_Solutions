/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: systick.c
*
* PROJECT....: Assignment 1
*
* DESCRIPTION: .c for systick related components
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230216  LS    Module created.
*
*****************************************************************************/
/***************** Include files **************/
#include <stdint.h>
#include <tm4c.h>
#include "systick.h"

/***************** Defines ********************/
/***************** Constants ******************/
/***************** Variables ******************/
volatile INT32U ticks = 0;
/***************** Functions ******************/
void systick_handler(void)
/*****************************************************************************
*   Input    : -Interrupt triggered by systick timer counter overflow
*   Output   : -
*   Function : Handle systick interrupt
******************************************************************************/
{
  if(ticks)
  {
      ticks--;
  }
  // Hardware clears systick int request
}


void init_systick()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the systick interrupt.
******************************************************************************/
{

  // Disable systick timer
  NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);

  // Set current systick counter to reload value
  NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
  // Set Reload value, Systick reload register
  NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;

  // NVIC systick setup, vector number 15
  // Clear pending systick interrupt request
  NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;

  // Set systick priority to 0x10, first clear then set.
  NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
  NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));

  // Select systick clock source, Use core clock
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;

  // Enable systick interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

  // Enable and start timer
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

void delay(INT32U duration)
/*****************************************************************************
*   Input    : -Duration of delay in milliseconds
*   Output   : -
*   Function : Wait for given amount of milliseconds
******************************************************************************/
{
    ticks = duration;
    while( ticks );
}
/***************** End of module **************/
