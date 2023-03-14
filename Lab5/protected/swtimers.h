/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: swtimers.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: SW timers for triggering tasks
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

/*****************************    Defines    *******************************/
#define TICK_TIME	5		// tick time in milli seconds.

#define MILLISEC(time_in_msec)  time_in_msec / TICK_TIME

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT16U swtimer( INT8U );
/*****************************************************************************
*   Input    : Index of swtimer to access
*   Output   : -
*   Function : Getter function for accessing state of swtimers
******************************************************************************/

void start_swtimer( INT8U, INT8U, INT16U );
/*****************************************************************************
*   Input    : -Timer to start
*              -Event to trigger when timer expires
*              -Value to start the timer with
*   Output   : -
*   Function : Function for starting the swtimers
******************************************************************************/

void swt_ctrl(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : This function updates the timers every tick. runs in main loop
******************************************************************************/

void init_swtimers(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Set timer value and event buffer to 0 for all timers
******************************************************************************/

/****************************** End Of Module *******************************/
#endif

