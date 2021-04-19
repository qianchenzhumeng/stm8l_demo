#include <stdio.h>
#include "stm8l15x.h"
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
    int i;  /* 如果定义成 uint8_t 类型，后面使用 printf 输出的值会很奇怪 */

    BoardInit();
    memset(&sht3x_value, 0, sizeof(t_sht3x_value));
    memset(&sgp30_value, 0, sizeof(sgp30_value));

    printf("\n");
    printf("waiting 15s for sgp30 init");
    /* 延时 15s，等待 sgp30 初始化完成 */
    for(i = 0; i < 15; i++)
    {
        delay_ms(1000);
        printf(".");
    }
    printf("\n");
    for(i = 0; i < 10; i++)
    {
        memset(&sgp30_value, 0, sizeof(sgp30_value));
        sensorRet = sgp30_sensor.value(SGP30_SENSOR_CO2_TVOC, &sgp30_value);
        printf("[%d] co2: %u, tvoc: %u, ret: %d\n", i, sgp30_value.co2, sgp30_value.tvoc, sensorRet);
        delay_ms(1000);
    }

printf("let sgp30 go to sleep...\n");
    SENSORS_DEACTIVATE(sgp30_sensor);
    printf("sgp30 was slept, press \"RESET\" key to wake it up.\n");

    while(1);
}