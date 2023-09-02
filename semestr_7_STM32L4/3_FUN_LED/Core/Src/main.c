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
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef void (*button_event_t)();

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t pin;
} pin_t;

typedef struct
{
  GPIO_PinState lastState;
  pin_t buttonPin;
  button_event_t onRelease;
  button_event_t onLongpress;
  uint32_t bounceStartTimeMillis;
  uint32_t longpressTimeMillis;
} button_t;

typedef enum
{
  MODE_MANUAL,
  MODE_ANIMATED
} mode_t;

typedef enum
{
  BACKWARD = -1,
  FORWARD = 1
} direction_t;

typedef void (*transition_handler_t)();

typedef enum
{
  TRANSITION_SIMPLE,
  TRANSITION_BOUNCE,
  TRANSITION_TOGGLE_SIMPLE,
  TRANSITION_TOGGLE_BOUNCE,
  TRANSITION_TWOCOLORS,
  TRANSITION_CROSSROADS,
  TRANSITION_NOISE,
  TRANSITION_RAINDROPS,
  TRANSITIONS_COUNT
} transition_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOUNCE_TIME_MILLIS 50
#define LONGPRESS_TIME_MILLIS 500
#define TRANSITION_INITIAL_LEVEL 8
#define TRANSITION_INTERVAL_BASE 2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define ARRLEN(x) (sizeof(x) / sizeof(x)[0]) // count number of elemnts in array - divide size of whole array, by size of one of elements inside it

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RNG_HandleTypeDef hrng;

/* USER CODE BEGIN PV */
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
static const int LEDS_COUNT = ARRLEN(LED);
static uint32_t interval = 128;
static int intervalLevel = TRANSITION_INITIAL_LEVEL;
static uint32_t transitionTimer = 0;
static transition_t transition = TRANSITION_SIMPLE;
static mode_t mode = MODE_MANUAL;
static direction_t direction = FORWARD;
static int led = -1;
static uint32_t randResult = 0;
static int rainAnimationStage = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*The force argument is needed to force an update - this is done with a button. Since it is a function, it will be used without "force" in the main loop,
and with "force" in the button event functions.
*/

// LED STEERING STUFF
void led_set(int led, bool turn_on)
{
  GPIO_PinState state = (turn_on) ? GPIO_PIN_SET : GPIO_PIN_RESET;
  if (led >= 0 && led < LEDS_COUNT)
  {
    HAL_GPIO_WritePin(LED[led].port, LED[led].pin, state);
  }
  else
  {
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
  }
}

void leds_clear()
{
  for (int i = 0; i < LEDS_COUNT; i++)
  {
    led_set(i, false);
  }
}

void led_toggle(int led)
{
  if (led >= 0 && led < LEDS_COUNT)
    HAL_GPIO_TogglePin(LED[led].port, LED[led].pin);
}

int randLED()
{
  HAL_RNG_GenerateRandomNumber(&hrng, &randResult);
  return randResult % LEDS_COUNT;
}

// ANIMATIONS
void simpleTransitionAnimation()
{
  led_set(led, false);
  led += direction;
  if (direction == BACKWARD && led < 0)
    led += LEDS_COUNT;
  else if (direction == FORWARD && led >= LEDS_COUNT)
    led -= LEDS_COUNT;
  led_set(led, true);
}

void bounceAnimation()
{
  led_set(led, false);

  led += direction;
  if (direction == BACKWARD && led < 0)
  {
    led = -led;
    direction = FORWARD;
  }
  else if (direction == FORWARD && led >= LEDS_COUNT)
  {
    led = led - LEDS_COUNT + 1;
    led = LEDS_COUNT - led - 1;
    direction = BACKWARD;
  }

  led_set(led, true);
}

void toggleSimpleAnimation()
{
  led_toggle(led);

  led += direction;
  if (direction == BACKWARD && led < 0)
    led += LEDS_COUNT;
  else if (direction == FORWARD && led >= LEDS_COUNT)
    led -= LEDS_COUNT;
}

void bounceToggleAnimation()
{
  led_toggle(led);

  led += direction;
  if (direction == BACKWARD && led < 0)
  {
    led = -led - 1;
    direction = FORWARD;
  }
  else if (direction == FORWARD && led >= LEDS_COUNT)
  {
    led = led - LEDS_COUNT + 1;
    led = LEDS_COUNT - led;
    direction = BACKWARD;
  }
}

void twocolorsAnimation()
{
  for (int i = 0; i < LEDS_COUNT / 2; ++i)
    led_set(i * 2 + led, false);

  led ^= 1;

  for (int i = 0; i < LEDS_COUNT / 2; ++i)
    led_set(i * 2 + led, true);
}

void crossroadsAnimation()
{
  led_set(led, false);
  led_set(LEDS_COUNT - led - 1, false);

  led += direction;
  if (direction == BACKWARD && led < 0)
    led += LEDS_COUNT;
  else if (direction == FORWARD && led >= LEDS_COUNT)
    led -= LEDS_COUNT;

  led_set(led, true);
  led_set(LEDS_COUNT - led - 1, true);
}

void noiseAnimation()
{
  led_set(led, false);

  led = randLED();

  led_set(led, true);
}

