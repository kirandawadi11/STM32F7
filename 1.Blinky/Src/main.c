
#include "main.h"
#include "stm32f7xx_hal.h"


void SystemClock_Config(void);
void GPIO_Init(void);


int main(void)
{
  
  HAL_Init();

  
  SystemClock_Config();
 
  GPIO_Init();
 
  while (1)
  {
		
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_1);
		HAL_Delay(200);
  }
 
}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

   /*************Basics to Clock Enabling********************/
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

   
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
 
    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
 

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


void GPIO_Init(void)
{

  GPIO_InitTypeDef my_Pin;
	GPIO_InitTypeDef my_Pin1;

  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_GPIOI_CLK_ENABLE();

  /*****Configure GPIO pin : PB8 ******/
  my_Pin.Pin = GPIO_PIN_8;
  my_Pin.Mode = GPIO_MODE_OUTPUT_PP;
  my_Pin.Pull = GPIO_NOPULL;
  my_Pin.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &my_Pin);
	
/******Configure GPIO pin : PI1 i.e User LED************/
	 my_Pin1.Pin = GPIO_PIN_1;
  my_Pin1.Mode = GPIO_MODE_OUTPUT_PP;
  my_Pin1.Pull = GPIO_NOPULL;
  my_Pin1.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &my_Pin1);
	

}

