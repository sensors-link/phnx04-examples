/**
 * @file tim_counter_example.c
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

int tim_counter_example(void)
{
	static u8 flag = 1;
	u32 cnt;

	if(flag)
	{
        printf("gpio13 input counter pulse\n");

        GPIO_PinSelect(GPIO_PIN12 | GPIO_PIN13, PIN_FUNC_2);
        TIM_CounterInit(TIM2, TIM_CNT_POLARITY_LOW);
        flag = 0;
	}
    cnt = TIM1->CTVAL;

    return cnt;
}
SHELL_EXPORT_CMD(counter_example, tim_counter_example, timer counter example);
