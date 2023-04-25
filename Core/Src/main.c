/* USER CODE BEGIN Header */
/**
The is an open source project developed by:
Nayyer Abbas Zaidi
Germany
 */

#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include"data.h"
extern USART_HandleTypeDef husart1;
extern USART_HandleTypeDef husart2;

/* USER CODE BEGIN PV */
int16_t master_rxdata[10];
int16_t slave_rxdata[10];
uint8_t FE_error = 0;
uint8_t ORE_error = 0;
uint8_t NE_error = 0;
static void MX_ICACHE_Init(void);

int main(void) {
	HAL_Init();
	SystemClock_Config();
	SystemPower_Config();
	MX_GPIO_Init();
	MX_USART1_Init();
	MX_USART2_Init();
	MX_ICACHE_Init();
	//clear the recieve buffer
	memset(master_rxdata, 0, sizeof(master_rxdata));
	memset(slave_rxdata, 0, sizeof(slave_rxdata));

	if (HAL_USART_TransmitReceive_IT(&husart2, slave_txdata, slave_rxdata,
			sizeof(slave_rxdata)) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_USART_TransmitReceive_IT(&husart1, master_txdata, master_rxdata,
			sizeof(master_rxdata)) != HAL_OK) {
		Error_Handler();
	}

	/*framing error*/
	if (__HAL_USART_GET_FLAG(&husart1, USART_FLAG_FE) == TRUE
			|| __HAL_USART_GET_FLAG(&husart2, USART_FLAG_FE) == TRUE)

			{
		FE_error++;
		Error_Handler();
	}

	/*Overrun error*/

	if (__HAL_USART_GET_FLAG(&husart1, USART_FLAG_ORE) == TRUE
			|| __HAL_USART_GET_FLAG(&husart2, USART_FLAG_ORE) == TRUE)

			{
		ORE_error++;
		Error_Handler();

	}
	/*Noise error*/

	if (__HAL_USART_GET_FLAG(&husart1, USART_FLAG_NE) == TRUE
			|| __HAL_USART_GET_FLAG(&husart2, USART_FLAG_NE) == TRUE)

			{
		NE_error++;
		Error_Handler();

	}

	while (1) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);

		HAL_Delay(1000);
	}

}

static void MX_ICACHE_Init(void) {

	if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_ICACHE_Enable() != HAL_OK) {
		Error_Handler();
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM17) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
