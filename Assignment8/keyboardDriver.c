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
#include "tm4c123gh6pm.h"
#include "keyboardDriver.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

/*****************************    Defines    *******************************/
enum currently_writing
{
  SCALE,
  OFFSET
};

/*****************************   Constants   *******************************/
/*****************************   Variables   *******************************/
const INT8U keys[3][4] = {{'1','4','7','*'},
                          {'2','5','8','0'},
                          {'3','6','9','#'}};
static INT8U xPressed = 0;
static INT8U yPressed = 0;
volatile INT8U yPin = 0;

static enum currently_writing cur_wrt = SCALE;
static INT8U buffer_scale_factor[] = {'?','?','?','?'};
static INT8U buffer_offset[] = {'?','?','?','?'};
static INT8U counter_scale_factor = 0;
static INT8U counter_offset = 0;

extern INT16U scale_factor; extern SemaphoreHandle_t scale_factor_Mutex;
extern INT16U offset;       extern SemaphoreHandle_t offset_Mutex;
extern char LCD_Image[];    extern SemaphoreHandle_t LCD_Image_Mutex;

/*****************************   Functions   *******************************/
void keyboard_init()
{
  // Enable the GPIO port that is used for the keypad Y-axis.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
  // Enable the GPIO port that is used for the keypad X-axis.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

  // Do a dummy read to insert a few cycles after enabling the peripherals.
  int dummy;
  dummy = SYSCTL_RCGC2_R;

  // Set the directions. (Port A is also used elsewhere)
  GPIO_PORTE_DIR_R = 0b00000000;
  GPIO_PORTA_DIR_R |= 0b00011100;

  // Enable the GPIO pins for digital function (PE0, PE1, PE2, PE3, PA2, PA3, PA4).
  GPIO_PORTE_DEN_R = 0b00001111;
  GPIO_PORTA_DEN_R |= 0b00011100;

  // Enable NO internal pull-up (PE0, PE1, PE2, PE3).
  GPIO_PORTE_PUR_R = 0b00000000;

  // Set output to high (PA2, PA3, PA4).
  GPIO_PORTA_DATA_R |= 0b00011100;

  //Enable external interrupt for keypad Y-axis
  GPIO_PORTE_IS_R  &= ~(0b00001111);  //Trigger on edges
  GPIO_PORTE_IEV_R |= (0b00001111);  //Trigger on rising edges
  GPIO_PORTE_IM_R |= (0b00001111);    //Enable interrupt from pins PFE0-PE3
  GPIO_PORTE_ICR_R |= 0x10;     //Clear interrupt flag
  NVIC_EN0_R |= (1<<4);        //Enable interrupt IRQ4 (PORTE external interrupts)
}

void keyboard_handler(void)
{
  //Figure out which pin triggered the interrupt
  yPin = GPIO_PORTE_MIS_R & 0b00001111;

  GPIO_PORTE_ICR_R |= 0b00001111; /* clear the interrupt flags */
  NVIC_EN0_R &= ~(1<<4);  //Disable the interrupt to avoid contact bouncing triggering it again
}

void write_input(INT16U* stateVar,
                 SemaphoreHandle_t* stateVar_mutex,
                 INT8U* buffer_stateVar,
                 INT8U* counter,
                 INT8U LCD_offset)
{
  //Get mutexes
  if(xSemaphoreTake( *stateVar_mutex, portMAX_DELAY))
  {
    if(xSemaphoreTake( LCD_Image_Mutex, portMAX_DELAY))
    {
      buffer_stateVar[*counter] = keys[xPressed-1][yPressed-1];

      LCD_Image[LCD_offset+*counter] = buffer_stateVar[*counter];
      ++(*counter);

      if(buffer_stateVar[3] != '?')
      {
        *stateVar = ((buffer_stateVar[0]-48) * 1000) +
                    ((buffer_stateVar[1]-48) * 100) +
                    ((buffer_stateVar[2]-48) * 10) +
                    (buffer_stateVar[3]-48);

        buffer_stateVar[0] = '?';
        buffer_stateVar[1] = '?';
        buffer_stateVar[2] = '?';
        buffer_stateVar[3] = '?';

        LCD_Image[LCD_offset] = ' ';
        LCD_Image[LCD_offset+1] = ' ';
        LCD_Image[LCD_offset+2] = ' ';
        LCD_Image[LCD_offset+3] = ' ';

        *counter = 0;
      }
      xSemaphoreGive( LCD_Image_Mutex );
    }
    xSemaphoreGive( *stateVar_mutex );
  }
}

void Keyboard_task(void *pvParameters)  //LS function should be split into smaller functions
{
  while(1)
  {
    if(yPin) 
    {
      //Convert yPressed to a number switch
      switch(yPin) {
        case 0b00000001:
          yPressed = 4;
          break;
        case 0b00000010:
          yPressed = 3;
          break;
        case 0b00000100:
          yPressed = 2;
          break;
        case 0b00001000:
          yPressed = 1;
          break;
      }

      GPIO_PORTA_DATA_R = 0b00011000;
      if (!(GPIO_PORTE_DATA_R & 0b00001111))
      {
        xPressed = 3;
      }
      GPIO_PORTA_DATA_R = 0b00010100;
      if (!(GPIO_PORTE_DATA_R & 0b00001111))
      {
        xPressed = 2;
      }
      GPIO_PORTA_DATA_R = 0b00001100;
      if (!(GPIO_PORTE_DATA_R & 0b00001111))
      {
        xPressed = 1;
      }
      GPIO_PORTA_DATA_R = 0b00011100;  //Reset X-axis pins to high

      vTaskDelay(150 / portTICK_RATE_MS);  //Wait 150ms for any potential contact bouncing to dissapate
      NVIC_EN0_R |= (1<<4);        //Re-enable interrupt IRQ4 (PORTE external interrupts)
      yPin = 0;


      if(keys[xPressed-1][yPressed-1] == '*')  //Does user want to edit scalefactor?
      {
        cur_wrt = SCALE;
      }
      else if(keys[xPressed-1][yPressed-1] == '#')  //Does user want to edit offset?
      {
        cur_wrt = OFFSET;
      }
      else  //Number pressed
      {
        if(cur_wrt == SCALE)
        {
          write_input(&scale_factor, &scale_factor_Mutex, &buffer_scale_factor, &counter_scale_factor, 44U);
        }
        else if(cur_wrt == OFFSET)
        {
          write_input(&offset, &offset_Mutex, &buffer_offset, &counter_offset, 52U);
        }
      }
    }
    vTaskDelay(5 / portTICK_RATE_MS);
  }
}




