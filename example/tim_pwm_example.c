/**
 * @file tim_pwm_example.c
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

#define LED_PIN       GPIO_PIN12

#define LED_ON        GPIO_SetPin(LED_PIN)
#define LED_OFF       GPIO_ClrPin(LED_PIN)

int tim_pwm_example(void)
{
    //TIM_PWMInit(TIM1, TIM_PWM_POL_PWM0_PWM1, 1, 50, TIM1_PWM_PORT_P8_P9, 0);

	return 0;
}
SHELL_EXPORT_CMD(pwm_example, tim_pwm_example, timer pwm example);
