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

#define LED_PIN    GPIO_PIN12
#define LED_ON     GPIO_SetPin(LED_PIN)
#define LED_OFF    GPIO_ClrPin(LED_PIN)

#define MTIMELO    (0xE000000C)
#define MTIMEHI    (0xE0000010)
#define TICK       (125)  //ns (1/8000000)

void LPT_IrqHandler(void) 
{
    static int tog = 0;
    static int prev_count = 0;
    int count = 0;
    int diff  = 0;

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
    LPT_ClrIntFlag();
    printf("tog %x, lpt_count %d\n", tog, LPT_GetCount());

    //以下是利用系统定时器验证定时准确性，不是必要的功能代码
    printf("mtime high %d, low %d\n", REG32(MTIMEHI), REG32(MTIMELO));
	count = REG32(MTIMELO);
	diff  = count - prev_count;
	printf("mtime different from prev count %d, time %d\n", diff, diff*TICK/1000);
	prev_count = count;
};

int lptimer_count(void)
{
    return LPT_GetCount();
}
SHELL_EXPORT_CMD(lptimer_count, lptimer_count, get lptimer count);

int lptimer_example(int mode, int delay)
{
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);

    if(mode == 1)
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

    return LPT_GetCount();
}
SHELL_EXPORT_CMD(lptimer_example, lptimer_example, mode<0-1> delay<4-262000ms>);
