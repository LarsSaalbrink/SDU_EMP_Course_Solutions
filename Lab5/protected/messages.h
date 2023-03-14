/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: messages.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Functions for managing messages of the task-driven system
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef _MESSAGES_H
  #define _MESSAGES_H

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT8U get_msg_event( INT8U );
/*****************************************************************************
*   Input    : -Index for which event to get
*   Output   : -The event at the given index
*   Function : Getter function for reading and resetting event
******************************************************************************/

void put_msg_event( INT8U, INT8U );
/*****************************************************************************
*   Input    : -Index of which event to trigger
*              -ID of which event to put at the index
*   Output   : -
*   Function : Setter function for inserting events into event buffer
******************************************************************************/

INT8U get_msg_state( INT8U );
/*****************************************************************************
*   Input    : -Index for which state to get
*   Output   : -The state at the given index
*   Function : Getter function for reading and resetting state
******************************************************************************/

void put_msg_state( INT8U, INT8U );
/*****************************************************************************
*   Input    : -Index of which state to trigger
*              -ID of which state to put at the index
*   Output   : -
*   Function : Setter function for inserting events into state buffer
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /*_MESSAGES_H*/
