/**
 * @file tim_timer_example.c
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

#define LED_PIN      GPIO_PIN12
#define LED_ON       GPIO_SetPin(LED_PIN)
#define LED_OFF      GPIO_ClrPin(LED_PIN)

void TIMER1_IrqHandler(void) 
{
    static int tog = 0;
    if (tog) 
    {
        LED_ON;
        tog = 0;
    } 
    else 
    {
        LED_OFF;
        tog = 1;
    }
    TIM_ClrIntFlag(TIM1);
    printf("tog %x\n", tog);
}

int tim_timer_example(int delay)
{
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);
    TIM_TimerInit(TIM1, delay);
    PLIC_EnableIRQ(TIMER1_IRQn);
    PLIC_SetPriority(TIMER1_IRQn, 1);
    TIM_ClrIntFlag(TIM1);
    TIM_EnableIRQ(TIM1);

    TIM_EnableControl(TIM1, ENABLE);
}
SHELL_EXPORT_CMD(timer_example, tim_timer_example, input delay<0 - xxx>);
