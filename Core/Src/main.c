/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "adc.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void MAX_Send(uint8_t addr, uint8_t data)
{
    uint8_t tx[2] = {addr, data};

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void MAX_Init(void)
{
    MAX_Send(0x0F, 0x00); // test off
    MAX_Send(0x09, 0x00); // matrix mode
    MAX_Send(0x0B, 0x07); // scan all rows
    MAX_Send(0x0A, 0x08); // brightness
    MAX_Send(0x0C, 0x01); // normal mode ON
}

void MAX_Draw(uint8_t *buf)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        MAX_Send(i + 1, buf[i]);
    }
}


uint8_t on[8]  = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t Pos_1[8] = {0b10000000, 0b10000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000, 0b00000000
};
uint8_t Pos_2[8] = {0b00000000, 0b10000000, 0b10000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000, 0b00000000
};
uint8_t Pos_3[8] = {0b00000000, 0b00000000, 0b10000000, 0b10000000,
		0b00000000, 0b00000000, 0b00000000, 0b00000000
};
uint8_t Pos_4[8] = {0b00000000, 0b00000000, 0b00000000, 0b10000000,
		0b10000000, 0b00000000, 0b00000000, 0b00000000};
uint8_t Pos_5[8] = {0b00000000, 0b00000000, 0b00000000, 0b00000000,
		0b10000000, 0b10000000, 0b00000000, 0b00000000
};
uint8_t Pos_6[8] = {0b00000000, 0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b10000000, 0b10000000, 0b00000000
};
uint8_t Pos_7[8] = {
		0b00000000, 0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b10000000, 0b10000000
};
uint8_t smile[8] = {
    0b00111100, 0b01000010, 0b10100101, 0b10000001,
    0b10100101, 0b10011001, 0b01000010, 0b00111100
};
uint8_t num1[8] = {
    0b00011000, 0b00111000, 0b00011000, 0b00011000,
    0b00011000, 0b00011000, 0b00111100, 0b00000000
};
uint8_t num2[8] = {
    0b00111100, 0b01000010, 0b00000010, 0b00001100,
    0b00110000, 0b01000000, 0b01111110, 0b00000000
};
uint8_t num3[8] = {
    0b00111100, 0b01000010, 0b00000010, 0b00011100,
    0b00000010, 0b01000010, 0b00111100, 0b00000000
};
uint8_t off[8] = {0};

const uint8_t small_num_L[10][5] = {
    {0xE0, 0xA0, 0xA0, 0xA0, 0xE0}, // 0
    {0x40, 0xC0, 0x40, 0x40, 0xE0}, // 1
    {0xE0, 0x20, 0xE0, 0x80, 0xE0}, // 2
    {0xE0, 0x20, 0xE0, 0x20, 0xE0}, // 3
    {0xA0, 0xA0, 0xE0, 0x20, 0x20}, // 4
    {0xE0, 0x80, 0xE0, 0x20, 0xE0}, // 5
    {0xE0, 0x80, 0xE0, 0xA0, 0xE0}, // 6
    {0xE0, 0x20, 0x20, 0x20, 0x20}, // 7
    {0xE0, 0xA0, 0xE0, 0xA0, 0xE0}, // 8
    {0xE0, 0xA0, 0xE0, 0x20, 0xE0}  // 9
};

const uint8_t small_num_R[10][5] = {
    {0x0E, 0x0A, 0x0A, 0x0A, 0x0E}, // 0
    {0x04, 0x0C, 0x04, 0x04, 0x0E}, // 1
    {0x0E, 0x02, 0x0E, 0x08, 0x0E}, // 2
    {0x0E, 0x02, 0x0E, 0x02, 0x0E}, // 3
    {0x0A, 0x0A, 0x0E, 0x02, 0x02}, // 4
    {0x0E, 0x08, 0x0E, 0x02, 0x0E}, // 5
    {0x0E, 0x08, 0x0E, 0x0A, 0x0E}, // 6
    {0x0E, 0x02, 0x02, 0x02, 0x02}, // 7
    {0x0E, 0x0A, 0x0E, 0x0A, 0x0E}, // 8
    {0x0E, 0x0A, 0x0E, 0x02, 0x0E}  // 9
};
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
uint8_t scoreP1 = 0;
uint8_t scoreP2 = 0;

