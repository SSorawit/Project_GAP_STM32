/*
 * sensor_app.h
 *
 *  Created on: Apr 25, 2025
 *      Author: sorawit srisun
 */

#ifndef INC_SENSOR_APP_H_
#define INC_SENSOR_APP_H_

#include <stdint.h>

typedef struct {
    float temperature;
    float humidity;
    float dewpoint;
    float pressure;
} temphumi_t;

typedef struct {
    float temperature;
    float humidity;
} soil_t;

void Build_Modbus_Request(uint8_t slave_addr, uint16_t start_reg, uint16_t quantity, uint8_t *frame_out);
uint16_t Modbus_CRC16(uint8_t *buf, uint8_t len);

temphumi_t Decode_TempHumi(uint8_t *rx_buf);
soil_t Decode_Soil(uint8_t *rx_buf);
uint32_t Decode_Light(uint8_t *rx_buf);


temphumi_t TempHumi(void);
soil_t SoilTempHumi(void);
uint32_t Light(void);

#endif /* INC_SENSOR_APP_H_ */

