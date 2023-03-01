/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: driver.c
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: Driver to interpret input from switch 1.
*              Uses "sw1_pressed" flag from io.c
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
#include "driver.h"
#include "t_light.h"
#include "io.h"
/***************** Defines ********************/
#define CONTACT_BOUNCE_DELAY 50U
#define D_PRESS_TOTAL        200U
#define D_PRESS_DELAY        (D_PRESS_TOTAL - CONTACT_BOUNCE_DELAY)
#define LONG_PRESS_DELAY     (2000U - D_PRESS_DELAY)
/***************** Constants ******************/
/***************** Variables ******************/
extern volatile INT32U  ticks;
extern volatile BOOLEAN sw1_pressed;
/***************** Functions ******************/
void start_t_light(INT32U* delay_start,
                   volatile BOOLEAN* sw1_pressed,
                   enum driver_sm_state* driver_state)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if(*sw1_pressed)
    {
        *sw1_pressed = 0;
        *delay_start = ticks;  //Get timestamp
        *driver_state = CONTACT_BOUNCE;
    }
}

void wait_for_contact_bounce(volatile INT32U* ticks,
                             INT32U* delay_start,
                             volatile BOOLEAN* sw1_pressed,
                             enum driver_sm_state* driver_state)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if((*ticks - *delay_start) >= CONTACT_BOUNCE_DELAY)  //Wait for contact-bounce delay to pass
    {
        *sw1_pressed = 0;       //Discard any press provoked by contact bouncing
        *delay_start = *ticks;  //Get timestamp
        *driver_state = D_CLICK;
    }
}

void identify_press_type(volatile INT32U* ticks,
                         INT32U* delay_start,
                         volatile BOOLEAN* sw1_pressed,
                         enum driver_sm_state* driver_state,
                         enum t_light_sm_state* t_light_state)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if((*ticks - *delay_start) >= D_PRESS_DELAY)  //Wait for double press delay to pass
    {
        if(*sw1_pressed)                  //Double press occurred
        {
            *sw1_pressed = 0;
            *t_light_state = EMERGENCY;   //Buttons was double pressed -> red light
            *driver_state = FIRST_PRESS;  //Reset state
        }
        //Check for long hold
        else if(!(GPIO_PORTF_DATA_R & 0x10))  //User is holding button
        {
            *delay_start = *ticks;        //Get timestamp
            *driver_state = LONG_WAIT;
        }
        else
        {
            *t_light_state = NOR_NIGHT;   //Button was pressed once -> yellow blink
            *driver_state = FIRST_PRESS;  //Reset state
        }
    }
}

void did_longpress_complete(volatile INT32U* ticks,
                            INT32U* delay_start,
                            enum driver_sm_state* driver_state,
                            enum t_light_sm_state* t_light_state)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if((*ticks - *delay_start) >= LONG_PRESS_DELAY)  //Wait for double press delay to pass
    {
        if(!(GPIO_PORTF_DATA_R & 0x10))  //User is still holding button
        {
            *t_light_state = REGULAR;    //Button was held for 2 seconds -> regular traffic light
        }
        *driver_state = FIRST_PRESS;     //Reset state
    }
}

void read_sw1(enum t_light_sm_state* t_light_state)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    static enum driver_sm_state driver_state = FIRST_PRESS;
    static INT32U delay_start = 0;

    switch(driver_state)
    {
        case FIRST_PRESS:
            start_t_light(&delay_start, &sw1_pressed, &driver_state);
            break;

        case CONTACT_BOUNCE:
            wait_for_contact_bounce(&ticks, &delay_start, &sw1_pressed, &driver_state);
            break;

        case D_CLICK:
            identify_press_type(&ticks, &delay_start, &sw1_pressed, &driver_state, t_light_state);
            break;

        case LONG_WAIT:
            did_longpress_complete(&ticks, &delay_start, &driver_state, t_light_state);
            break;
    }
}

/***************** End of module **************/
