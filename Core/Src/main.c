/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define KEY_1 0x1e // Keyboard 1 and !
#define KEY_2 0x1f // Keyboard 2 and @
#define KEY_3 0x20 // Keyboard 3 and #
#define KEY_4 0x21 // Keyboard 4 and $

#define ROWS 2
#define COLS 2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

	// 2x2 clusterrel kiolvasas teszt
	typedef struct colrow {
		GPIO_TypeDef *GPIO_PORT;
		uint16_t GPIO_PIN;
	}colrow;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	colrow COL[2] = {
			{COL6_GPIO_Port, COL6_Pin},
			{COL5_GPIO_Port, COL5_Pin}
	};

	colrow ROW[2] = {
			{ROW0_GPIO_Port, ROW0_Pin},
			{ROW1_GPIO_Port, ROW1_Pin}
	};

	uint8_t keyMap[2][2] = {
			{KEY_1, KEY_2},
			{KEY_3, KEY_4}
	};

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_USB_DEVICE_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */


  extern USBD_HandleTypeDef hUsbDeviceFS;
  uint8_t keyState[ROWS][COLS] = {0};  // Keeps track of the current state of each key
  uint8_t HID_buffer[8] = {0};         // USB HID report buffer
  uint8_t previousHIDBuffer[8] = {0};  // To detect changes
  uint32_t keyTimers[ROWS][COLS] = {0}; // Key debounce and repeat timers
  const uint32_t debounceDelay = 5;    // Debounce delay in ms
  const uint32_t repeatDelay = 50;     // Repeat delay for held keys in ms

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  // ------------------ test 1 -----------------------

//	  HID_buffer[0] = 2; //left shift down
//	  HID_buffer[3] = 7; // d down
//	  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//	  HAL_Delay(20);
//
//	  HID_buffer[0] = 0; //left shift up
//	  HID_buffer[3] = 0; // d up
//	  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//	  HAL_Delay(2000);

	  // ------------------ test 2 -----------------------

	  //COL6 es ROW0 a sarki billentyu
//	  HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_SET);
//	  HAL_Delay(10);
//	  if( HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET ) {
//
//	  	  HID_buffer[0] = 2; //left shift down
//	  	  HID_buffer[3] = 7; // d down
//	  	  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//	  	  HAL_Delay(20);
//
//	  	  HID_buffer[0] = 0; //left shift up
//	  	  HID_buffer[3] = 0; // d up
//	  	  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//	  	  HAL_Delay(150);
//	  	  HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, GPIO_PIN_RESET);
//	  	  HAL_Delay(20);
//	  }

	  // ------------------ version 1 -----------------------

//	  for (uint8_t i = 0; i < 2; i++) {
//		  for (uint8_t c = 0; c < 2; c++) {
//			  HAL_GPIO_WritePin(COL[c].GPIO_PORT, COL[c].GPIO_PIN, (c == i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//		  }
//
//		  HAL_Delay(1);
//
//		  for(uint8_t j = 0; j < 2; j++) {
//			  if( HAL_GPIO_ReadPin(ROW[j].GPIO_PORT, ROW[j].GPIO_PIN) == GPIO_PIN_SET ) {
//				  HID_buffer[3] = keyMap[i][j];
//				  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//				  HAL_Delay(20);
//
//				  HID_buffer[3] = 0;
//				  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//			  }
//			  HAL_Delay(5);
//		  }
//	  }

	  // ------------------ version 2 -----------------------

//	  for (uint8_t i = 0; i < 2; i++) {
//	      // Activate only the current column
//	      for (uint8_t c = 0; c < 2; c++) {
//	          HAL_GPIO_WritePin(COL[c].GPIO_PORT, COL[c].GPIO_PIN, (c == i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	      }
//
//	      HAL_Delay(1); // Stabilize signals
//
//	      // Check rows
//	      for (uint8_t j = 0; j < 2; j++) {
//	          if (HAL_GPIO_ReadPin(ROW[j].GPIO_PORT, ROW[j].GPIO_PIN) == GPIO_PIN_SET) {
//	              // Key press detected
//	              HID_buffer[3] = 7; // Example keycode
//	              USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//
//	              HAL_Delay(20);
//
//	              HID_buffer[3] = 0; // Release key
//	              USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//	          }
//	      }
//
//	      HAL_Delay(5); // Small delay before switching columns
//	  }

	  //--------------------- version 3 -----------------------
