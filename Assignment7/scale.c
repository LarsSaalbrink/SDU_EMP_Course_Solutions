// -----------------
// adc.c
// -----------------
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern INT16U Al_Value;     extern SemaphoreHandle_t Al_Value_Mutex;
extern INT16U scale_factor; extern SemaphoreHandle_t scale_factor_Mutex;
extern INT16U offset;       extern SemaphoreHandle_t offset_Mutex;

extern char LCD_Image[];    extern SemaphoreHandle_t LCD_Image_Mutex;

void Scale_task(void *pvParameters)
{
  char temp_LCD_Image[80] = "";
  INT16U temp_Al_Value = 1111;
  INT16U prev_Al_Value = 0;

  while(1)
  {
    //Read Al_Value
    if(xSemaphoreTake(Al_Value_Mutex, portMAX_DELAY))
    {
      temp_Al_Value = Al_Value;
      xSemaphoreGive(Al_Value_Mutex);

      if(xSemaphoreTake(scale_factor_Mutex, portMAX_DELAY))
      {
        if(xSemaphoreTake(offset_Mutex, portMAX_DELAY))
        {
          scale_factor = scale_factor;


          temp_Al_Value = (temp_Al_Value / scale_factor) + offset;

          if(temp_Al_Value != prev_Al_Value)
          {
            prev_Al_Value = temp_Al_Value;
            temp_LCD_Image[5] = (temp_Al_Value / 1000) + 48;
            temp_LCD_Image[6] = ((temp_Al_Value % 1000) / 100) + 48;
            temp_LCD_Image[7] = ((temp_Al_Value % 100) / 10) + 48;
            temp_LCD_Image[8] = ((temp_Al_Value % 10)) + 48;
          }
          xSemaphoreGive(offset_Mutex);
        }
        xSemaphoreGive(scale_factor_Mutex);
      }
    }

    //Handle scale_factor

    //Handle offset

    //Write to LCD_Image
    if(xSemaphoreTake(LCD_Image_Mutex, portMAX_DELAY))
    {
      int i;
      for(i = 5; i < 9; i++)
      {
        LCD_Image[i] = temp_LCD_Image[i];
      }
      xSemaphoreGive(LCD_Image_Mutex);
    }

    //temp_LCD_Image[42] = '!';
    //LCD_Image[42] = temp_LCD_Image[42];

    vTaskDelay(1000 / portTICK_RATE_MS); // wait for 1000ms
  }
}
