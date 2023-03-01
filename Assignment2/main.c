//PLAN:
/*
 * -Default to emergency state
 * -Press to activate "norwegian night" mode
 * -Change program flow to accept all commands from "driver" (dummy state for traffic light)
 *  Brug hans fixed interval code til at køre Traffic light SM'en, spam buttonhandler resten af tiden
 * -Implement traffic light state
 * -"delay_start" fra t_light.c skal resettes til 0 ved stateskift!
 * -Figure out how to disable global interrupts before config (look at his example code?)
 * -Split up large functions into smaller units
 *
 * -Clean up unused variables & defines
 * -Ret alle headers / commentarer
 * -Judge needed size of "ticks" variable
 *
 */








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
#include "systick.h"
#include "emp_type.h"
#include "driver.h"

/***************** Defines ********************/
/***************** Constants ******************/
//From assignment description
#define CONTACT_BOUNCE_DELAY 50U
#define D_CLICK_DELAY (200U - CONTACT_BOUNCE_DELAY)
#define AUTO_BLINK_DELAY 200U
#define AUTO_ACTIVATION_DELAY (2000U - D_CLICK_DELAY)
/***************** Variables ******************/
extern volatile INT32U ticks;

extern BOOLEAN sw1_pressed;

INT8U color_state = 1;

extern enum t_light_sm_state t_light_state;
/***************** Functions ******************/


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

    // Loop forever.
    while(1){
        read_sw1(&t_light_state);
        t_light();
    }
    return (0);
}
/******************************* End Of Module **************************/
