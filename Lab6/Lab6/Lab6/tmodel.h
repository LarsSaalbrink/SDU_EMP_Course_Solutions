/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the elements of the task model.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 101004  MoH   Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

#include "rtcs.h"

// Tasks.
// ------
#define TASK_SW1         USER_TASK
#define TASK_LED_R       USER_TASK+1
#define TASK_LED_Y       USER_TASK+2
#define TASK_LED_G       USER_TASK+3

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21

// Semaphores.
// -----------
#define SEM_SW1          USER_SEM
#define SEM_LED_ON       USER_SEM+1

// Shared State Memory.
// --------------------
#define SSM_RTC_SEC            31
#define SSM_RTC_MIN            32
#define SSM_RTC_HOUR           33

// QUEUEs.
// -------
#define Q_UART_TX 	USER_QUEUE
#define Q_UART_RX   USER_QUEUE+1
#define Q_LCD       USER_QUEUE+2

#endif /* _TMODEL_H_ */
