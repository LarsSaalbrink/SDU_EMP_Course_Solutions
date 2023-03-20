/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: Assignment 4
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230320  LS   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "protected/tm4c123gh6pm.h"
#include "protected/uart0.h"
#include "protected/messages.h"
#include "tmodel.h"
#include "events.h"
#include "serialDriver.h"

/*****************************    Defines    *******************************/
enum state {SETCLOCK, GETCLOCK};
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void serial_task( INT8U task_no )
{
    static BOOLEAN active = 0;
    static INT8U byteCounter = 0;
    static enum state serialState = SETCLOCK;
    //static INT8U dataBuffer[6];

    //For testing
    // if(serialState == SETCLOCK)
    // {
    // dataBuffer[0] = '1';
    // dataBuffer[1] = '2';
    // dataBuffer[2] = '3';
    // dataBuffer[3] = '4';
    // dataBuffer[4] = '5';
    // dataBuffer[5] = '6';
    // }

    if(active)
    {
        if(serialState == GETCLOCK)
        {
            if(uart0_tx_rdy())
            {
                uart0_putc(dataBuffer[byteCounter]);
                ++byteCounter;
                if(byteCounter == 6)
                {
                    active = 0;
                }
            }
        }
        else if(serialState == SETCLOCK)
        {
            if(uart0_rx_rdy())
            {
                dataBuffer[byteCounter] = uart0_getc();
                ++byteCounter;
                if(byteCounter == 6)
                {
                    active = 0;
                    put_msg_event( SEB_SERIAL_EVENT, SE_RX);
                }
            }
        }
    }
    else if(uart0_rx_rdy())
    {
        INT8U data = uart0_getc();

        //Get ready for the new command
        if(data == '1')
        {
            serialState = SETCLOCK;
            active = 1;
            byteCounter = 0;
        }
        else if(data == '2')
        {
            serialState = GETCLOCK;
            active = 1;
            byteCounter = 0;
            put_msg_event( SEB_SERIAL_EVENT, SE_TX);
        }
    }
}



//Ide:
//Communikation til update_display() i main skal ske gennem
//events




