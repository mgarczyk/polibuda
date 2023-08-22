/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

static const uint16_t LED_PIN[] = {
	    LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin,
	    LED6_Pin, LED7_Pin, LED8_Pin, LED9_Pin, LED10_Pin,
	};


static GPIO_TypeDef* const LED_PORT[] = {
		LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port, LED5_GPIO_Port,
		LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port, LED9_GPIO_Port, LED10_GPIO_Port,
};

typedef struct{
	GPIO_TypeDef* port;
	uint16_t pin;
}pin_t;

static const pin_t LED[] = {
		{LED1_GPIO_Port, LED1_Pin},
		{LED2_GPIO_Port, LED2_Pin},
		{LED3_GPIO_Port, LED3_Pin},
		{LED4_GPIO_Port, LED4_Pin},
		{LED5_GPIO_Port, LED5_Pin},
		{LED6_GPIO_Port, LED6_Pin},
		{LED7_GPIO_Port, LED7_Pin},
		{LED8_GPIO_Port, LED8_Pin},
		{LED9_GPIO_Port, LED9_Pin},
		{LED10_GPIO_Port, LED10_Pin},
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void set_led_int(int led, bool turn_on){
	GPIO_PinState state;
	if (turn_on){
		state = GPIO_PIN_SET;
	}else{
		state = GPIO_PIN_RESET;
	}
	if (led >= 0 && led < 10){
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin << led, state);
	}
}


void set_led_switch(int led, bool turn_on)
{
	GPIO_PinState state = (turn_on) ? GPIO_PIN_SET : GPIO_PIN_RESET;

	switch (led) {
	case 0:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
		break;
	case 1:
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, state);
		break;
	case 2:
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, state);
		break;
	case 3:
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, state);
		break;
	case 4:
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, state);
		break;
	case 5:
		HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, state);
		break;
	case 6:
		HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, state);
		break;
	case 7:
		HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, state);
		break;
	case 8:
		HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, state);
		break;
	case 9:
		HAL_GPIO_WritePin(LED10_GPIO_Port, LED10_Pin, state);
		break;
	default:
		break;
	}
}

void set_led_list(int led, bool turn_on){
	GPIO_PinState state = (turn_on) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	if (led >=0 && led<10){
		HAL_GPIO_WritePin(LED_PORT[led], LED_PIN[led], state);
	}else{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
	}
}

void set_led_struct(int led, bool turn_on){
	GPIO_PinState state = (turn_on) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	if (led >=0 && led<10){
		HAL_GPIO_WritePin(LED[led].port, LED[led].pin, state);
	}else{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
	}
}

bool is_button_pressed(void){
	if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_RESET){
		return true;
	}else{
		return false;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		if (is_button_pressed()){
			set_led_int(0, true);
		}else{
			set_led_int(0, false);
		}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin
                          |LED10_Pin|LED1_Pin|LED2_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED6_Pin LED7_Pin LED8_Pin LED9_Pin
                           LED10_Pin LED1_Pin LED2_Pin LED3_Pin
                           LED4_Pin LED5_Pin */
  GPIO_InitStruct.Pin = LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin
                          |LED10_Pin|LED1_Pin|LED2_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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