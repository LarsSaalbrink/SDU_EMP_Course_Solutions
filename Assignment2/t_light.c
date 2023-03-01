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
#include "t_light.h"
#include "emp_type.h"
#include "io.h"
/***************** Defines ********************/
#define NOR_NIGHT_DELAY 1000U
#define RED_DELAY 2000U
#define REDYELLOW_DELAY 500U
#define GREEN_DELAY 2000U
#define YELLOW_DELAY 750U
#define OFF 0b00001110U        /*LED's off*/
#define RED 0b00001100U        /*Red*/
#define REDYELLOW 0b00001000U  /*Red + Yellow*/
#define GREEN 0b00000110U      /*Green*/
#define YELLOW 0b00001010U     /*Yellow*/
/***************** Constants ******************/
/***************** Variables ******************/
enum t_light_sm_state t_light_state = EMERGENCY;
enum colorstate_t_light colorstate = RED_STATE;
extern INT8U color_array[8];
extern volatile INT32U ticks;
/***************** Functions ******************/
void t_light(void)
{
    static INT32U delay_start = 0;
    static BOOLEAN blink_state = 0;

    switch(t_light_state)
    {
        case REGULAR:
            if(delay_start == 0){  //First entry into REGULAR state
                delay_start = ticks;
            }
            switch(colorstate){
                case RED_STATE:
                    if((ticks - delay_start) >= RED_DELAY)
                    {
                        delay_start = ticks;
                        colorstate = RED_YELLOW_STATE;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | REDYELLOW);
                    }
                    break;
                case RED_YELLOW_STATE:
                    if((ticks - delay_start) >= REDYELLOW_DELAY)
                    {
                        delay_start = ticks;
                        colorstate = GREEN_STATE;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | GREEN);
                    }
                    break;
                case GREEN_STATE:
                    if((ticks - delay_start) >= GREEN_DELAY)
                    {
                        delay_start = ticks;
                        colorstate = YELLOW_STATE;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | YELLOW);
                    }
                    break;
                case YELLOW_STATE:
                    if((ticks - delay_start) >= YELLOW_DELAY)
                    {
                        delay_start = ticks;
                        colorstate = RED_STATE;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | RED);
                    }
                    break;
            }
            break;
        case NOR_NIGHT:
            if(delay_start == 0){  //First entry into NOR_NIGHT state
                delay_start = ticks;
            }
            else if((ticks - delay_start) >= NOR_NIGHT_DELAY)
            {
                if(blink_state)
                {
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | YELLOW);
                }
                else
                {
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | OFF);
                }
                delay_start = ticks;
                blink_state = ~blink_state;
            }
            break;
        case EMERGENCY:
            GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & 0b11110001) | RED);
            break;
    }
}




