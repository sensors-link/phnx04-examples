/**
 * @file led_driver_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-06-30
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"


int led_driver_example(void)
{
	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	// Step1： 配置 DCDC.CFG.VSL 为 2’b01， 设置 DCDC 输出电压大小为 5.5V 档。
	// Step2： 设置 DCDC.CCFG.DCDC_EN 为 1， 打开 DCDC 模块。
	// Step3： 等待 SDC.ANAC_FLAG.DCDC_VOK 为 1， DCDC 输出电压达到稳定。
	// Step5： 配置 LED.CFG.IIRLED_CC， 设置红外红光管 LED 端口驱动电流大小。
	// Step5： 配置 LED.CFG.IBLUE_CC， 设置红外蓝光管 LED 端口驱动电流大小。
	// Step6： 配置 LED.CFG.IIRLED_EN， 打开红外红光管 LED 模块。 或者配置 LED.CFG.IBLUE_EN， 打开红外蓝光管 LED 模块
    return 0;
}
SHELL_EXPORT_CMD(led_driver, led_driver_example, led driver example);
