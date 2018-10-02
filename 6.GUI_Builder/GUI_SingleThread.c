
#include "cmsis_os.h"                   // CMSIS RTOS header file
#include "GUI.h"
#include "dialog.h"
#include "stm32746g_discovery.h"        // Keil.STM32F746G-Discovery::Board Support:Drivers:Basic I/O
#include "stdio.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

FRAMEWIN_Handle hWin;
PROGBAR_Handle hPrB;
GRAPH_Handle hGra;
GRAPH_DATA_Handle hData;
SLIDER_Handle hSli;
CHECKBOX_Handle hCheck;
extern uint16_t c,dt;
extern WM_HWIN CreateWindow(void);

/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
 
void GUIThread (void const *argument);              // thread function
void Led_func(void const *argument);
osThreadId tid_GUIThread;                           // thread id
osThreadId led1;
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object
osThreadDef (Led_func, osPriorityNormal, 1, 0);   // thread object
/*static void wincallback(WM_MESSAGE* message)
{
	GUI_RECT Rect;
	
	switch (message->MsgId)
  {
  	case WM_PAINT:
		WM_GetInsideRect(&Rect);
		GUI_SetBkColor(GUI_MAGENTA);
		GUI_SetColor(GUI_YELLOW);
		GUI_ClearRectEx(&Rect);
		GUI_DrawRectEx(&Rect);
		GUI_SetFont(&GUI_Font8x16);
		GUI_DispStringHCenterAt("ADC Channel 0",220,20);
		GUI_DrawLine(20,35,365,35);
		break;
  	default:
			WM_DefaultProc(message);
  		break;
  }
	
}

*/

int Init_GUIThread (void) {

  tid_GUIThread = osThreadCreate (osThread(GUIThread), NULL);
  if (!tid_GUIThread) return(-1);
  
  return(0);
}

void Led_func(void const *argument)
{
	int x = 20;
	 GUI_Init();	
	GUI_SetBkColor(GUI_MAGENTA);
	GUI_Clear();
	GUI_SetBkColor(GUI_MAGENTA);
	GUI_SetColor(GUI_BLUE);
	GUI_SetFont(&GUI_Font32B_ASCII);
	while(1){	
	HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_1);
		GUI_Clear();
	GUI_DispStringHCenterAt("HELLO!",220,x);			//yini GUI haru rakhda hang vaidinxa
		x = x+20;
	
	osDelay(500);
	}
	
}


int Init_LedThread (void) {	

  led1 = osThreadCreate (osThread(Led_func), NULL);
  if (!tid_GUIThread) return(-1);
  
  return(0);
}



void GUIThread (void const *argument) {

  GUI_Init();                     /* Initialize the Graphics Component */
	hWin = CreateWindow();
		/*hWin = FRAMEWIN_Create("Main Window",wincallback,WM_CF_SHOW,0,0,480,272);
		hPrB = PROGBAR_CreateEx(110,180,160,25,hWin,WM_CF_SHOW,0,0);
	
		hGra = GRAPH_CreateEx(100,60,200,100,hWin,WM_CF_SHOW,0,0);
		GRAPH_SetColor(hGra,GUI_BLUE,0);
	
		hData = GRAPH_DATA_YT_Create(GUI_YELLOW,200,0,1);
	GRAPH_AttachData(hGra,hData);
	
	hSli = SLIDER_CreateEx(100,230,160,25,hWin,WM_CF_SHOW,0,0);
	hCheck = CHECKBOX_CreateEx(10,220,25,25,hWin,WM_CF_SHOW,0,0);*/
	
  /* Add GUI setup code here */

  while (1) 
		{
    
    /* All 	 GUI related activities might only be called from here */
	/*	#ifdef RTE_Graphics_Touchscreen
		if (osOK) GUI_TOUCH_Exec();
		#endif
			if(CHECKBOX_IsChecked(hCheck))
			{
		PROGBAR_SetValue(hPrB,c);
		GRAPH_DATA_YT_AddValue(hData,c);
			}
		dt = SLIDER_GetValue(hSli);*/
    GUI_Exec();                   /* Execute all GUI jobs ... Return 0 if nothing was done. */
		osDelay(5);
			//osDelay(50+dt);
    GUI_X_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
  }
}

