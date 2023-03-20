/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: queue.c
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "queue.h"
#include "gpio.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
INT8U output_queue[QUEUE_LEN];  //Array used for FIFO buffer

//Current data is contained between these to indices
INT8U firstPos = 0;
INT8U lastPos = 0;

/*****************************   Functions   *******************************/
void queue_put(INT8U newCh)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    output_queue[lastPos] = newCh;
    ++lastPos;
    if(lastPos >= QUEUE_LEN)
    {
        lastPos = 0;
    }
}

INT8U queue_get(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    INT8U chToRet = output_queue[firstPos];
    output_queue[firstPos] = 0;
    ++firstPos;
    if(firstPos >= QUEUE_LEN)
    {
        firstPos = 0;
    }
    return chToRet;
}

BOOLEAN queueHasData(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    return (firstPos != lastPos);
}

/****************************** End Of Module *******************************/
