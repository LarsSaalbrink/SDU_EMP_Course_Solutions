/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: swtimers.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Function for distinguishing between different types of button
*              presses and triggering the appropriate event
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT8U select_button(void);
/*****************************************************************************
*   Input    : -
*   Output   : Button Event
*   Function : Function for reading SW1
******************************************************************************/

void button_task( INT8U );
/*****************************************************************************
*   Input    : -Dummy input for debugging
*   Output   : -
*   Function : Function for interpreting type of button press
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /*BUTTON_H_*/
