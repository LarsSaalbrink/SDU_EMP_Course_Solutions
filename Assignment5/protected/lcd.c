/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
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
#include "lcd.h"
#include "tmodel.h"
#include "systick.h"
#include "queue.h"

/*****************************    Defines    *******************************/
enum LCD_states
{
  LCD_POWER_UP,
  LCD_INIT,
  LCD_READY,
  LCD_ESC_RECEIVED,
};

/*****************************   Constants   *******************************/
const INT8U LCD_init_sequense[]= 
{
  0x30,		// Reset
  0x30,		// Reset
  0x30,		// Reset
  0x20,		// Set 4bit interface
  0x28,		// 2 lines Display
  0x0C,		// Display ON, Cursor OFF, Blink OFF
  0x06,		// Cursor Increment
  0x01,		// Clear Display
  0x02,     // Home
  0xFF		// stop
}; 

/*****************************   Variables   *******************************/

enum LCD_states LCD_state = LCD_POWER_UP;
INT8U LCD_init;

/*****************************   Functions   *******************************/
void wr_ch_LCD( INT8U Ch )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    queue_put(0,Ch);
}

void wr_str_LCD( INT8U *pStr )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  while( *pStr )
  {
    wr_ch_LCD( *pStr );
	pStr++;
  }
}

void move_LCD( INT8U x, INT8U y )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U Pos;

  Pos = y*0x40 + x;
  Pos |= 0x80;
  wr_ch_LCD( ESC );
  wr_ch_LCD( Pos );
}

void wr_ctrl_LCD_low( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write low part of control data to LCD.
******************************************************************************/
{
  INT8U temp;
  volatile int i;
  
  temp = GPIO_PORTC_DATA_R & 0x0F;
  temp  = temp | ((Ch & 0x0F) << 4);
  GPIO_PORTC_DATA_R  = temp;
  delay_ms_systick(1);
  GPIO_PORTD_DATA_R &= 0xFB;        // Select Control mode, write
  delay_ms_systick(1);
  GPIO_PORTD_DATA_R |= 0x08;		// Set E High

  delay_ms_systick(1);

  GPIO_PORTD_DATA_R &= 0xF7;		// Set E Low

  delay_ms_systick(1);
}

void wr_ctrl_LCD_high( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write high part of control data to LCD.
******************************************************************************/
{
  wr_ctrl_LCD_low(( Ch & 0xF0 ) >> 4 );
}

void out_LCD_low( INT8U Ch )
/*****************************************************************************
*   Input    : Mask
*   Output   : -
*   Function : Send low part of character to LCD.
*              This function works only in 4 bit data mode.
******************************************************************************/
{
  INT8U temp;

  temp = GPIO_PORTC_DATA_R & 0x0F;
  GPIO_PORTC_DATA_R  = temp | ((Ch & 0x0F) << 4);
  GPIO_PORTD_DATA_R |= 0x04;        // Select data mode
  GPIO_PORTD_DATA_R |= 0x08;		// Set E High
  GPIO_PORTD_DATA_R &= 0xF7;		// Set E Low
}

void out_LCD_high( INT8U Ch )
/*****************************************************************************
*   Input    : Mask
*   Output   : -
*   Function : Send high part of character to LCD.
*              This function works only in 4 bit data mode.
******************************************************************************/
{
  out_LCD_low((Ch & 0xF0) >> 4);
}

void wr_ctrl_LCD( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/
{
  static INT8U Mode4bit = 0;

  wr_ctrl_LCD_high( Ch );
  if( Mode4bit )
  {
    delay_ms_systick(1);
	wr_ctrl_LCD_low( Ch );
  }
  else
  {
	if( (Ch & 0x30) == 0x20 )
	  Mode4bit = 1;
  }
}

void clr_LCD()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clear LCD.
******************************************************************************/
{
  wr_ctrl_LCD( 0x01 );
}


void home_LCD()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Return cursor to the home position.
******************************************************************************/
{
  wr_ctrl_LCD( 0x02 );
}

void Set_cursor( INT8U Ch )
/*****************************************************************************
*   Input    : New Cursor position
*   Output   : -
*   Function : Place cursor at given position.
******************************************************************************/
{
  wr_ctrl_LCD( Ch );
}


void out_LCD( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/
{
  out_LCD_high( Ch );
  out_LCD_low( Ch );
}

void lcd_task( task_no )
INT8U task_no;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U ch;

  switch( LCD_state )
  {
    case LCD_POWER_UP:
      LCD_init = 0;
      LCD_state = LCD_INIT;
      break;

    case LCD_INIT:
      if( LCD_init_sequense[LCD_init] != 0xFF )
        wr_ctrl_LCD( LCD_init_sequense[LCD_init++] );
      else
	  {
        LCD_state = LCD_READY;
	  }
      break;

    case LCD_READY:
      if( queueHasData(0) )
      {
        ch = queue_get(0);
        switch( ch )
        {
	      case 0xFF:
	        clr_LCD();
	        break;
	      case ESC:
          LCD_state = LCD_ESC_RECEIVED;
		    break;
	      default:
		    out_LCD( ch );
		}
	  }
	  break;

	case LCD_ESC_RECEIVED:

    if( queueHasData(0) )
	  {
        ch = queue_get(0);
		if( ch & 0x80 )
		{
			Set_cursor( ch );
		}
		else
		{
		  switch( ch )
		  {
		    case '@':
		    	home_LCD();
			  break;
		  }
    }
    LCD_state = LCD_READY;
    }
	  break;
  }
}

/****************************** End Of Module *******************************/
