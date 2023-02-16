/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: A1Header.h
*
* PROJECT....: Assignment 1
*
* DESCRIPTION: Header for main.c of Assignment 1 project
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230216  LS    Module created.
*
*****************************************************************************/
#ifndef _A1HEADER_H
#define _A1HEADER_H
/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
/*****************************   Functions   *******************************/
void update_leds(INT8U* color_counter, BOOLEAN* dir_color_counter);
/***********************************
* Input :   -Pointer to counter variable keeping track of current color
*           -Pointer to variable indicating whether to increment or decrement
* Output :  [No output]
* Function: Update the output pins connected to RGB-leds to match the current program state
***********************************/

void does_user_want_auto_mode(BOOLEAN* auto_mode);
/***********************************
* Input :   -Pointer to variable indicating if auto mode is currently active
* Output :  [No output]
* Function: Analyse user input to determine whether they double-clicked or pressed for 2+ seconds
***********************************/

void handle_auto_mode(INT8U* auto_delay_counter_short, INT8U* color_counter, BOOLEAN* dir_color_counter);
/***********************************
* Input :   -Pointer to variable holding the delay duration between auto mode color changes (milliseconds)
*           -Pointer to counter variable keeping track of current color
*           -Pointer to variable indicating whether to increment or decrement
* Output :  [No output]
* Function: Update LED's when in auto mode without freezing the rest of main()
***********************************/

#endif //_A1HEADER_H
/***************** End of module **************/
