
#include "cmsis_os.h"                   // CMSIS RTOS header file
#include "GUI.h"
#include "dialog.h"

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
/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
 
void GUIThread (void const *argument);              // thread function
osThreadId tid_GUIThread;                           // thread id
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object

static void wincallback(WM_MESSAGE* message)
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

int Init_GUIThread (void) {

  tid_GUIThread = osThreadCreate (osThread(GUIThread), NULL);
  if (!tid_GUIThread) return(-1);
  
  return(0);
}

void GUIThread (void const *argument) {

  GUI_Init();                     /* Initialize the Graphics Component */

		hWin = FRAMEWIN_Create("Main Window",wincallback,WM_CF_SHOW,0,0,480,272);
		hPrB = PROGBAR_CreateEx(110,180,160,25,hWin,WM_CF_SHOW,0,0);
	
		hGra = GRAPH_CreateEx(100,60,200,100,hWin,WM_CF_SHOW,0,0);
		GRAPH_SetColor(hGra,GUI_BLUE,0);
	
		hData = GRAPH_DATA_YT_Create(GUI_YELLOW,200,0,1);
	GRAPH_AttachData(hGra,hData);
	
	hSli = SLIDER_CreateEx(100,230,160,25,hWin,WM_CF_SHOW,0,0);
	hCheck = CHECKBOX_CreateEx(10,220,25,25,hWin,WM_CF_SHOW,0,0);
	
  /* Add GUI setup code here */

  while (1) 
		{
    
		
    /* All 	 GUI related activities might only be called from here */
		#ifdef RTE_Graphics_Touchscreen
		if (osOK) GUI_TOUCH_Exec();
		#endif
			if(CHECKBOX_IsChecked(hCheck))
			{
		PROGBAR_SetValue(hPrB,c);
		GRAPH_DATA_YT_AddValue(hData,c);
			}
		dt = SLIDER_GetValue(hSli);
    GUI_Exec();                   /* Execute all GUI jobs ... Return 0 if nothing was done. */
		osDelay(50+dt);
    GUI_X_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
  }
}

