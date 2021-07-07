/**
 * @file gpio_out_example.c
 * @author david.lin 
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#include "lib_include.h"
#include "platform.h"
#include "shell.h"

#define TEST_PIN          GPIO_PIN12

#define PIN_ON            GPIO_SetPin(TEST_PIN)
#define PIN_OFF           GPIO_ClrPin(TEST_PIN)

int gpio_out_example(void)
{
    GPIO_PinConfigure(TEST_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);

    while (1)
    {
        PIN_OFF;
        printf("IOM->DATA %x\n", IOM->DATA);
        DelayNus(1000000);

        PIN_ON;
        printf("IOM->DATA %x\n", IOM->DATA);
        DelayNus(1000000);
    }
}
SHELL_EXPORT_CMD(gpio_out, gpio_out_example, gpio out example);
