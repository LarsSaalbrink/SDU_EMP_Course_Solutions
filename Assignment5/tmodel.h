/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Defines the elements of the task model.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

// Tasks.
// ------
#define TASK_SW_TIMERS 11
#define TASK_MAIN 12
#define TASK_BUTTON 13
#define TASK_LCD 14
#define TASK_UPDATE_DISPLAY 15
#define TASK_SERIAL 16
#define TASK_KEYBOARD 17

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21

// Shared State Memory.
// --------------------


// Shared Event Buffers.
// ---------------------
#define SEB_BUTTON_EVENT 41
#define SEB_TO_BUTTON 42 // Time Out
#define SEB_TO_SECOND 43 // Time Out
#define SEB_SERIAL_EVENT 44
#define SEB_KEYBOARD_EVENT 45

// Software Timers.
// ----------------
#define ST_BUTTON   1
#define ST_SECOND   2
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif /* _TMODEL_H_ */
