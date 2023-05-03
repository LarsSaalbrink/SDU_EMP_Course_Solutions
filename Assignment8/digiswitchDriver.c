/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230320  LS   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "digiswitchDriver.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/
void digiswitch_init(void)
{
  // Enable the GPIO port that is used for the keypad X-axis.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

  // Do a dummy read to insert a few cycles after enabling the peripherals.
  int dummy;
  dummy = SYSCTL_RCGC2_R;

  // Enable the GPIO pins for digital function
  GPIO_PORTA_DEN_R |= 0b11100000;

  //Enable external interrupts
  GPIO_PORTA_IS_R  &= ~(0b11100000);  //Trigger on edges
  GPIO_PORTA_IEV_R &= ~(0b11100000);  //Trigger on falling edges
  GPIO_PORTA_IM_R |= (0b11100000);    //Enable interrupt from pins PA5-PA7
  GPIO_PORTA_ICR_R |= 0x10;           //Clear interrupt flag
  NVIC_EN0_R |= (1<<0);               //Enable interrupt IRQ4 (PORTA external interrupts)
}

void digiswitch_handler(void)
{
  //Check which pin triggered the interrupt
  if((GPIO_PORTA_MIS_R & (0b10000000)))  //Pressing has higher priority than turning
  {
    digiswitch_event = DIGISWITCH_P2;
  }
  else if((GPIO_PORTA_MIS_R & (0b00100000))) //PA5
  {
    digiswitch_event = DIGISWITCH_A;
  }
  else if((GPIO_PORTA_MIS_R & (0b01000000)))  //PA6
  {
    digiswitch_event = DIGISWITCH_B;
  }

  //Clear interrupt when done
  GPIO_PORTA_ICR_R |= 0b11100000; /* clear the interrupt flags */
}

void Digiswitch_task(void *pvParameters)
{

}




