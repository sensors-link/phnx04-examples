/**
 * @file sdc_hard_example.c
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


int sdc_hard_example(void)
{
	int temp_AD;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	SDC->ME_CTL |= BIT(0);                           // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启SDC工作模块。
	SYSC->ANCLKDIV &= ~(BITS(0, 3));                 // Step2：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度即anac_clk_500k=500KHz。
	SYSC->ANCLKDIV |= (1 << 0);                      //       ADC_CLK 4分频，2M
	SYSC->ANCLKDIV &= ~(BITS(4, 8));
	SYSC->ANCLKDIV |= (3 << 4);                      //       4分频 500KHz
	ADC->CFG &= ~(BITS(4, 5));                       // Step3：配置ADC_CFG.VRSEL，选择ADC参考电压输入源。
	ADC->CFG |= BIT(0);
	ADC->CFG &= ~(BITS(1, 3));
	ADC->CTL |= BIT(1);                              // Step4：配置ADC.CTL.IE，使能ADC中断。
	ADC->CFG |= BIT(0);                              // Step5：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。。
	ADC->CFG &= ~(BITS(11, 12));                     // Step6：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
	ADC->CFG |= (2 << 11);
	ADC->CFG &= ~(BITS(13, 14));                     // Step7：设置ADC.CTL.SMP_TIME为0，选择1次转换模式。
	SDC->DLY_CFG &= ~BITS(4,5);                      // Step8： 配置寄存器 DLY_CFG， 确定每个步骤的时间长度。 寄存器 DLY_CFG 的默认值是按照
	                                                 //     anac_clk_500k=500KHz 计算所得。
	SDC->ME_CTL &= ~BITS(8, 10);                     // Step9： 配置 ME_CTL.ADC_TRIG_SEL， 选择 ADC 转换触发源如 TMR1 中断。
	SDC->ME_CTL |= BIT(0);                           // Step10： 配置 ME_CTL.ANAC_EN 开启测量模块使能。
	SDC->ME_CTL |= BIT(4);                           // Step11： 配置 ME_CTL.ME_AUTO 启动自动测量模式。
	SDC->ME_CTL |= (3 << 5);                         // Step12： 配置 ME_CTL.MODE_SEL 选择烟雾检测模式。
	SDC->ME_CTL |= BIT(3);                           // Step13： 配置 ME_CTL.ME_MODE 选择外设中断触发源作为 ADC 转换触发。
	while (!(ANAC->ANAC_FLAG & (1 << 0)));           // Step14： 等待 ADC 中断或查询 SDC.ANAC_CFG.ADC_INTF 为 1， 读取 ADC_VALx 寄存器以获取 ADC 转换结果即为烟雾 PDSENSOR 检测值。
	temp_AD = ADC->AVG_VAL;

    return temp_AD;
}
SHELL_EXPORT_CMD(sdc_hard, sdc_hard_example, sdc hardware example);