void raindropsAnimation()
{
  if (rainAnimationStage == 0)
  {
    led = randLED();
    led_set(led, true);
  }
  else if (rainAnimationStage == 1)
  {
    led_set(led - 1, true);
    led_set(led + 1, true);
  }
  else if (rainAnimationStage == 2)
  {
    led_set(led, false);
    led_set(led - 2, true);
    led_set(led + 2, true);
  }
  else if (rainAnimationStage == 3)
  {
    led_set(led - 1, false);
    led_set(led + 1, false);
  }
  else if (rainAnimationStage == 4)
  {
    led_set(led - 2, false);
    led_set(led + 2, false);
  }

  if (++rainAnimationStage > 4)
    rainAnimationStage = 0;
}
// HANDLER FOR ANIMATIONS CHOOSING
static transition_handler_t animations[TRANSITIONS_COUNT] = {simpleTransitionAnimation, bounceAnimation, toggleSimpleAnimation, bounceToggleAnimation, twocolorsAnimation, crossroadsAnimation, noiseAnimation, raindropsAnimation};

void animate(bool force)
{
  if (force || ((mode == MODE_ANIMATED) && (HAL_GetTick() - transitionTimer > interval)))
  {
    // execute selected transition
    animations[transition]();

    if (!force)
      transitionTimer += interval;
  }
}

// BUTTONS FUNCTIONS

// MODE BUTTON

void pressModeChangeTransiton()
{
  if (mode != MODE_MANUAL)
  {
    transitionTimer = HAL_GetTick();
    leds_clear();
    led = 0;
    direction = FORWARD;
  }

  if (++transition >= TRANSITIONS_COUNT)
    transition = TRANSITION_SIMPLE;
}

void longpressModeChange()
{
  if (mode == MODE_MANUAL)
  {
    transitionTimer = HAL_GetTick();
    mode = MODE_ANIMATED;
  }
  else
    mode = MODE_MANUAL;
  return;
}

// BACKWARD BUTTON

void longpressBackward()
{
  direction = BACKWARD;
}

void longpressForward()
{
  direction = FORWARD;
}

// FORWARD BUTTON

void pressForward()
{
  if (mode == MODE_MANUAL)
  {
    direction = FORWARD;
    animate(true);
  }
  else
  {
    if (--intervalLevel < 1)
      intervalLevel = 1;
    interval = (int)pow(TRANSITION_INTERVAL_BASE, intervalLevel);
  }
}

void pressBackward()
{
  if (mode == MODE_MANUAL)
  {
    direction = BACKWARD;
    animate(true);
  }
  else
  {
    ++intervalLevel;
    interval = (int)pow(TRANSITION_INTERVAL_BASE, intervalLevel);
  }
}

static button_t buttons[] = {
    {GPIO_PIN_RESET, {BUTTON_BACKWARD_LED_GPIO_Port, BUTTON_BACKWARD_LED_Pin}, pressBackward, longpressBackward, 0, 0},
    {GPIO_PIN_RESET, {BUTTON_FORWARD_GPIO_Port, BUTTON_FORWARD_Pin}, pressForward, longpressForward, 0, 0},
    {GPIO_PIN_RESET, {BUTTON_LED_MODE_GPIO_Port, BUTTON_LED_MODE_Pin}, pressModeChangeTransiton, longpressModeChange, 0, 0}

};

static const int BUTTONS_COUNT = ARRLEN(buttons);

void checkAllButtonsEvents()
{
  uint32_t millis = HAL_GetTick();

  for (int i = 0; i < BUTTONS_COUNT; ++i)
  {
    button_t *button = &buttons[i];

    if (millis - button->bounceStartTimeMillis > BOUNCE_TIME_MILLIS)
    {
      GPIO_TypeDef *port = button->buttonPin.port;
      int pin = button->buttonPin.pin;
      GPIO_PinState currentState = HAL_GPIO_ReadPin(port, pin);

      if (button->lastState == GPIO_PIN_RESET && currentState == GPIO_PIN_SET)
      {
        // on release event
        if (button->longpressTimeMillis > 0)
        {
          button->bounceStartTimeMillis = millis;
          button->onRelease();
        }
      }
      else if (button->lastState == GPIO_PIN_SET && currentState == GPIO_PIN_RESET)
      {
        // on press event -> on longpress event
        button->longpressTimeMillis = millis;
      }
      else if (currentState == GPIO_PIN_RESET)
      {
        if (button->longpressTimeMillis > 0)
        {
          if (millis - button->longpressTimeMillis > LONGPRESS_TIME_MILLIS)
          {
            button->longpressTimeMillis = 0;
            button->onLongpress();
          }
        }
      }

      button->lastState = currentState;
    }
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
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    checkAllButtonsEvents();
    animate(false);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief RNG Initialization Function
 * @param None
 * @retval None
 */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED6_Pin | LED7_Pin | LED8_Pin | LED9_Pin | LED10_Pin | LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUTTON_FORWARD_Pin */
  GPIO_InitStruct.Pin = BUTTON_FORWARD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_FORWARD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED6_Pin LED7_Pin LED8_Pin LED9_Pin
                           LED10_Pin LED1_Pin LED2_Pin LED3_Pin
                           LED4_Pin LED5_Pin */
  GPIO_InitStruct.Pin = LED6_Pin | LED7_Pin | LED8_Pin | LED9_Pin | LED10_Pin | LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_BACKWARD_LED_Pin BUTTON_LED_MODE_Pin */
  GPIO_InitStruct.Pin = BUTTON_BACKWARD_LED_Pin | BUTTON_LED_MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
