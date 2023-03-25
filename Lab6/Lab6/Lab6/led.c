
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "glob_def.h"
#include "tmodel.h"

enum yellow_states
{
  YELLOW_OFF,
  YELLOW_ON,
};

void red_led_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    GPIO_PORTF_DATA_R ^= 0x02;              //toggle red led
    wait(1000);                             //wait 1000*5ms = 5sec,

    if(!(GPIO_PORTF_DATA_R & 0x02))         //if the red led was just turned on we signal to the green led
    {
        preset_sem(SEM_LED_ON, 1);
    }
}

void yellow_led_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    switch(my_state)
    {
    case YELLOW_OFF:
        GPIO_PORTF_DATA_R |= 0x04;                  //turn off yellow led
        set_state(YELLOW_ON);                       //change state
        wait_sem(SEM_SW1, 600);                     //wait for SW1 semaphore or 3sec (600*5ms)
        break;
    case YELLOW_ON:
        GPIO_PORTF_DATA_R &= 0xFB;                  //turn on yellow led
        preset_sem(SEM_LED_ON, 1);                  //signal to green led
        set_state(YELLOW_OFF);                      //change state
        wait(100);                                  //wait for 0.5sec (100*5ms)
        break;
    }
}

void green_led_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    if(wait_sem(SEM_LED_ON, 0))                     //wait for signal from either red or yellow led
    {
        GPIO_PORTF_DATA_R ^= 0x08;                  //toggle green led
    }
    else wait(1);
}
