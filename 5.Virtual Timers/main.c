/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
 
#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#define osObjectsPublic                     // define objects in main module
//#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
extern int Init_Thread (void);
int counter1 = 0,counter2 = 0;

void _Error_Handler(char *file, int line);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void callback(void const *param);
void ledThread1 (void const *argument);
void ledThread2 (void const *argument);

osThreadDef(ledThread1, osPriorityNormal, 1, 0);
osThreadDef(ledThread2, osPriorityNormal, 1, 0);

osThreadId T_ledThread1;
osThreadId T_ledThread2;

osTimerDef(timer0_handle, callback);
osTimerDef(timer1_handle, callback);
osTimerDef(timer2_handle, callback);
osTimerDef(timer3_handle, callback);

/*----------------------------------------------------------------------------
  Timer callback function. Toggle the LED associated with the timer
 *---------------------------------------------------------------------------*/
void callback(void const *param)
{
	switch( (uint32_t) param)
	{
		case 0:
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_6);
		break;

		case 1:
				HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_7);
		break;

		case 2:
				HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_8);	
		break;

		case 3:
				HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		break;
	}
}
/*----------------------------------------------------------------------------
  Flash LED 1 when signaled by thread 2
 *---------------------------------------------------------------------------*/
void ledThread1 (void const *argument) 
{
	for (;;) 
	{
		osSignalWait(0x02,osWaitForever);
		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_1,GPIO_PIN_SET);                       
		osSignalWait(0x02,osWaitForever);	
		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_1,GPIO_PIN_RESET);  
	}
}
/*----------------------------------------------------------------------------
  Flash LED 2 and signal thread 1
 *---------------------------------------------------------------------------*/
void ledThread2 (void const *argument) 
{
	for (;;) 
	{
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);		
		osSignalSet	(T_ledThread1,0x02);
		osDelay(500);
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET);
		osSignalSet	(T_ledThread1,0x02);
		osDelay(500);
	}
}


/*
 * main: initialize and start the system
 */
int main (void) {
	
	osTimerId timer0 = osTimerCreate(osTimer(timer0_handle), osTimerPeriodic, (void *)0);	
	osTimerId timer1 = osTimerCreate(osTimer(timer1_handle), osTimerPeriodic, (void *)1);	
	osTimerId timer2 = osTimerCreate(osTimer(timer2_handle), osTimerPeriodic, (void *)2);	
	osTimerId timer3 = osTimerCreate(osTimer(timer3_handle), osTimerPeriodic, (void *)3);	
	
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// initialize peripherals here
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();


	//Init_Thread();
	osTimerStart(timer0, 1500);	
	osTimerStart(timer1, 1000);	
	osTimerStart(timer2, 2000);	
	osTimerStart(timer3, 500);		
	
	T_ledThread1 = osThreadCreate(osThread(ledThread1), NULL);
	T_ledThread2 = osThreadCreate(osThread(ledThread2), NULL);	
	
  osKernelStart ();                         // start thread execution 
}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_9 
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PI1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : PF7 PF6 PF10 PF9 
                           PF8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_9 
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

}

void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
