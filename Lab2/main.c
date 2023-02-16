#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"

#define TIM_1_SEC     200
extern int ticks;

/**
 * main.c
 */
int main(void)
{
    //A)
    /*
    INT16U var1 = 0xFFFF;

    while(1)
    {
        var1 &= ~(3<<5);
    }
    */

//---------------------------------------------------------------------------------------------------------

    //B)
    /*
    INT16U var2 = 0xFFFF;
    INT16U mask = 0x7E0;  //0b111 1110 0000

    while(1)
    {
        var2 = (var2 & (~mask)) | (0x1E << 5);  //0x1E = 0b01 1110
    }
    */

//---------------------------------------------------------------------------------------------------------

    //C)
    /*
    // Enable the GPIO port that is used for the on-board LEDs and switches.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    int dummy;
    dummy = SYSCTL_RCGC2_R;
    // Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DIR_R = 0x0E;

    // Enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_DEN_R = 0x1E;

    // Enable internal pull-up (PF4).
    GPIO_PORTF_PUR_R = 0x10;


    //Set up constant to loop through
    INT8U constant = 0x67;

    //Discrete color for all but two of the bits
    unsigned char colorArray[9] = {
                  0b00000000,
                  0b00000010,
                  0b00001000,
                  0b00000100,
                  0b00001100,
                  0b00000010,
                  0b00001010,
                  0b00000110,
                  0b00001110
    };
    INT8U bit_counter = 1;
    INT8U button_state = 0;



    // Loop forever.
    while(1)
    {
        if( GPIO_PORTF_DATA_R & 0x10 )
        {
            if(button_state)
            {
                button_state = 0;
            }
        }
        else
        {
            if(!button_state)
            {
                button_state = 1;
                ++bit_counter;
                if(bit_counter == 9)
                {
                    bit_counter = 1;
                }
            }
        }

        if(constant & (1<<(bit_counter-1)))  //If current bit is 1, turn on the LED's to produce the color matching the current position
        {
            GPIO_PORTF_DATA_R = colorArray[bit_counter];
        }
        else
        {
            GPIO_PORTF_DATA_R &= colorArray[0];
        }

    }
    */

//---------------------------------------------------------------------------------------------------------

    //D)
    // Enable the GPIO port that is used for the on-board LEDs and switches.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    int dummy;
    dummy = SYSCTL_RCGC2_R;
    // Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DIR_R = 0x0E;

    // Enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_DEN_R = 0x1E;

    // Enable internal pull-up (PF4).
    GPIO_PORTF_PUR_R = 0x10;


    //Set up constant to loop through
    INT8U constant = 0x67;

    //Discrete color for all but two of the bits
    unsigned char colorArray[9] = {
                      0b00000000,
                      0b00000010,
                      0b00001000,
                      0b00000100,
                      0b00001100,
                      0b00000010,
                      0b00001010,
                      0b00000110,
                      0b00001110
    };
    INT8U bit_counter = 1;
    INT8U button_state = 0;

    init_systick();


    // Loop forever.
    while(1)
    {
        ++bit_counter;
        if(bit_counter == 9)
        {
            bit_counter = 1;
        }

        if(constant & (1<<(bit_counter-1)))  //If current bit is 1, turn on the LED's to produce the color matching the current position
        {
            GPIO_PORTF_DATA_R = colorArray[bit_counter];
        }
        else
        {
            GPIO_PORTF_DATA_R = colorArray[0];
        }
        delay(TIM_1_SEC);
    }

	return 0;
}
