//#include "main.h"
//#include "7SegDisplayDriver.h"
//#include "JoystickDriver.h"
//#include <stdbool.h>
//#include <stdio.h>
//
//#define ENTER_ASCII 13
//
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//
//int main(void)
//{
//  HAL_Init();
//  SystemClock_Config();
//  MX_GPIO_Init();
//  LPUART_ClearScreen();
//  LPUART_SendString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
//  LPUART_NewLine();
//  LPUART_SendString("Welcome message - Wiktor");
//  LPUART_NewLine();
//  FIFO fifo = {0};
//  FIFO_Init(&fifo);
//  while (1)
//  {
//	  char c = toggle_case_char(LPUART_ReadChar());
//	  if(c == ENTER_ASCII)
//	  {
//		  LPUART_NewLine();
//		  LPUART_SendFifo(&fifo);
//		  LPUART_NewLine();
//	  }
//	  else if(isdigit(c) > 0)
//	  {
//		  FIFO_Put(&fifo, c);
//	  }
//	  else
//	  {
//		  LPUART_SendChar(c);
//	  }
//  }
//}
//
//void SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
//  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
//  RCC_OscInitStruct.MSICalibrationValue = 0;
//  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
//
//static void MX_GPIO_Init(void)
//{
//	basic_LPUART_init();
//}
//
//void Error_Handler(void)
//{
//  /* USER CODE BEGIN Error_Handler_Debug */
//  /* User can add his own implementation to report the HAL error return state */
//
//  /* USER CODE END Error_Handler_Debug */
//}
//
//#ifdef USE_FULL_ASSERT
///**
// * @brief  Reports the name of the source file and the source line number
// *         where the assert_param error has occurred.
// * @param  file: pointer to the source file name
// * @param  line: assert_param error line source number
// * @retval None
// */
//void assert_failed(char *file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  while (1)
//    ;
//  /* User can add his own implementation to report the file name and line number,
//     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//}
//#endif /* USE_FULL_ASSERT */
//
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
