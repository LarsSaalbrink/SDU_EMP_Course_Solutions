
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "glob_def.h"
#include "tmodel.h"

enum SW1_states
{
  SW1_WAIT,
  SW1_PRESSED,
};

INT8U button_pushed()
{
    return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4
}

void sw1_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    switch(my_state)
    {
    case SW1_WAIT:
        if(button_pushed())                 //if SW1 pushed
        {
            set_state(SW1_PRESSED);         //change state
        }
        break;
    case SW1_PRESSED:
        if(!button_pushed())                //if button released, change state and signal
        {
            set_state(SW1_WAIT);
            preset_sem(SEM_SW1, 1);         //signal semaphore
        }
        break;
    }
}
