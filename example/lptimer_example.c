/**
 * @file lptimer_example.c
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

#define LED_PIN    GPIO_PIN8
#define LED_ON     GPIO_SetPin(LED_PIN)
#define LED_OFF    GPIO_ClrPin(LED_PIN)

void LPT_IrqHandler(void) 
{
    static int tog = 0;
    if (tog) 
    {
        LED_ON;
        tog = 0;
    } else 
    {
        LED_OFF;
        tog = 1;
    }
    LPT_ClrIntFlag();
    printf("tog %x\n", tog);
};

int lptimer_count(void)
{
    return LPT_GetCount();
}
SHELL_EXPORT_CMD(lptimer_count, lptimer_count, get lptimer count);

int lptimer_example(int mode, int delay)
{
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);

    if(mode)
    {
        LPT_Init(LP_CLKSEL_LRC, delay, LPT_PIT_CNT);
    }
    else
    {
    	LPT_Init(LP_CLKSEL_LRC, delay, LPT_SIG_TIME_CNT);
    }
    PLIC_EnableIRQ(LPT_IRQn);
    PLIC_SetPriority(LPT_IRQn, 1);
    LPT_ClrIntFlag();
    LPT_EnableIRQ();

    LPT_EnableControl(ENABLE);

    return delay;
}
SHELL_EXPORT_CMD(lptimer_example, lptimer_example, mode<0-1> delay<0-xxx>);
