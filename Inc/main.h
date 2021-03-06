/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern float NRF_Data[10];
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct Flag
{
  int fivems;
  int fiftyms;
  int hundms;
  int halfs;
  int ones;
  int test1;
  int test2;
  int test3;
}Flag;   
extern Flag flag;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_UP_Pin GPIO_PIN_2
#define KEY_UP_GPIO_Port GPIOE
#define KEY_UP_EXTI_IRQn EXTI2_IRQn
#define KEY_DOWN_Pin GPIO_PIN_3
#define KEY_DOWN_GPIO_Port GPIOE
#define KEY_DOWN_EXTI_IRQn EXTI3_IRQn
#define KEY_LEFT_Pin GPIO_PIN_4
#define KEY_LEFT_GPIO_Port GPIOE
#define KEY_LEFT_EXTI_IRQn EXTI4_IRQn
#define KEY_RIGHT_Pin GPIO_PIN_5
#define KEY_RIGHT_GPIO_Port GPIOE
#define KEY_RIGHT_EXTI_IRQn EXTI9_5_IRQn
#define S1_Pin GPIO_PIN_2
#define S1_GPIO_Port GPIOG
#define S2_Pin GPIO_PIN_3
#define S2_GPIO_Port GPIOG
#define RING_Pin GPIO_PIN_6
#define RING_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_9
#define LED3_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
void inc(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
