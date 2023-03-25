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
INT8U output_queue[NUM_OF_QUEUES][QUEUE_LEN];  //Array used for FIFO buffer

//Current data is contained between these to indices
INT8U firstPos[NUM_OF_QUEUES] = {0};
INT8U lastPos[NUM_OF_QUEUES] = {0};

/*****************************   Functions   *******************************/
void queue_put(INT8U queueNum, INT8U newCh)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    output_queue[queueNum][lastPos[queueNum]] = newCh;
    ++lastPos[queueNum];
    if(lastPos[queueNum] >= QUEUE_LEN)
    {
        lastPos[queueNum] = 0;
    }
}

INT8U queue_get(INT8U queueNum)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if(firstPos[queueNum] != lastPos[queueNum])  //If data is available
    {
        INT8U chToRet = output_queue[queueNum][firstPos[queueNum]];
        output_queue[queueNum][firstPos[queueNum]] = 0;
        ++firstPos[queueNum];
        if(firstPos[queueNum] >= QUEUE_LEN)
        {
            firstPos[queueNum] = 0;
        }
    return chToRet;
    }
}

BOOLEAN queueHasData(INT8U queueNum)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    return (firstPos[queueNum] != lastPos[queueNum]);
}

/****************************** End Of Module *******************************/
