/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: Assignment 2
*
* DESCRIPTION: main.c of Assignment 2 project
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
#include "systick.h"
#include "emp_type.h"
#include "driver.h"
#include "io.h"
#include "t_light.h"

/***************** Defines ********************/
/***************** Constants ******************/
/***************** Variables ******************/
extern volatile INT32U       ticks;
extern volatile BOOLEAN      sw1_pressed;
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
    __asm(" cpsid i");  //Disable global interrupts.
    init_systick();
    init_io();
    __asm(" cpsie i");  //Enable global interrupts.

    // Loop forever.
    while(1){
        read_sw1(&t_light_state);
        t_light_sm();
    }
    return (0);
}
/******************************* End Of Module **************************/