uint8_t isPaused = 0;
uint8_t lastPause = 1;
uint8_t lastReset = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void PlayTon(uint16_t frequency, uint16_t duration_ms)
{
    if (frequency == 0) return;

    uint32_t delay_us = 1000000 / (frequency * 2);
    uint32_t cycles = ((uint32_t)frequency * duration_ms) / 1000;

    for (uint32_t i = 0; i < cycles; i++)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        for (volatile uint32_t d = 0; d < delay_us * 2; d++) { __NOP(); }

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
        for (volatile uint32_t d = 0; d < delay_us * 2; d++) { __NOP(); }
    }
}

void ShowScore(uint8_t score1, uint8_t score2) {
    uint8_t buf[8] = {0};
    if (score1 > 9) score1 = 9;
    if (score2 > 9) score2 = 9;

    for (int i = 0; i < 5; i++) {
        buf[i + 1] = small_num_L[score1][i] | small_num_R[score2][i];
    }
    MAX_Draw(buf);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t pot1 = 0;
	uint32_t pot2 = 0;

	// Stanje loptice (Kreće s centra)
	int8_t ballX = 3;
	int8_t ballY = 3;
	int8_t ballDx = 1;
	int8_t ballDy = 0;

	uint32_t ballTimer = 0;
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
  MX_ADC1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  HAL_Delay(100);

  MAX_Init();

  MAX_Draw(num3); HAL_Delay(500);
  MAX_Draw(num2); HAL_Delay(500);
  MAX_Draw(num1); HAL_Delay(500);
  MAX_Draw(off);  HAL_Delay(100);

  ballTimer = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  uint8_t pauseButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	  uint8_t resetButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);

	  //Pauza
	  if (lastPause == 1 && pauseButton == 0) {
	      isPaused = !isPaused;
	      PlayTon(2500, 40);
	      HAL_Delay(150);
	  }
	  lastPause = pauseButton;

	  //Restart
	  if (lastReset == 1 && resetButton == 0) {
	      isPaused = 0;
	      scoreP1 = 0; scoreP2 = 0;
	      ballX = 3; ballY = 3;
	      ballDx = 1; ballDy = 0;

	      PlayTon(3500, 100);

	      MAX_Draw(off);  HAL_Delay(100);
	      MAX_Draw(num3); HAL_Delay(400);
	      MAX_Draw(num2); HAL_Delay(400);
	      MAX_Draw(num1); HAL_Delay(400);

	      ballTimer = HAL_GetTick();
	      HAL_Delay(150);
	  }
	  lastReset = resetButton;


	  HAL_ADC_Start(&hadc1);
	  if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
	      pot1 = HAL_ADC_GetValue(&hadc1);
	  }
	  if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
	      pot2 = HAL_ADC_GetValue(&hadc1);
	  }
	  HAL_ADC_Stop(&hadc1);

	  uint8_t *p1_pos;
	  uint8_t *p2_pos;
	  uint8_t zaslon[8] = {0};

	  //pozicije palice 1. igrac
	  if      (pot1 <= 585)  p1_pos = Pos_1;
	  else if (pot1 <= 1170) p1_pos = Pos_2;
	  else if (pot1 <= 1755) p1_pos = Pos_3;
	  else if (pot1 <= 2340) p1_pos = Pos_4;
	  else if (pot1 <= 2925) p1_pos = Pos_5;
	  else if (pot1 <= 3510) p1_pos = Pos_6;
	  else                   p1_pos = Pos_7;

	  //pozicije palice 2. igraca
	  if      (pot2 <= 585)  p2_pos = Pos_1;
	  else if (pot2 <= 1170) p2_pos = Pos_2;
	  else if (pot2 <= 1755) p2_pos = Pos_3;
	  else if (pot2 <= 2340) p2_pos = Pos_4;
	  else if (pot2 <= 2925) p2_pos = Pos_5;
	  else if (pot2 <= 3510) p2_pos = Pos_6;
	  else                   p2_pos = Pos_7;


	  if (isPaused) {
	      for (int i = 0; i < 8; i++) {
	          zaslon[i] = p1_pos[i] | (p2_pos[i] >> 7);
	          if (ballY == i) zaslon[i] |= (0x80 >> ballX);
	      }
	      MAX_Draw(zaslon);
	      HAL_Delay(20);
	      continue;
	  }


	  if (HAL_GetTick() - ballTimer > 150) {
	      ballTimer = HAL_GetTick();

	      ballX += ballDx;
	      ballY += ballDy;


	      if (ballY <= 0) {
	          ballY = 0;
	          PlayTon(600, 15);
	          if (ballDy < 0) ballDy = -ballDy;
	      }

	      else if (ballY >= 7) {
	          ballY = 7;
	          PlayTon(600, 15);
	          if (ballDy > 0) ballDy = -ballDy;
	      }

	      //Igrac 1
	      if (ballX == 0) {
	          if (p1_pos[ballY] & 0x80) { //obrana
	              ballDx = 1;
	              PlayTon(1000, 25);
	              ballDy = (HAL_GetTick() % 5) - 2;
	          } else {
	              //gol
	              scoreP2++;
	              PlayTon(200, 300);

	              if (scoreP2 >= 10) { // POBJEDA IGRAČA 2
	                  PlayTon(2000, 100); HAL_Delay(50);
	                  PlayTon(2500, 100); HAL_Delay(50);
	                  PlayTon(3500, 300);
	                  MAX_Draw(smile); HAL_Delay(3000);
	                  scoreP1 = 0; scoreP2 = 0;
	              } else {
	                  ShowScore(scoreP1, scoreP2);
	                  HAL_Delay(1500);
	              }

	              ballX = 3; ballY = 3;
	              ballDx = 1;
	              ballDy = 0;

	              MAX_Draw(off);  HAL_Delay(100);
	              MAX_Draw(num3); HAL_Delay(500);
	              MAX_Draw(num2); HAL_Delay(500);
	              MAX_Draw(num1); HAL_Delay(500);
	              ballTimer = HAL_GetTick();
	          }
	      }

	      //Igrac 2
	      if (ballX == 7) {
	          if (p2_pos[ballY] & 0x80) { //obrana
	              ballDx = -1;
	              PlayTon(1000, 25);
	              ballDy = (HAL_GetTick() % 5) - 2;
	          } else {
	              //gol
	              scoreP1++;
	              PlayTon(200, 300);

	              if (scoreP1 >= 10) {
	                  PlayTon(2000, 100); HAL_Delay(50);
	                  PlayTon(2500, 100); HAL_Delay(50);
	                  PlayTon(3500, 300);
	                  MAX_Draw(smile); HAL_Delay(3000);
	                  scoreP1 = 0; scoreP2 = 0;
	              } else {
	                  ShowScore(scoreP1, scoreP2);
	                  HAL_Delay(1500);
	              }

	              ballX = 3; ballY = 3;
	              ballDx = -1;
	              ballDy = 0;

	              MAX_Draw(off);  HAL_Delay(100);
	              MAX_Draw(num3); HAL_Delay(500);
	              MAX_Draw(num2); HAL_Delay(500);
	              MAX_Draw(num1); HAL_Delay(500);
	              ballTimer = HAL_GetTick();
	          }
	      }
	  }


	  for (int i = 0; i < 8; i++) {
	      zaslon[i] = p1_pos[i] | (p2_pos[i] >> 7);

	      if (ballY == i) {
	          zaslon[i] |= (0x80 >> ballX);
	      }
	  }

	  MAX_Draw(zaslon);
	  HAL_Delay(20);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
