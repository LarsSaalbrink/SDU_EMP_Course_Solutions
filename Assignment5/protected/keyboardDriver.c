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
#include "protected/tm4c123gh6pm.h"
#include "protected/uart0.h"
#include "protected/messages.h"
#include "protected/systick.h"
#include "protected/keyboardDriver.h"
#include "protected/queue.h"
#include "tmodel.h"
#include "events.h"

/*****************************    Defines    *******************************/
/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/
const INT8U keys[3][4] = {{'1','4','7','*'},
                          {'2','5','8','0'},
                          {'3','6','9','#'}};
INT8U xPressed = 0;
INT8U yPressed = 0;
volatile INT8U yPin = 0;

/*****************************   Functions   *******************************/
void keyboard_init()
{
  // Enable the GPIO port that is used for the keypad Y-axis.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
  // Enable the GPIO port that is used for the keypad X-axis.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

  // Do a dummy read to insert a few cycles after enabling the peripherals.
  int dummy;
  dummy = SYSCTL_RCGC2_R;

  // Set the directions.
  GPIO_PORTE_DIR_R = 0b00000000;
  GPIO_PORTA_DIR_R = 0b00011100;

  // Enable the GPIO pins for digital function (PE0, PE1, PE2, PE3, PA2, PA3, PA4).
  GPIO_PORTE_DEN_R = 0b00001111;
  GPIO_PORTA_DEN_R = 0b00011100;

  // Enable NO internal pull-up (PE0, PE1, PE2, PE3).
  GPIO_PORTE_PUR_R = 0b00000000;

  // Set output to high (PA2, PA3, PA4).
  GPIO_PORTA_DATA_R = 0b00011100;

  //Enable external interrupt for keypad Y-axis
  GPIO_PORTE_IS_R  &= ~(0b00001111);  //Trigger on edges
  GPIO_PORTE_IEV_R |= (0b00001111);  //Trigger on rising edges
  GPIO_PORTE_IM_R |= (0b00001111);    //Enable interrupt from pins PFE0-PE3
  GPIO_PORTE_ICR_R |= 0x10;     //Clear interrupt flag
  NVIC_EN0_R |= (1<<4);        //Enable interrupt IRQ4 (PORTE external interrupts)
}

void keyboard_handler(void)
{
  //Figure out which pin triggered the interrupt
  yPin = GPIO_PORTE_MIS_R & 0b00001111;

  GPIO_PORTE_ICR_R |= 0b00001111; /* clear the interrupt flags */
  NVIC_EN0_R &= ~(1<<4);        //Disable the interrupt to avoid contact bouncing triggering it again
}

void keyboard_task( INT8U task_no )
{
  static INT8U bufferContent = 0;
  if(yPin) {
    //Convert yPressed to a number switch
    switch(yPin) {
      case 0b00000001:
        yPressed = 4;
        break;
      case 0b00000010:
        yPressed = 3;
        break;
      case 0b00000100:
        yPressed = 2;
        break;
      case 0b00001000:
        yPressed = 1;
        break;
    }

    GPIO_PORTA_DATA_R = 0b00011000;
    if (!(GPIO_PORTE_DATA_R & 0b00001111)) {
      xPressed = 3;
    }
    GPIO_PORTA_DATA_R = 0b00010100;
    if (!(GPIO_PORTE_DATA_R & 0b00001111)) {
      xPressed = 2;
    }
    GPIO_PORTA_DATA_R = 0b00001100;
    if (!(GPIO_PORTE_DATA_R & 0b00001111)) {
      xPressed = 1;
    }
    GPIO_PORTA_DATA_R = 0b00011100;  //Reset X-axis pins to high

    delay_ms_systick(150);       //Wait for any potential contact bouncing to dissapate
    NVIC_EN0_R |= (1<<4);        //Re-enable interrupt IRQ4 (PORTE external interrupts)
    yPin = 0;

    queue_put(1,keys[xPressed-1][yPressed-1]);  //Use queue number 1 for keyboard events
    ++bufferContent;

    if(bufferContent == 4) {  //Send key to the message queue
      put_msg_event(SEB_KEYBOARD_EVENT, KE_KEY_PRESSED);
      bufferContent = 0;
    }
  }
}





