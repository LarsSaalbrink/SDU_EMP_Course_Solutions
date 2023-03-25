/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: KeyboardDriver.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
*
*****************************************************************************/

#ifndef _SERIAL_DRIVER_H
  #define _SERIAL_DRIVER_H

/***************************** Include files *******************************/
#include "protected/emp_type.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/
INT8U keyboardDataBuffer[80];

/*****************************   Functions   *******************************/
void keyboard_handler(void);
void keyboard_task( INT8U task_no );



#endif /* _SERIAL_DRIVER_H */
