/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: swtimers.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Very basic FIFO buffer for storing characters which will be written
*              to the LCD later
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
#define QUEUE_LEN   128

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void queue_put(INT8U newElem);
/*****************************************************************************
*   Input    : -Element to insert into the buffer
*   Output   : -
*   Function : Function for putting characters into buffer
******************************************************************************/

INT8U queue_get(void);
/*****************************************************************************
*   Input    : -
*   Output   : -Oldest element in the buffer
*   Function : Return oldest element and delete it from the buffer
******************************************************************************/

BOOLEAN queueHasData(void);
/*****************************************************************************
*   Input    : -
*   Output   : -FALSE if buffer has data, TRUE if not
*   Function : Function to check if FIFO buffer contains any characters.
*              Buffer MAY NOT be read from when empty
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /*QUEUE_H_*/
