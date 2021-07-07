/**
 * @file gpio_int_example.c
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

#define TEST_PIN   GPIO_PIN12

#define PIN_ON     GPIO_SetPin(TEST_PIN)
#define PIN_OFF    GPIO_ClrPin(TEST_PIN)

void IOM_IrqHandler(void)
{
    if (GPIO_GetIntFlag() == TEST_PIN)
    {
        printf("iom int\r\n");
    }
    GPIO_ClrIntFlag(TEST_PIN);
};

int gpio_int_example(void)
{
    GPIO_PinConfigure(TEST_PIN, DISABLE, DISABLE, ENABLE, DISABLE, DISABLE); // gpio pd in

    GPIO_PinIntConfig(TEST_PIN, PIN_INT_TYPE_EDGE, PIN_INT_POL_LOW);

    PLIC_EnableIRQ(IOM_IRQn);
    PLIC_SetPriority(IOM_IRQn, 1);
    GPIO_GlobleIRQControl(DISABLE, DISABLE, ENABLE);
    GPIO_ClrIntFlag(TEST_PIN);

    GPIO_PinIRQControl(TEST_PIN, ENABLE);

    printf("poll test pin gp08 generate int\r\n");

    return TEST_PIN;
}
SHELL_EXPORT_CMD(gpio_int, gpio_int_example, gpio irq example);

