/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: events.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Defines the events of the task model.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef EVENTS_H_
#define EVENTS_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
// Events.
// -------

// General Events
// --------------
#define GE_NO_EVENT      0

// Button Events
// -------------
#define BE_SINGLE_PUSH   1
#define BE_DOUBBLE_PUSH  2
#define BE_LONG_PUSH     3

// Serial Events
// -------------
#define SE_RX            4
#define SE_TX            5

// Keyboard Events
// ---------------
#define KE_KEY_PRESSED   6

// Timer Events
// ------------
#define TE_TIMEOUT      10
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif /*EVENTS_H_*/
