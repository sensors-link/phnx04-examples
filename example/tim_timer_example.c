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

#define MTIMELO      (0xE000000C)
#define MTIMEHI      (0xE0000010)
#define TICK         (125)  //ns (1/8000000)

static int gDel = 0;

void TIMER1_IrqHandler(void) 
{
    static int tog = 0;
    static int prev_count = 0;
    int count = 0;
    int diff  = 0;

    TIM_ClrIntFlag(TIM1);
    TIM_DeInit(TIM1);
    TIM_TimerInit(TIM1, gDel);
    TIM_EnableControl(TIM1, ENABLE);

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
    printf("timer1 tog %x\n", tog);

    //以下是利用系统定时器验证定时准确性，不是必要的功能代码
    printf("mtime high %d, low %d\n", REG32(MTIMEHI), REG32(MTIMELO));
	count = REG32(MTIMELO);
	diff  = count - prev_count;
	printf("mtime different from prev count %d, time %d\n", diff, diff*TICK/1000);
	prev_count = count;
}

void TIMER2_IrqHandler(void)
{
    static int tog = 0;
    static int prev_count = 0;
    int count = 0;
    int diff  = 0;

    TIM_ClrIntFlag(TIM2);
    TIM_DeInit(TIM2);
    TIM_TimerInit(TIM2, gDel);
    TIM_EnableControl(TIM2, ENABLE);

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
    printf("timer2 tog %x\n", tog);

    //以下是利用系统定时器验证定时准确性，不是必要的功能代码
    printf("mtime high %d, low %d\n", REG32(MTIMEHI), REG32(MTIMELO));
	count = REG32(MTIMELO);
	diff  = count - prev_count;
	printf("mtime different from prev count %d, time %d\n", diff, diff*TICK/1000);
	prev_count = count;
}

//功能延时时delay不能设置太小，否则受打印耗时影响过大，打印看不出定时器定时效果，
//需要在100000及以上，如果使用示波器抓去，则去掉打印，delay数值大小均可
int tim_timer_example(int timer, int delay)
{
	switch(timer)
	{
	case 1:
	    TIM_DeInit(TIM1);
        GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);
        gDel = delay;
        TIM_TimerInit(TIM1, delay);
        PLIC_SetPriority(TIMER1_IRQn, 1);
        PLIC_EnableIRQ(TIMER1_IRQn);
        TIM_ClrIntFlag(TIM1);
        TIM_EnableIRQ(TIM1);
        TIM_EnableControl(TIM1, ENABLE);
	    break;
	case 2:
	    TIM_DeInit(TIM2);
        GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);
        gDel = delay;
        TIM_TimerInit(TIM2, delay);
        PLIC_SetPriority(TIMER2_IRQn, 1);
        PLIC_EnableIRQ(TIMER2_IRQn);
        TIM_ClrIntFlag(TIM2);
        TIM_EnableIRQ(TIM2);
        TIM_EnableControl(TIM2, ENABLE);
	    break;
	default:
		break;
	}

    return delay;
}
SHELL_EXPORT_CMD(tim_timer_example, tim_timer_example, timer<1-2> delay<0-x>);
