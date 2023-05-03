

/**
 * main.c
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick_frt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"
#include "lcd.h"
#include "scale.h"
#include "semphr.h"
#include "keyboardDriver.h"
#include "digiswitchDriver.h"

//LS: Trim includes til alle filer
#define USERTASK_STACK_SIZE 70 //configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3

//Global variables (Diagram specifies that these should be state variables, not queues)
INT16U Al_Value = 0;           SemaphoreHandle_t Al_Value_Mutex;

INT16U scale_factor = 1;       SemaphoreHandle_t scale_factor_Mutex;
INT16U offset = 0;             SemaphoreHandle_t offset_Mutex;

char LCD_Image[] = "ADC:                                    Scl:    Off:                            ";
SemaphoreHandle_t LCD_Image_Mutex;

extern volatile enum digiswitch_ev digiswitch_event;

void enable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // enable interrupts.
  __asm("   cpsie i");
}

void disable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // disable interrupts.
  __asm("   cpsid i");
}

static void setupHardware(void)
/*****************************************************************************
*   Input    :  -
*   Output   :  -
*   Function :
*****************************************************************************/
{
  // TODO: Put hardware configuration and initialization in here

  // Warning: If you do not initialize the hardware clock, the timings will be inaccurate
  disable_global_int();
  //init_systick();
  //init_gpio();
  //init_adc();
  //keyboard_init();
  digiswitch_init();
  enable_global_int();
}

int main(void)
{
    digiswitch_event = DIGISWITCH_NONE;

    setupHardware();

    while(1)
    {
        digiswitch_event = DIGISWITCH_NONE;
    }

    //Allocate memory for mutexes
    Al_Value_Mutex = xSemaphoreCreateMutex();
    scale_factor_Mutex = xSemaphoreCreateMutex();
    offset_Mutex = xSemaphoreCreateMutex();
    LCD_Image_Mutex = xSemaphoreCreateMutex();

    //Verify that mutexes were created
    if(Al_Value_Mutex == NULL || 
       scale_factor_Mutex == NULL || 
       offset_Mutex == NULL || 
       LCD_Image_Mutex == NULL)
    {
        while(1);  //Mutex creation failed, loop forever (for debugging)
    }

    xTaskCreate( LCD_task, "LCD Task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    xTaskCreate( Scale_task, "Scale Task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    xTaskCreate( Al_task, "Al Task", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
    xTaskCreate( Keyboard_task, "Keyboard Task", USERTASK_STACK_SIZE, NULL, HIGH_PRIO, NULL );  //High priority as it needs to read button GPIO

    //LS Heartbeat task would be nice
    
    vTaskStartScheduler();
	return 0;
}
