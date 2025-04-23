/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "app_lorawan.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t rx_buffer[16];
uint8_t modbus_frame[8];
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
void Build_Modbus_Request(uint8_t slave_addr, uint16_t start_reg, uint16_t quantity, uint8_t *frame_out);
void RS485_Transmit(uint8_t *data, uint16_t size);
void TempHumi();
void Lihgt();
void SoilTempHumi();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_LoRaWAN_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_LoRaWAN_Process();

    /* USER CODE BEGIN 3 */
//    TempHumi();
//    Lihgt();
//    SoilTempHumi();
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint16_t Modbus_CRC16(uint8_t *buf, uint8_t len) {
    uint16_t crc = 0xFFFF;

    for (uint8_t pos = 0; pos < len; pos++) {
        crc ^= (uint16_t)buf[pos];
        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

void Build_Modbus_Request(uint8_t slave_addr, uint16_t start_reg, uint16_t quantity, uint8_t *frame_out) {
    frame_out[0] = slave_addr;                // AA
    frame_out[1] = 0x03;                      // Function Code

    frame_out[2] = (start_reg >> 8) & 0xFF;   // RRRR (high byte)
    frame_out[3] = start_reg & 0xFF;          // RRRR (low byte)

    frame_out[4] = (quantity >> 8) & 0xFF;    // NNNN (high byte)
    frame_out[5] = quantity & 0xFF;           // NNNN (low byte)

    uint16_t crc = Modbus_CRC16(frame_out, 6);  // คำนวณ CRC จาก 6 byte แรก

    frame_out[6] = crc & 0xFF;               // CRC Low byte
    frame_out[7] = (crc >> 8) & 0xFF;        // CRC High byte
}

void Decode_TempHumi(uint8_t *rx_buf) {
    int16_t temp_raw = (rx_buf[3] << 8) | rx_buf[4];
    uint16_t humi_raw = (rx_buf[5] << 8) | rx_buf[6];
    int16_t dew_raw = (rx_buf[7] << 8) | rx_buf[8];
    uint16_t press_raw = (rx_buf[9] << 8) | rx_buf[10];

    float temp_c = temp_raw / 100.0f;  // °C
    float humidity = humi_raw / 100.0f;  // %
    float dewpoint_c = dew_raw / 100.0f;  // °C
    float pressure_hpa = press_raw / 10.0f;  // hPa

    printf("Temperature: %.2f C\r\n", temp_c);
    printf("Humidity: %.2f %%\r\n", humidity);
    printf("Dew Point: %.2f C\r\n", dewpoint_c);
    printf("Pressure: %.1f hPa\r\n", pressure_hpa);
}

void Decode_Light(uint8_t *rx_buf) {
    // อ่านค่า High และ Low 16 bits ของ Illuminance
    uint16_t lux_high = (rx_buf[3] << 8) | rx_buf[4];  // High 16 bits
    uint16_t lux_low  = (rx_buf[5] << 8) | rx_buf[6];  // Low 16 bits

    // รวม High และ Low 16 bits เป็น 32-bit Illuminance
    uint32_t lux = ((uint32_t)lux_high << 16) | lux_low;

    // แสดงผล
    printf("Illuminance: %lu lux\r\n", lux);
}

void Decode_Soil(uint8_t *rx_buf) {
    // ดึง Humidity (unsigned)
    uint16_t humi_raw = (rx_buf[3] << 8) | rx_buf[4];
    // ดึง Temperature (signed)
    int16_t temp_raw = (rx_buf[5] << 8) | rx_buf[6];

    // แปลงหน่วย
    float humidity = humi_raw / 10.0f;   // %RH
    float temperature = temp_raw / 10.0f; // °C

    // แสดงผล
    printf("Humidity: %.1f %%RH\r\n", humidity);
    printf("Temperature: %.1f C\r\n", temperature);
}

void TempHumi() {
	Build_Modbus_Request(0x01, 0x0000, 0x0004, modbus_frame);
	HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
	HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

	printf("TEMPHUMI: ");
	for (int i = 0; i < 16; i++) {
	    printf("%d ", rx_buffer[i]);
	}
    printf("\r\n");

    Decode_TempHumi(rx_buffer);

	HAL_Delay(1000);
}

void Lihgt() {
	Build_Modbus_Request(0x02, 0x0000, 0x0002, modbus_frame);
	HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
	HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

	printf("LiGHT: ");
	for (int i = 0; i < 16; i++) {
	    printf("%d ", rx_buffer[i]);
	}
    printf("\r\n");

    Decode_Light(rx_buffer);

	HAL_Delay(1000);
}

void SoilTempHumi() {
	Build_Modbus_Request(0x03, 0x0000, 0x0002, modbus_frame);
	HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
	HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

	printf("SOIL: ");
	for (int i = 0; i < 16; i++) {
	    printf("%d ", rx_buffer[i]);
	}
    printf("\r\n");

    Decode_Soil(rx_buffer);

	HAL_Delay(1000);
}
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
