/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Assignment 3, main module.
*
* Change Log:
*****************************************************************************
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
#include "protected/swtimers.h"
#include "protected/systick.h"
#include "protected/gpio.h"
#include "protected/messages.h"
#include "protected/devices.h"
#include "protected/leds.h"
#include "protected/lcd.h"
#include "protected/uart0.h"
#include "protected/keyboardDriver.h"
#include "serialDriver.h"
#include "button.h"
#include "events.h"
#include "tmodel.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern volatile INT16S ticks;
INT16S alive_timer = MILLISEC(500);

extern INT8U dataBuffer[6];

/*****************************   Functions   *******************************/

void update_display( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for operating LCD display as digital clock
******************************************************************************/
{
  static INT8U secs, mins, hrs = 0;
  static INT8U butt_ev, serial_ev, keypad_ev;
  static BOOLEAN colon_state = 1;
  static BOOLEAN incrDir = 1;
  static BOOLEAN update = 1;

  butt_ev = get_msg_event(SEB_BUTTON_EVENT);
  if(butt_ev)
  {
    update = 1;

    switch(butt_ev)
    {
      case BE_SINGLE_PUSH:
        mins += (incrDir ? 1 : -1);
        break;
      case BE_DOUBBLE_PUSH:
        incrDir = !incrDir;
        break;
      case BE_LONG_PUSH:
        start_swtimer( ST_SECOND, SEB_TO_SECOND, MILLISEC( 1000 ) );   // start 1 second timer
        break;
    }
  }

  serial_ev = get_msg_event(SEB_SERIAL_EVENT);
  if(serial_ev)
  {
    update = 1;

    switch(serial_ev)
    {
      case SE_RX:
        hrs = ((dataBuffer[0]-48)*10) + (dataBuffer[1]-48);
        mins = ((dataBuffer[2]-48)*10) + (dataBuffer[3]-48);
        secs = ((dataBuffer[4]-48)*10) + (dataBuffer[5]-48);
        break;
      case SE_TX:
          dataBuffer[0] = (hrs/10) + 48;
          dataBuffer[1] = (hrs%10) + 48;
          dataBuffer[2] = (mins/10) + 48;
          dataBuffer[3] = (mins%10) + 48;
          dataBuffer[4] = (secs/10) + 48;
          dataBuffer[5] = (secs%10) + 48;
        break;
    }
  }

  keypad_ev = get_msg_event(SEB_KEYBOARD_EVENT);
  if(keypad_ev)
  {
    update = 1;

    //Get user input from queue 1
    hrs = ((queue_get(1) - 48) * 10) + (queue_get(1) - 48);
    mins = ((queue_get(1) - 48) * 10) + (queue_get(1) - 48);
  }

  if(get_msg_event(SEB_TO_SECOND))  //SEB_TO_SECOND is timeout
  {
    update = 1;
    start_swtimer( ST_SECOND, SEB_TO_SECOND, MILLISEC( 1000 ) );   // start 1 second timer

    if(secs >= 60)
    {
      secs = 0;
      ++mins;
    }
    else
    {
      ++secs;
    }

    wr_ch_LCD(ESC);
    wr_ch_LCD(0b10000010);  //Return cursor to pos 2
    if( colon_state )
    {
        wr_ch_LCD(':');
    }
    else
    {
         wr_ch_LCD(' ');
    }
    colon_state = !colon_state;
  }

  if(update)
  {
    update = 0;
    if(mins == 255)
    {
      mins = 59;
      --hrs;
    }
    else if(mins >= 60)
    {
        mins = 0;
        ++hrs;
    }

    if(hrs == 255)
    {
      hrs = 23;
    }
    else if(hrs > 23)
    {
      hrs = 0;
    }
      wr_ch_LCD(ESC);
      wr_ch_LCD(0b10000000);    //Return cursor to pos 0
      wr_ch_LCD((hrs/10)+48);
      wr_ch_LCD((hrs%10)+48);
      wr_ch_LCD(ESC);
      wr_ch_LCD(0b10000011);    //Jump cursor to pos 3
      wr_ch_LCD((mins/10)+48);
      wr_ch_LCD((mins%10)+48);
  }
}

int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  disable_global_int();
  init_systick();
  init_gpio();
  keyboard_init();
  uart0_init( 19200, 8, 1, 0);
  enable_global_int();

  start_swtimer( ST_SECOND, SEB_TO_SECOND, MILLISEC( 1000 ) );

  // Loop forever.
  while(1)
  {
    // System part of the super loop.
    // ------------------------------
    while(ticks < 5);


    // The following will be executed every 5mS
    ticks -= 5;

    if( ! --alive_timer )
    {
    alive_timer =   MILLISEC( 500 );
      GPIO_PORTD_DATA_R ^= 0x40;
    }

    // Protected operating system mode
    swt_ctrl();                         // task controlling the timers
    lcd_task( TASK_LCD );               // LCD display driver

    // Application mode
    button_task( TASK_BUTTON );
    delay_ms_systick(1);
    update_display( TASK_UPDATE_DISPLAY );
    //serial_task( TASK_SERIAL );  //No serial for assignment 5
    keyboard_task( TASK_KEYBOARD );
  }
}

/****************************** End Of Module *******************************/
