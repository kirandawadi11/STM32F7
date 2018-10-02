
#include "cmsis_os.h"                                           // CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 #include "main.h"
#include "GUI.h"                        // Segger.MDK-Pro::Graphics:CORE
#include "stm32746g_discovery_sdram.h"  // Keil.STM32F746G-Discovery::Board Support:Drivers:SDRAM
#include "stdio.h"
#include "stdlib.h"

void td1(void const *argument);
void td2(void const *argument);
void int3(void const *argument);
void Init_Thread1(void);
void Init_Thread2(void);
void Init_Interrupt_Thread(void);

int x1=70,y1 = 0,x2=300,y2=0,y3=0,x3=120;

 osThreadId thread1,thread2,int_thread;

osThreadDef (td1, osPriorityNormal, 1, 0);   
osThreadDef (td2, osPriorityNormal, 1, 0);   
osThreadDef (int3, osPriorityHigh, 1, 0);

void td1(void const *argument)
{
	while(1)
	{
		osSignalWait(0x01,osWaitForever);
		GUI_SetColor(GUI_BLUE);
		GUI_SetFont(&GUI_Font13H_ASCII);
		GUI_DispStringHCenterAt("I am from Thread1",x1,y1);
		y1 = y1+15;
		if(y1>230)
		{
			y1 = 0;
			x1 = x1+100;
		}
		osDelay(1000);
	}
}

void td2(void const *argument)
{
	while(1)
	{
		GUI_SetColor(GUI_BLUE);
		GUI_SetFont(&GUI_Font13H_ASCII);
		GUI_DispStringHCenterAt("I am from Thread2",x2,y2);
		y2 = y2+15;
		if(y2>230)
		{
			y2 = 0;
			x2 = x2+100;
		}
		osDelay(2000);
		osSignalSet(thread1,0x01);
	}
}
void int3(void const *argument)
{
	while(1)
	{
	osSignalWait(0x02,osWaitForever);
	GUI_SetColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font13H_ASCII);
		GUI_DispStringHCenterAt("INTERRUPTED!",x3,y3);
		y3 = y3+15;
		if(y3>230)
		{
			y3 = 0;
			x3 = x3+100;
		}
	}
	}
	

void Init_Thread1(void)
{
		thread1 = osThreadCreate (osThread(td1), NULL);
}

void Init_Thread2(void)
{
	thread2 = osThreadCreate (osThread(td2), NULL);
}

void Init_Interrupt_Thread(void)
{
	int_thread = osThreadCreate (osThread(int3), NULL);
}
