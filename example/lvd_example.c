/**
 * @file lvd_example.c
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


int lvd_example(void)
{
	int temp = 0;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	LVD->CFG |= BITS(8,15);                 // Step1： 配置 LVD.FLT， 设置 LVD 输出结果滤波时间。
	LVD->CFG &=~(BITS(3,6));
	LVD->CFG &=~(BITS(1,2));

	LVD->CFG |= BIT(7);                     // Step2： 配置 LVD.IE， 设置 LVD 是否产生中断信号,通过ANAC中断查看对应标志位。
	                                        // Step3： 配置 PMU.CR.LVDCHIPRSTEN， 设置 LVD 输出信号是否产生复位。
	                                        // 注： 如配置此步骤， 则 Step3 中断信号则相应会失效。
	ANAC_WPT_UNLOCK();
	LVD->CFG |= BIT(0);                     // Step4： 配置 LVD.LVD_EN， 开启 LVD 模块。

	printf("LVD CFG %x\n", LVD->CFG);
	while (!(ANAC->ANAC_FLAG & (1 << 2)));  // Step5： 查询 SDC.ANAC_FLAG.LVD_INTF， 判断 LVD 电压是否低于所设阈值。
	temp = LVD->ANAC_FLAG;

    return temp;
}
SHELL_EXPORT_CMD(lvd, lvd_example, lvd example);
