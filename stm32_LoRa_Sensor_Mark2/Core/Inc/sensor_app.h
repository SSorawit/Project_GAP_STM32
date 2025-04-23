#ifndef __SENSOR_APP_H
#define __SENSOR_APP_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SENSOR_IDLE = 0,
    SENSOR_READING,
    SENSOR_READY
} SensorStatus_t;

typedef struct {
    float temperature;
    float humidity;
    float dew_point;
    float pressure;
    uint32_t lux;
    float soil_temp;
    float soil_humi;
} SensorData_t;

void SensorApp_Init(void);
void SensorApp_StartRead(void);
bool SensorApp_IsReady(void);
void SensorApp_GetData(SensorData_t *data_out);
void SensorApp_UART_RxCallback(void);  // call from UART ISR

#endif // __SENSOR_APP_H
