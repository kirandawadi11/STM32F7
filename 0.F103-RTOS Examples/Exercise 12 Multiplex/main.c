/*----------------------------------------------------------------------------
	
	Designers Guide to the Cortex-M Family
	CMSIS RTOS Multiplex Example

*----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "cmsis_os.h"

#include "Board_LED.h"

void  multiplex_Thread (void const *argument);

osThreadDef(multiplex_Thread, osPriorityNormal, 6, 0);

osThreadId T_mux1;																			
osThreadId T_mux2;
osThreadId T_mux3;
osThreadId T_mux4;
osThreadId T_mux5;
osThreadId T_mux6;

osSemaphoreId semMultiplex;						//declare the Semaphore
osSemaphoreDef(semMultiplex);
osSemaphoreId semSignal;
osSemaphoreDef(semSignal);

/*******************************************************************
Create a thread and use the Semaphore to control the number of threads 
running simultaneously
********************************************************************/

void multiplex_Thread (void const *argument) 
{
	for (;;) 
	{
    osSemaphoreWait(semMultiplex,osWaitForever);
		LED_On((uint32_t)argument);
		osDelay(100);
		LED_Off((uint32_t)argument);
		osDelay(100);
		osSemaphoreRelease(semMultiplex);
	}
}

/*----------------------------------------------------------------------------
 Create the Semaphore and launch the threads
 *---------------------------------------------------------------------------*/
int main (void) 
{
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	LED_Initialize();
	semMultiplex = osSemaphoreCreate(osSemaphore(semMultiplex), 2);	
	T_mux1 = osThreadCreate(osThread(multiplex_Thread),(void *)1UL);
	T_mux2 = osThreadCreate(osThread(multiplex_Thread),(void *)2UL);                  
	T_mux3 = osThreadCreate(osThread(multiplex_Thread),(void *)3UL);
	T_mux4 = osThreadCreate(osThread(multiplex_Thread),(void *)4UL); 
	T_mux5 = osThreadCreate(osThread(multiplex_Thread),(void *)0x5UL);
	T_mux6 = osThreadCreate(osThread(multiplex_Thread),(void *)0x6UL); 	
	
	osKernelStart ();                         // start thread execution 
}
