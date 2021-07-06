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

#define TEST_PIN          GPIO_PIN8

#define PIN_ON            GPIO_SetPin(TEST_PIN)
#define PIN_OFF           GPIO_ClrPin(TEST_PIN)

int gpio_out_example(void)
{
    int i;
    GPIO_PinConfigure(TEST_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);

    while (1)
    {
        PIN_OFF;
        for (i = 10000; i > 0; i--)
            ;
        PIN_ON;
        for (i = 10000; i > 0; i--)
            ;
    }
}
