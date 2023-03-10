/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: io.c
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: .c for io related components
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230301  LS    Module created.
*
*****************************************************************************/
/***************** Include files **************/
#include "io.h"
/***************** Defines ********************/
/***************** Constants ******************/
/***************** Variables ******************/
volatile BOOLEAN sw1_pressed = 0;
/***************** Functions ******************/
void init_io(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    // Enable the GPIO port that is used for the on-board LEDs and switches.
    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
    dummy          = SYSCTL_RCGC2_R;  //Do a dummy read to insert a few
                                      //cycles after enabling the peripheral.

    //Enable LED
    GPIO_PORTF_DIR_R = 0x0E;  //Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DEN_R = 0x1E;  //Enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x10;  //Enable internal pull-up (PF4).

    //Enable external interrupt
    GPIO_PORTF_IS_R  &= ~(1<<4);  //Trigger on edges
    GPIO_PORTF_IEV_R &= ~(1<<4);  //Trigger on rising edges
    GPIO_PORTF_IM_R  |= (1<<4);   //Enable interrupt from pin PF4 specifically
    GPIO_PORTF_ICR_R |= 0x10;     //Clear interrupt flag
    NVIC_EN0_R       |= (1<<30);  //Enable interrupt IRQ30 (PORTF external interrupts)
}

void GPIOFHandler(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    sw1_pressed = 1;
    GPIO_PORTF_ICR_R |= 0x10; //clear the interrupt flag
}

/***************** End of module **************/

