/*
 * sensor_app.c
 *
 *  Created on: Apr 23, 2025
 *      Author: sorawit srisun
 */

#include "sensor_app.h"
#include "usart.h"
#include "main.h"
#include <string.h>

static SensorStatus_t sensor_status = SENSOR_IDLE;
static SensorData_t sensor_data;
static uint8_t rx_buffer[16];
static uint8_t modbus_frame[8];

static void Build_Modbus_Request(uint8_t slave_addr, uint16_t start_reg, uint16_t quantity);
static uint16_t Modbus_CRC16(uint8_t *buf, uint8_t len);
static void Decode_TempHumi(uint8_t *rx_buf);

void SensorApp_Init(void) {
    sensor_status = SENSOR_IDLE;
}

void SensorApp_StartRead(void) {
    if (sensor_status == SENSOR_IDLE) {
        Build_Modbus_Request(0x01, 0x0000, 0x0004);  // Ex: temp/humi sensor
        HAL_UART_Transmit(&huart2, modbus_frame, 8, 1000);
        HAL_UART_Receive_IT(&huart2, rx_buffer, 16);  // non-blocking
        sensor_status = SENSOR_READING;
    }
}

bool SensorApp_IsReady(void) {
    return (sensor_status == SENSOR_READY);
}

void SensorApp_GetData(SensorData_t *data_out) {
    if (data_out && sensor_status == SENSOR_READY) {
        memcpy(data_out, &sensor_data, sizeof(SensorData_t));
        sensor_status = SENSOR_IDLE;
    }
}

void SensorApp_UART_RxCallback(void) {
    if (sensor_status == SENSOR_READING) {
        Decode_TempHumi(rx_buffer);
        sensor_status = SENSOR_READY;
    }
}

static void Decode_TempHumi(uint8_t *rx_buf) {
    int16_t temp_raw = (rx_buf[3] << 8) | rx_buf[4];
    uint16_t humi_raw = (rx_buf[5] << 8) | rx_buf[6];
    int16_t dew_raw = (rx_buf[7] << 8) | rx_buf[8];
    uint16_t press_raw = (rx_buf[9] << 8) | rx_buf[10];

    sensor_data.temperature = temp_raw / 100.0f;
    sensor_data.humidity = humi_raw / 100.0f;
    sensor_data.dew_point = dew_raw / 100.0f;
    sensor_data.pressure = press_raw / 10.0f;
}

static void Build_Modbus_Request(uint8_t slave_addr, uint16_t start_reg, uint16_t quantity) {
    modbus_frame[0] = slave_addr;
    modbus_frame[1] = 0x03;
    modbus_frame[2] = (start_reg >> 8) & 0xFF;
    modbus_frame[3] = start_reg & 0xFF;
    modbus_frame[4] = (quantity >> 8) & 0xFF;
    modbus_frame[5] = quantity & 0xFF;

    uint16_t crc = Modbus_CRC16(modbus_frame, 6);
    modbus_frame[6] = crc & 0xFF;
    modbus_frame[7] = (crc >> 8) & 0xFF;
}

static uint16_t Modbus_CRC16(uint8_t *buf, uint8_t len) {
    uint16_t crc = 0xFFFF;
    for (uint8_t pos = 0; pos < len; pos++) {
        crc ^= buf[pos];
        for (int i = 0; i < 8; i++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xA001;
            else crc >>= 1;
        }
    }
    return crc;
}

