/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: Lab 3
*
* DESCRIPTION: main.c of Lab 3 project
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230227  LS    Module created.
*
*****************************************************************************/
/***************** Include files **************/
#include "io.h"
#include "lab3_header.h"
#include "emp_type.h"

/***************** Defines ********************/
/***************** Constants ******************/
//From assignment description

/***************** Variables ******************/
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

INT8U counter = 0;
INT8U sw_num = 0;

enum state_machine
{
    S1, S2, S3, S4, S5, UNLOCKED
};
enum state_machine sm = S1;
/***************** Functions ******************/


int main(void)
/***********************************
* Input :   -
* Output :  -
* Function: main() function
***********************************/
{
    unsigned char bitmask = 0b11110001;

    //Configure registers
    init_io();
    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[4]);  //Red

    // Loop forever.
    while(1){
        if((sw_num == 1U) || (sw_num == 2U))  //If button was pressed
        {
            switch(sm){
                case S1:
                    if(sw_num == 1)
                    {
                        ++counter;
                    }
                    ++sm;
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[5]);  //Yellow
                    break;
                case S2:
                    if(sw_num == 2)
                    {
                        ++counter;
                    }
                    ++sm;
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[6]);  //Magenta
                    break;
                case S3:
                    if(sw_num == 2)
                    {
                        ++counter;
                    }
                    ++sm;
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[7]);  //White
                    break;
                case S4:
                    if(sw_num == 1)
                    {
                        ++counter;
                    }
                    ++sm;
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[2]);  //Blue
                    break;
                case S5:
                    if((sw_num == 2) && (counter == 4))
                    {
                        ++sm;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[1]);  //Green
                    }
                    else
                    {
                        counter = 0;
                        sm = S1;
                        GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[4]);  //Red
                    }
                    break;
                case UNLOCKED:
                    counter = 0;
                    sm = S1;
                    GPIO_PORTF_DATA_R = ((GPIO_PORTF_DATA_R & bitmask) | colorArray[4]);  //Red
                    break;
            }
            sw_num = 0;
        }
    }
    return (0);
}
/******************************* End Of Module **************************/
