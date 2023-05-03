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
#include <string.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "lcd.h"
#include "FreeRTOS.h"
#include "semphr.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/
const INT8U LCD_init_sequence[]= 
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
extern char LCD_Image[];  extern SemaphoreHandle_t LCD_Image_Mutex;

/*****************************   Functions   *******************************/
void LCD_task(void *pvParameters)
{
  char* LCD_string_temp = "";
  char* prev_LCD_string = "";
  
  const INT8U LCD_init_sequence[]= 
  {
    0x30,		// Reset
    0x30,		// Reset
    0x30,		// Reset
    0x20,		// Set 4bit interface
    0x28,		// 2 lines Display
    0x0C,		// Display ON, Cursor OFF, Blink OFF
    0x06,		// Cursor Increment
    0x01,		// Clear Display
    0x02,   // Home
    0xFF		// stop
  };
  INT8U LCD_init = 0;
  while( LCD_init_sequence[LCD_init] != 0xFF ){
      wr_ctrl_LCD( LCD_init_sequence[LCD_init++] );
      vTaskDelay(50 / portTICK_RATE_MS); // wait for 50ms
  }

  while(1){
    if(xSemaphoreTake(LCD_Image_Mutex, portMAX_DELAY))
    {
      LCD_string_temp = LCD_Image;
      xSemaphoreGive(LCD_Image_Mutex);
    }

    if((strcmp(LCD_string_temp, prev_LCD_string) != 0)){
      memcpy(prev_LCD_string, LCD_string_temp, sizeof(LCD_string_temp));
      
      Set_cursor(0);  //Return cursor to pos 0
      vTaskDelay(5 / portTICK_RATE_MS); // wait for 5ms
      wr_str_LCD(LCD_string_temp);
    }

    vTaskDelay(250 / portTICK_RATE_MS); // wait for 250ms
  }

}

//LS Funktioner der ikke virker skal fikses eller trimmes

void wr_ch_LCD( INT8U Ch )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    out_LCD(Ch);
    vTaskDelay(5 / portTICK_RATE_MS); // wait for 5ms
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
  vTaskDelay(1 / portTICK_RATE_MS); // wait for 1ms
  GPIO_PORTD_DATA_R &= 0xFB;        // Select Control mode, write
  vTaskDelay(1 / portTICK_RATE_MS); // wait for 1ms
  GPIO_PORTD_DATA_R |= 0x08;		// Set E High

  vTaskDelay(1 / portTICK_RATE_MS); // wait for 1ms

  GPIO_PORTD_DATA_R &= 0xF7;		// Set E Low

  vTaskDelay(1 / portTICK_RATE_MS); // wait for 1ms
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
    vTaskDelay(1 / portTICK_RATE_MS); // wait for 1ms
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


/****************************** End Of Module *******************************/
