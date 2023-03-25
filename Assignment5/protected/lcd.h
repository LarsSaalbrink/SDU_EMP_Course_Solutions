/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Driver for LCD display HW
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 230313  LS    Module created.
*
*****************************************************************************/

#ifndef _LCD_H
  #define _LCD_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
// Special ASCII characters
// ------------------------
#define LF		0x0A
#define FF		0x0C
#define CR		0x0D

#define ESC		0x1B

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void move_LCD( INT8U, INT8U );
/*****************************************************************************
*   Input    : X and Y coordinate for where to place cursor
*   Output   : -
*   Function : Change the position of the cursor on the screen
******************************************************************************/
void wr_ch_LCD( INT8U );
/*****************************************************************************
*   OBSERVE  : LCD_PROC NEEDS 20 mS TO PRINT OUT ONE CHARACTER
*   Input    : Put a single character into the output queue
*   Output   : -
*   Function : Insert character into output FIFO buffer to be printed when
*              time is available
*****************************************************************************/
void wr_str_LCD( INT8U* );
/*****************************************************************************
*   Input    : Put multiple characters into the output queue
*   Output   : -
*   Function : Insert multiple characters into output FIFO buffer to be printed when
*              time is available
*****************************************************************************/
void wr_ctrl_LCD_low( INT8U );
/*****************************************************************************
*   Input    : Lower 4 bits to write to LCD driver
*   Output   : -
*   Function : Write lower 4 bits to LCD driver. Out connection to the HW
*              uses a 4 bit interface, so bytes have to be written in two
*              separate steps
*****************************************************************************/
void wr_ctrl_LCD_high( INT8U );
/*****************************************************************************
*   Input    : Upper 4 bits to write to LCD driver
*   Output   : -
*   Function : Write upper 4 bits to LCD driver. Out connection to the HW
*              uses a 4 bit interface, so bytes have to be written in two
*              separate steps
*****************************************************************************/
void lcd_task( INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for initializing, writing characters to, clearing and moving
*              cursor on LCD display
******************************************************************************/

/****************************** End Of Module *******************************/
#endif

