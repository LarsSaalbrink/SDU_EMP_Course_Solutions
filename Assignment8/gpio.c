/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: gpio.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "systick_frt.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_gpio(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  int dummy;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as output (PF1, PF2 and PF3).
  GPIO_PORTF_DIR_R = 0x0E;
  // Set the direction as output (PD2, PD3, PD6).
  GPIO_PORTD_DIR_R = 0b01001100;
  // Set the direction as output (PC4, PC5, PC6, PC7).
  GPIO_PORTC_DIR_R = 0b11110000;

  // Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
  GPIO_PORTF_DEN_R = 0x1F;
  // Enable the GPIO pins for digital function (PD2, PD3, PD6).
  GPIO_PORTD_DEN_R = 0b01001100;
  // Enable the GPIO pins for digital function (PC4, PC5, PC6, PC7).
  GPIO_PORTC_DEN_R = 0b11110000;

  // Enable internal pull-up (PF0 and PF4).
  GPIO_PORTF_PUR_R = 0x11;

  //Set starting state of PD2 and PD3 to LOW
  GPIO_PORTD_DATA_R &= 0b11110011;
}

/****************************** End Of Module *******************************/
