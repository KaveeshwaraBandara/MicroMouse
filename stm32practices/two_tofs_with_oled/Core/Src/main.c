/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "fonts.h"
#include "ssd1306.h"
#include "VL53L0X.h"
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
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t stop_variable = 50;
uint16_t timeout_start_ms = 50;
uint16_t io_timeout = 50;
uint8_t did_timeout = 50;

uint8_t SENSOR1_ADDRESS =0x31;
uint8_t SENSOR2_ADDRESS = 0x32;

void displayMessage(const char *line1, const char *line2, uint16_t delay) {
    SSD1306_Clear();
    SSD1306_GotoXY(0, 10);
    SSD1306_Puts(line1, &Font_11x18, 1);
    if (line2 != NULL) {
        SSD1306_GotoXY(0, 30);
        SSD1306_Puts(line2, &Font_11x18, 1);
    }
    SSD1306_UpdateScreen();
    HAL_Delay(delay);
}

void scanI2CBus(void) {
    char buffer[16];
    SSD1306_Clear();
    SSD1306_GotoXY(0, 0);
    SSD1306_Puts("I2C Scan:", &Font_11x18, 1);

    for (uint8_t address = 1; address < 128; address++) {
        // Perform an I2C write operation to check if the device responds
        if (HAL_I2C_IsDeviceReady(&hi2c1, (address << 1), 1, 10) == HAL_OK) {
            snprintf(buffer, sizeof(buffer), "Found: 0x%02X", address);
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts(buffer, &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(1000);
            //SD1306_Clear();// Delay to display each address found
        }
    }
    HAL_Delay(2000);  // Delay at the end of the scan
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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  //scanI2CBus();
  //displayMessage("Initializing", "I2C...", 500);

//  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
//      displayMessage("I2C Init", "Failed", 2000);
//      Error_Handler();
//  } else {
//      displayMessage("I2C Init", "Success", 2000);
//  }

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);  // Enable Sensor 1
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);  // Disable Sensor 2
  HAL_Delay(50);

//  displayMessage("Initializing", "Sensor 1", 500);
  if (!init(true)) {
      //displayMessage("Sensor 1", "Init Failed", 2000);
      Error_Handler();
  }
  setAddress(SENSOR1_ADDRESS);
  //displayMessage("Sensor 1", "Initialized", 1000);
  //scanI2CBus();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);  // Disable Sensor 1
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);  // Enable Sensor 2
  HAL_Delay(50);

  //displayMessage("Initializing", "Sensor 2", 500);
  if (!init(true)) {
    //  displayMessage("Sensor 2", "Init Failed", 2000);
      Error_Handler();
  }
  setAddress(SENSOR2_ADDRESS);
  //displayMessage("Sensor 2", "Initialized", 1000);
  SSD1306_Init();
  scanI2CBus();
  uint16_t distance1, distance2;
  char buffer1[16], buffer2[16];
 // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
 // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // Enable Sensor 1
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0); // Disable Sensor 2

	  VL53L0X_SetAddress(SENSOR1_ADDRESS);
	  uint16_t distance = readRangeSingleMillimeters();
	  SSD1306_Clear();
	  SSD1306_GotoXY(0, 10);
	  SSD1306_Puts("Sensor 1:", &Font_11x18, 1);
	  SSD1306_GotoXY(0, 30);
	  itoa(distance, buffer1, 10);
	  SSD1306_Puts(buffer1, &Font_11x18, 1);
	  SSD1306_UpdateScreen();
	  HAL_Delay(1000);

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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
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
