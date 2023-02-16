#include "io.h"

extern BOOLEAN button_pressed;

void init_io(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the PORTF external interrupt and configure it
*              to trigger on PF4 rising edges
******************************************************************************/
{
    // Enable the GPIO port that is used for the on-board LEDs and switches.
    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
    dummy = SYSCTL_RCGC2_R;  // Do a dummy read to insert a few cycles after enabling the peripheral.

    //Enable LED
    GPIO_PORTF_DIR_R = 0x0E;  // Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DEN_R = 0x1E;  // Enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x10;  // Enable internal pull-up (PF4).

    //Enable external interrupt
    GPIO_PORTF_IS_R  &= ~(1<<4);  //Trigger on edges
    GPIO_PORTF_IEV_R &= ~(1<<4);  //Trigger on rising edges
    GPIO_PORTF_IM_R |= (1<<4);    //Enable interrupt from pin PF4 specifically
    GPIO_PORTF_ICR_R |= 0x10;     //Clear interrupt flag
    NVIC_EN0_R |= (1<<30);        //Enable interrupt IRQ30 (PORTF external interrupts)
}

void GPIOFHandler(void)
/***********************************
* Input :   -External interrupt triggered by PORTF
* Output :  [No output]
* Function: Set "button_pressed" flag to true
***********************************/
{
    button_pressed = 1;
    GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
}

