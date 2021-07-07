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
    printf("p09 input counter pulse,press any key to print cnt value\r\n");
    //TIM_CounterInit(TIM1, TIM_CNT_POLARITY_HIGH, TIM1_CNT_PORT_P8_P9);
    u32 cnt = TIM1->CTVAL;
    printf("cnt:%d\r\n", cnt);

    return 0;
}
SHELL_EXPORT_CMD(counter_example, tim_counter_example, timer counter example);
