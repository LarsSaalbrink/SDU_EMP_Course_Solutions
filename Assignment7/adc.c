// -----------------
// adc.c
// -----------------

//LS: Header mangler

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "FreeRTOS.h"
#include "semphr.h"

extern INT16U Al_Value;  SemaphoreHandle_t Al_Value_Mutex;

void Al_task(void *pvParameters)
{
  INT16U Al_Value_temp;

  //Wait for init to finish
  vTaskDelay(250 / portTICK_RATE_MS); // wait for 250ms

  while(1)
  {
    Al_Value_temp = get_adc();  //Read ADC

    //Updates mutex protected global variable
    if(xSemaphoreTake(Al_Value_Mutex, portMAX_DELAY)){
      Al_Value = Al_Value_temp;
      xSemaphoreGive(Al_Value_Mutex);
    }

    vTaskDelay(250 / portTICK_RATE_MS); // wait for 250ms
  }
}

INT16U get_adc()
{
  return( ADC0_SSFIFO3_R );
}

init_adc()
{
  SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC0;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;

  // Set ADC0 Sequencer priorities.
  // SS3(bit12-13): Priority = 0 ; Highest
  // SS2(bit8-9):   Priority = 1
  // SS1(bit4-5):   Priority = 2
  // SS0(bit0-1):   Priority = 3 ; Lowest
  ADC0_SSPRI_R = 0x00000123;

  //Disable all sequencers
  ADC0_ACTSS_R = 0;

  // Trigger for Sequencer 3 (bit 12-15) = 0xF = Always.
  ADC0_EMUX_R = 0x0000F000;

  //sample multiplexer input, sequencer 3 select, ADC 11 (0x0B) enable.
  ADC0_SSMUX3_R = 0x0B;

  //ADC sample sequence control 3 = END0
  ADC0_SSCTL3_R =  0x00000002;

  //enable sequencer 3
  ADC0_ACTSS_R = 0x00000008;

  // Start conversion at sequencer 3
  ADC0_PSSI_R = 0x08;
}