//	  uint8_t keyIndex = 2; // Start filling keycodes from HID_buffer[2]
//	      memset(HID_buffer + 2, 0, 6); // Clear keycode slots
//
//	      for (uint8_t i = 0; i < COLS; i++) {
//	          // Activate only the current column
//	          for (uint8_t c = 0; c < COLS; c++) {
//	              HAL_GPIO_WritePin(COL[c].GPIO_PORT, COL[c].GPIO_PIN, (c == i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	          }
//
//	          HAL_Delay(1); // Allow signal to stabilize
//
//	          // Check rows for pressed keys
//	          for (uint8_t j = 0; j < ROWS; j++) {
//	              uint8_t isPressed = HAL_GPIO_ReadPin(ROW[j].GPIO_PORT, ROW[j].GPIO_PIN) == GPIO_PIN_SET;
//
//	              // Detect key press (pressed now but not before)
//	              if (isPressed && keyState[j][i] == 0) {
//	                  if (keyIndex < 8) {
//	                      HID_buffer[keyIndex++] = keyMap[j][i]; // Add keycode to HID buffer
//	                  }
//	                  keyState[j][i] = 1; // Update key state to pressed
//	              }
//	              // Detect key release (was pressed before but not now)
//	              else if (!isPressed && keyState[j][i] == 1) {
//	                  keyState[j][i] = 0; // Update key state to released
//	              }
//	          }
//
//	          HAL_Delay(5); // Small delay before switching columns 1122443312214343341212121212121432124311324
//	      }
//
//	      // Send HID report only if there’s a change
//	      if (memcmp(HID_buffer, previousHIDBuffer, 8) != 0) {
//	          USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
//	          memcpy(previousHIDBuffer, HID_buffer, 8); // Update previous buffer
//	      }

	  //--------------------- version 4 -----------------------

	  uint8_t keyIndex = 2; // Start filling keycodes from HID_buffer[2]
	  memset(HID_buffer + 2, 0, 6); // Clear keycode slots

	  for (uint8_t i = 0; i < COLS; i++) {
		  // Activate only the current column
		  for (uint8_t c = 0; c < COLS; c++) {
			  HAL_GPIO_WritePin(COL[c].GPIO_PORT, COL[c].GPIO_PIN, (c == i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		  }

		  HAL_Delay(5); // Allow signal to stabilize

		  // Check rows for pressed keys
		  for (uint8_t j = 0; j < ROWS; j++) {
			  uint8_t isPressed = HAL_GPIO_ReadPin(ROW[j].GPIO_PORT, ROW[j].GPIO_PIN) == GPIO_PIN_SET;

			  if (isPressed) {
				  uint32_t currentTime = HAL_GetTick();

				  // Handle key press or hold
				  if (keyState[j][i] == 0 || (currentTime - keyTimers[j][i] >= repeatDelay)) {
					  if (keyIndex < 8) {
						  HID_buffer[keyIndex++] = keyMap[j][i]; // Add keycode to HID buffer
					  }
					  keyTimers[j][i] = currentTime; // Reset timer for repeat
					  keyState[j][i] = 1; // Mark key as pressed
				  }
			  } else {
				  keyState[j][i] = 0; // Mark key as released
			  }
		  }

		  HAL_Delay(5); // Small delay before switching columns
	  }

	  // Send HID report if there's a change or for held keys
	  if (memcmp(HID_buffer, previousHIDBuffer, 8) != 0 || keyIndex > 2) {
		  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
		  memcpy(previousHIDBuffer, HID_buffer, 8); // Update previous buffer
	  }


	  //--------------------- version 5 -----------------------


	  uint8_t keyIndex = 2; // Start filling keycodes from HID_buffer[2]
	  memset(HID_buffer + 2, 0, 6); // Clear keycode slots

	  for (uint8_t i = 0; i < COLS; i++) {
		  // Activate only the current column
		  for (uint8_t c = 0; c < COLS; c++) {
			  HAL_GPIO_WritePin(COL[c].GPIO_PORT, COL[c].GPIO_PIN, (c == i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		  }

		  HAL_Delay(1); // Allow signal to stabilize

		  // Check rows for pressed keys
		  for (uint8_t j = 0; j < ROWS; j++) {
			  uint8_t isPressed = HAL_GPIO_ReadPin(ROW[j].GPIO_PORT, ROW[j].GPIO_PIN) == GPIO_PIN_SET;
			  uint32_t currentTime = HAL_GetTick();

			  // Handle key press
			  if (isPressed) {
				  if (keyState[j][i] == 0 && (currentTime - keyTimers[j][i] >= debounceDelay)) {
					  // First valid press or repeat
					  if (keyIndex < 8) {
						  HID_buffer[keyIndex++] = keyMap[j][i]; // Add keycode to HID buffer
					  }
					  keyTimers[j][i] = currentTime; // Reset timer
					  keyState[j][i] = 1; // Mark as pressed
				  }
			  } else {
				  // Handle key release
				  if (keyState[j][i] == 1 && (currentTime - keyTimers[j][i] >= debounceDelay)) {
					  keyState[j][i] = 0; // Mark as released
					  keyTimers[j][i] = currentTime; // Reset timer
				  }
			  }
		  }

		  HAL_Delay(5); // Small delay before switching columns
	  }

	  // Send HID report if there's a change or for held keys
	  if (memcmp(HID_buffer, previousHIDBuffer, 8) != 0 || keyIndex > 2) {
		  USBD_HID_SendReport(&hUsbDeviceFS, HID_buffer, 8);
		  memcpy(previousHIDBuffer, HID_buffer, 8); // Update previous buffer
	  }






  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
