/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: Assignment 1
*
* DESCRIPTION: main.c of Assignment 1 project
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230216  LS    Module created.
*
*****************************************************************************/
/***************** Include files **************/
#include "io.h"
#include "systick.h"
#include "A1Header.h"
#include "emp_type.h"

/***************** Defines ********************/
/***************** Constants ******************/
//From assignment description
#define CONTACT_BOUNCE_DELAY 50U
#define D_CLICK_DELAY (200U - CONTACT_BOUNCE_DELAY)
#define AUTO_BLINK_DELAY 200U
#define AUTO_ACTIVATION_DELAY (2000U - D_CLICK_DELAY)
/***************** Variables ******************/
BOOLEAN button_pressed = 0;

INT8U colorArray[8] = {
      0b00000000, /*LED's off*/
      0b00001000, /*Green*/
      0b00000100, /*Blue*/
      0b00001100, /*Cyan*/
      0b00000010, /*Red*/
      0b00001010, /*Yellow*/
      0b00000110, /*Magenta*/
      0b00001110  /*White*/
};
/***************** Functions ******************/
void update_leds(INT8U* color_counter, BOOLEAN* dir_color_counter)
/***********************************
* Input :   -Pointer to counter variable keeping track of current color
*           -Pointer to variable indicating whether to increment or decrement
* Output :  [No output]
* Function: Update the output pins connected to RGB-leds to match the current program state
***********************************/
{
    if(*dir_color_counter)  //When counting down
    {
        --(*color_counter);
        if((*color_counter) == 255)
        {
            (*color_counter) = 7;
        }
    }
    else                   //When counting up
    {
        ++(*color_counter);
        if((*color_counter) == 8)
        {
            (*color_counter) = 0;
        }
    }

    unsigned char bitmask = 0b11110001;
    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[*color_counter]);
}

void does_user_want_auto_mode(BOOLEAN* auto_mode)
/***********************************
* Input :   -Pointer to variable indicating if auto mode is currently active
* Output :  [No output]
* Function: Analyse user input to determine whether they double-clicked or pressed for 2+ seconds
***********************************/
{
    unsigned int auto_delay_counter_long = 0;
    unsigned char activated = 0;

    while((!(GPIO_PORTF_DATA_R & 0x10)) && (!activated))
    {
        delay(1);
        ++auto_delay_counter_long;

        if(auto_delay_counter_long >= AUTO_ACTIVATION_DELAY)  //if 2 seconds have passed since button was pressed
        {
            *auto_mode = ~(*auto_mode);  //Enable auto mode
            activated = 1;
        }
    }
}

void handle_auto_mode(INT8U* auto_delay_counter_short, INT8U* color_counter, BOOLEAN* dir_color_counter)
/***********************************
* Input :   -Pointer to variable holding the delay duration between auto mode color changes (milliseconds)
*           -Pointer to counter variable keeping track of current color
*           -Pointer to variable indicating whether to increment or decrement
* Output :  [No output]
* Function: Update LED's when in auto mode without freezing the rest of main()
***********************************/
{
    delay(1);
    ++(*auto_delay_counter_short);

    if(*auto_delay_counter_short >= AUTO_BLINK_DELAY)
    {
        *auto_delay_counter_short = 0;
        update_leds(color_counter, dir_color_counter);
    }
}

int main(void)
/***********************************
* Input :   -
* Output :  -
* Function: main() function
***********************************/
{
    //Configure registers
    init_systick();
    init_io();

    BOOLEAN auto_mode, dir_color_counter = 0;
    INT8U auto_delay_counter_short, color_counter = 0;

    // Loop forever.
    while(1){
        if(button_pressed)
        {
            auto_mode = 0;
            delay(CONTACT_BOUNCE_DELAY);
            button_pressed = 0;
            delay(D_CLICK_DELAY);

            if(button_pressed)                    //Double click occurred
            {
                button_pressed = 0;
                dir_color_counter = ~dir_color_counter;  //Change direction
            }
            else if(!(GPIO_PORTF_DATA_R & 0x10))  //User is holding button
            {
                does_user_want_auto_mode(&auto_mode);
            }
            else                                  //Regular click
            {
                update_leds(&color_counter, &dir_color_counter);
            }
        }

        if(auto_mode)
        {
            handle_auto_mode(&auto_delay_counter_short, &color_counter, &dir_color_counter);
        }
    }
    return (0);
}
/******************************* End Of Module **************************/
