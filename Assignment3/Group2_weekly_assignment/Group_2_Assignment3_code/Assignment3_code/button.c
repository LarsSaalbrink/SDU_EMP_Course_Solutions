/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: button.c
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
#include "protected/tm4c123gh6pm.h"
#include "protected/emp_type.h"
#include "events.h"
#include "button.h"
#include "protected/swtimers.h"
#include "tmodel.h"
#include "protected/messages.h"

/*****************************    Defines    *******************************/
#define BS_IDLE           0
#define BS_FIRST_PUSH     1
#define BS_FIRST_RELEASE  2
#define BS_SECOND_PUSH    3
#define BS_LONG_PUSH      4

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
INT8U button_pushed()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4
}

void button_task( INT8U task_no )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  static INT8U  button_state = BS_IDLE;
         INT8U  time_out;

  time_out = get_msg_event( SEB_TO_BUTTON );

  switch( button_state )
  {
    case BS_IDLE:
        if( button_pushed( ))                                           // if button pushed
        {
          button_state = BS_FIRST_PUSH;                                 // we go from the idle state to first push
          start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC(2000) );    // we set a timer of 2s to see if this is a long push
        }
        break;
    case BS_FIRST_PUSH:
        if( time_out )                                                  // if the timer runs out before the button was released it was a long push
        {
          button_state = BS_LONG_PUSH;
          put_msg_event( SEB_BUTTON_EVENT, BE_LONG_PUSH );
        }
        else
        {
        if(  !button_pushed( ) )                                        // if button released before the timer runs out it was a normal push
        {
            button_state = BS_FIRST_RELEASE;
            start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC(100) );   // we set a new timer to see if the button is pressed again shortly after (double push)
        }
        }
        break;
    case BS_FIRST_RELEASE:
        if( time_out )                                                  // if the timer runs out without the button being pushed again it was a single push
        {
          button_state = BS_IDLE;
        put_msg_event( SEB_BUTTON_EVENT, BE_SINGLE_PUSH );
        }
        else
        {
        if(  button_pushed(  ))                                         // if button is pressed again before the timer runs out it was a double push
            {
            button_state = BS_SECOND_PUSH;
          start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC( 2000 ));   // we set a new timer to see if it is a long push
        }
        }
        break;
    case BS_SECOND_PUSH:
        if( time_out )                                                  // if the timer runs out before button is released it was a long push
        {
          button_state = BS_LONG_PUSH;
        put_msg_event( SEB_BUTTON_EVENT, BE_LONG_PUSH );
      }
        else
        {
        if( ! button_pushed( ) )                                        // if button released before the timer runs out it was a double push
            {
            button_state = BS_IDLE;
            put_msg_event( SEB_BUTTON_EVENT, BE_DOUBBLE_PUSH );
        }
        }
        break;
    case BS_LONG_PUSH:
        if( ! button_pushed(  ) )                                      // when the button is released after a long push we go back to the idle state
          button_state = BS_IDLE;
        break;
    default:
      break;
  }
}

/****************************** End Of Module *******************************/
