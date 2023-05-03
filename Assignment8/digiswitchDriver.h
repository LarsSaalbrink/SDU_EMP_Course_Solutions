/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: digiswitchDriver.h
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

#ifndef _DIGISWITCH_DRIVER_H
  #define _DIGISWITCH_DRIVER_H

/***************************** Include files *******************************/
#include "emp_type.h"

/*****************************    Defines    *******************************/
enum digiswitch_ev {
  DIGISWITCH_A,
  DIGISWITCH_B,
  DIGISWITCH_P2,
  DIGISWITCH_NONE
};

/*****************************   Constants   *******************************/
volatile enum digiswitch_ev digiswitch_event;

/*****************************   Functions   *******************************/
void digiswitch_handler(void);
void Digiswitch_task(void *pvParameters);



#endif /* _DIGISWITCH_DRIVER_H */
