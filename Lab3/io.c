#include "io.h"

extern BOOLEAN button_pressed;
extern INT8U sw_num;

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

    //Enable LEDs

    GPIO_PORTF_LOCK_R = 0x4C4F434B;  // unlock GPIO Port F
    GPIO_PORTF_CR_R   = 0x1F;        // allow changes to PF4-0
    GPIO_PORTF_DIR_R  = 0x0E;        // Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DEN_R  = 0x1F;        // Enable the GPIO pins for digital function (PF0 - PF4)
    GPIO_PORTF_PUR_R  = 0x11;        // Enable internal pull-up (PF0 & PF4).

    //Enable external interrupts for PF0 & PF4

    GPIO_PORTF_IS_R  &= ~((1<<4) | (1<<0));  //Trigger on edges
    GPIO_PORTF_IEV_R &= ~((1<<4) | (1<<0));  //Trigger on rising edges
    GPIO_PORTF_IM_R  |=  ((1<<4) | (1<<0));  //Enable interrupt from pin PF0 & PF4 specifically
    GPIO_PORTF_ICR_R |=  0x10;               //Clear interrupt flag
    NVIC_EN0_R       |= (1<<30);             //Enable interrupt IRQ30 (PORTF external interrupts)
}

void GPIOFHandler(void)
/***********************************
* Input :   -External interrupt triggered by PORTF
* Output :  [No output]
* Function: Set "button_pressed" flag to true
***********************************/
{
    if(~GPIO_PORTF_DATA_R & 0b10000)
    {
        sw_num = 1;
        GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
    }
    else
    {
        sw_num = 2;
        GPIO_PORTF_ICR_R |= 0x1; /* clear the interrupt flag */
    }

}

