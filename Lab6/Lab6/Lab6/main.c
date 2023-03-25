#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "systick.h"
#include "tmodel.h"
#include "systick.h"
#include "sw1.h"
#include "led.h"


int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : Init hardware and then loop forever
******************************************************************************/
{
  init_gpio();

  GPIO_PORTF_DATA_R |= 0x04;
  GPIO_PORTF_DATA_R |= 0x08;
  init_rtcs();


  start_task( TASK_SW1, sw1_task );
  start_task( TASK_LED_R, red_led_task);
  start_task( TASK_LED_Y, yellow_led_task);
  start_task( TASK_LED_G, green_led_task);

  schedule();
  return( 0 );
}
