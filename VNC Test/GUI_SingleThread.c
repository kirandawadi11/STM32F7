
#include "cmsis_os.h"                   // CMSIS RTOS header file
#include "GUI.h"
#include "DIALOG.h"
#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

extern WM_HWIN Createbox(void);
extern int GUI_VNC_X_StartServer(int, int) ;
/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
 
void GUIThread (void const *argument);              // thread function
osThreadId tid_GUIThread;                           // thread id
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object


int Init_GUIThread (void) {

  tid_GUIThread = osThreadCreate (osThread(GUIThread), NULL);
  if (!tid_GUIThread) return(-1);
  
  return(0); 
}

void GUIThread (void const *argument) {

  GUI_Init();                     /* Initialize the Graphics Component */
	GUI_VNC_X_StartServer(0,0);
	Createbox();
  /* Add GUI setup code here */

  while (1) {
		
		if(osOK)
		{
			GUI_TOUCH_Exec();
		}
     
    /* All GUI related activities might only be called from here */

    GUI_Exec();                   /* Execute all GUI jobs ... Return 0 if nothing was done. */
    GUI_X_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
		osDelay(75);
  }
}

