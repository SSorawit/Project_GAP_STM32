/*
 * sensor_app.c
 *
 *  Created on: Apr 25, 2025
 *      Author: sorawit srisun
 */


#include "sensor_app.h"
#include <stdio.h>
#include "main.h"
#include "usart.h"

uint8_t rx_buffer[16];
uint8_t modbus_frame[8];

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
    frame_out[0] = slave_addr;
    frame_out[1] = 0x03;
    frame_out[2] = (start_reg >> 8) & 0xFF;
    frame_out[3] = start_reg & 0xFF;
    frame_out[4] = (quantity >> 8) & 0xFF;
    frame_out[5] = quantity & 0xFF;
    uint16_t crc = Modbus_CRC16(frame_out, 6);
    frame_out[6] = crc & 0xFF;
    frame_out[7] = (crc >> 8) & 0xFF;
}

temphumi_t Decode_TempHumi(uint8_t *rx_buf) {
    temphumi_t data;

    int16_t temp_raw = (rx_buf[3] << 8) | rx_buf[4];
    uint16_t humi_raw = (rx_buf[5] << 8) | rx_buf[6];
    int16_t dew_raw = (rx_buf[7] << 8) | rx_buf[8];
    uint16_t press_raw = (rx_buf[9] << 8) | rx_buf[10];

    data.temperature = temp_raw / 100.0f;
    data.humidity = humi_raw / 100.0f;
    data.dewpoint = dew_raw / 100.0f;
    data.pressure = press_raw / 10.0f;

    printf("Temperature: %.2f C\r\n", data.temperature);
    printf("Humidity: %.2f %%\r\n", data.humidity);
    printf("Dew Point: %.2f C\r\n", data.dewpoint);
    printf("Pressure: %.1f hPa\r\n", data.pressure);

    return data;
}

uint32_t Decode_Light(uint8_t *rx_buf) {
    uint16_t lux_high = (rx_buf[3] << 8) | rx_buf[4];
    uint16_t lux_low  = (rx_buf[5] << 8) | rx_buf[6];
    uint32_t lux = ((uint32_t)lux_high << 16) | lux_low;

    printf("Illuminance: %lu lux\r\n", lux);

    return lux;
}

soil_t Decode_Soil(uint8_t *rx_buf) {
    soil_t data;

    uint16_t humi_raw = (rx_buf[3] << 8) | rx_buf[4];
    int16_t temp_raw = (rx_buf[5] << 8) | rx_buf[6];

    data.humidity = humi_raw / 10.0f;
    data.temperature = temp_raw / 10.0f;

    printf("Humidity: %.1f %%RH\r\n", data.humidity);
    printf("Temperature: %.1f C\r\n", data.temperature);

    return data;
}

temphumi_t TempHumi(void) {
    Build_Modbus_Request(0x01, 0x0000, 0x0004, modbus_frame);
    HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
    HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

    printf("TEMPHUMI: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", rx_buffer[i]);
    }
    printf("\r\n");

    temphumi_t result = Decode_TempHumi(rx_buffer);
    HAL_Delay(1000);
    return result;
}

uint32_t Light(void) {
    Build_Modbus_Request(0x02, 0x0000, 0x0002, modbus_frame);
    HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
    HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

    printf("LiGHT: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", rx_buffer[i]);
    }
    printf("\r\n");

    uint32_t lux = Decode_Light(rx_buffer);
    HAL_Delay(1000);
    return lux;
}

soil_t SoilTempHumi(void) {
    Build_Modbus_Request(0x03, 0x0000, 0x0002, modbus_frame);
    HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
    HAL_UART_Receive(&huart2, rx_buffer, 16, 1000);

    printf("SOIL: ");
    for (int i = 0; i < 16; i++) {
        printf("%d ", rx_buffer[i]);
    }
    printf("\r\n");

    soil_t result = Decode_Soil(rx_buffer);
    HAL_Delay(1000);
    return result;
}


