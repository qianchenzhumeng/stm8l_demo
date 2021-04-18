#include "stm8l15x.h"
#include "stdio.h"
#include "uart.h"
#include "sht3x_sensor.h"
#include "sgp30_sensor.h"
#include "string.h"
#include "delay.h"

void BoardInit( void )
{
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
    SENSORS_INIT(sgp30_sensor);
    SENSORS_ACTIVATE(sgp30_sensor);
    uart_init(115200);
    delay_init(16);
}

void main(void)
{
    t_sht3x_value sht3x_value;
    t_sgp30_value sgp30_value;
    int sensorRet;
    BoardInit();
    memset(&sht3x_value, 0, sizeof(t_sht3x_value));
    memset(&sgp30_value, 0, sizeof(sgp30_value));
    while (1)
    {
        memset(&sgp30_value, 0, sizeof(sgp30_value));
        sensorRet = sgp30_sensor.value(SGP30_SENSOR_CO2_TVOC, &sgp30_value);
        printf("co2: %u, tvoc: %u, ret: %d\n", sgp30_value.co2, sgp30_value.tvoc, sensorRet);
        delay_ms(1000);
    }
}