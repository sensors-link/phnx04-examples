/**
 * @file wdt_rst_example.c
 * @author david.lin 
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"

#define LED_PIN          GPIO_PIN8
#define LED_ON           GPIO_SetPin(LED_PIN)
#define LED_OFF          GPIO_ClrPin(LED_PIN)

int wdt_rst_example(int delay)
{
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);

    LED_ON;

    WDT_Init(delay, LP_CLKSEL_LRC, WDT_OV_RST);

    WDT_StartCount();

    return 0;
}
SHELL_EXPORT_CMD(wdt_rst_example, wdt_rst_example, input delay<0-xxx>);
