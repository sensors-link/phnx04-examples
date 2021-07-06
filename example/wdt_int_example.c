/**
 * @file wdt_int_example.c
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

#define LED_PIN     GPIO_PIN8
#define LED_ON      GPIO_SetPin(LED_PIN)
#define LED_OFF     GPIO_ClrPin(LED_PIN)

void NMI_Handler(void)
{
    static int tog = 0;
    if (tog)
    {
        LED_ON;
        tog = 0;
        printf("tog = %d\n", tog);
    }
    else
    {
        LED_OFF;
        tog = 1;
        printf("tog = %d\n", tog);
    }
    WDT_ClrIntFlag();
}

int wdt_int_example(int delay)
{
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);
    WDT_Init(delay, LP_CLKSEL_LRC, WDT_OV_INT);

    WDT_StartCount();

    return 0;
}
SHELL_EXPORT_CMD(wdt_int_example, wdt_int_example, input delay<0-xxx>);
