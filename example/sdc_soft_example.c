/**
 * @file sdc_soft_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-06-30
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "platform.h"
#include "shell.h"

int sdc_soft_example(void)
{
	int temp_AD;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	SDC->ME_CTL |= BIT(0);                           // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启SDC工作模块。
	SYSC->ANCLKDIV &= ~(BITS(0, 3));                 // Step2：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度即anac_clk_500k=500KHz。
	SYSC->ANCLKDIV |= (1 << 0);                      //       ADC_CLK 4分频，2M
	SYSC->ANCLKDIV &= ~(BITS(4, 8));
	SYSC->ANCLKDIV |= (3 << 4);                      //       4分频 500KHz
	ADC->CFG  &= ~(BITS(4, 5));                      // Step3：配置ADC_CFG.VRSEL，选择ADC参考电压输入源。
	ADC->CFG |= BIT(0);
	ADC->CFG &= ~(BITS(1, 3));
	ADC->CTL |= BIT(1);                              // Step4：配置ADC.CTL.IE，使能ADC中断。
	ADC->CFG |= BIT(0);                              // Step5：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。
	                                                 //       注：如果ADC参考电压选择外部参考电压引脚，则此步骤可忽略。
	SDC->ANAC_CFG |= BIT(6);                         // Step6：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
	DelayNus(150);                                   // Step7：延时150us，等待BGR模块启动完成。
	SDC->ANAC_CFG |= BIT(7);                         // Step8：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
	DelayNus(70);                                    // Step9：延时70us，等待ALDO4A模块启动完成。
	SDC->PDSENS_CFG |= BIT(7);                       // Step10：设置SDC.PDSENS_CFG.CHRG为1，开启PDSENSOR电容充电。
	DelayNus(1000);                                  // Step11：延时1ms，等待PDSENSOR电容充电完成。
	ADC->CFG |= BIT(6);                              // Step12：设置ADC.CFG.BUF_EN为1，使能BUF模块。
	ADC->CTL |= BIT(1);                              // Step13：设置ADC.CTL.ADC_EN为1，使能ADC模块。
	DelayNus(2);                                     // Step14：延时2us，等待ADC模块启动完成。
	ADC->CFG &= ~(BITS(11, 12));                     // Step15：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
	ADC->CFG |= (2 << 11);
	ADC->CFG &= ~(BITS(13, 14));                     // Step16：设置ADC.CTL.SMP_TIME为0，选择单次转换模式。
	ADC->CFG |= (0xC << 7);                          // Step17：设置ADC.CFG.CHSEL为4’b1100，选择PD SENSOR信号作为ADC输入通道。
	SDC->PDSENS_CFG |= BIT(0);                       // Step18：设置SDC.PDSENS_CFG.PDSENS_EN为1，开启PDSENSOR模块。
	SDC->PDSENS_CFG |= BIT(1);                       // Step19：设置SDC.PDSENS_CFG.PDSENS_RST为1，开启PDSENSOR模块复位。
	DelayNus(1000);                                  // Step20：延时1ms。
	SDC->PDSENS_CFG &= ~BIT(1);                      // Step21：设置SDC.PDSENS_CFG.PDSENS_RST为0，关闭PDSENSOR模块复位。
	LED_Driver->CFG |= BIT(0);                       // Step22：设置LED.IIRLED_EN为1，开启红外红光LED模块。
	DelayNus(70);                                    // Step23：延时70us。
	ADC->CTL |= BIT(2);                              // Step24：设置ADC.CTL.SST为1，启动ADC转换。
	while (!(ANAC->ANAC_FLAG & (1 << 0)));           // Step25：等待ADC中断或查询SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果即为烟雾PDSENSOR检测值。
	LED_Driver->CFG &= ~BIT(0);                      // Step26：设置LED.IIRLED_EN为0，关闭红外红光LED模块。

	temp_AD = ADC->AVG_VAL;
	ANAC->ANAC_FLAG = (1 << 0);

	ADC->CTL &= ~(BIT(0));
	ADC->CFG &= ~(BIT(6));
	SDC->ANAC_CFG &= ~(BIT(6) | BIT(7));

    return temp_AD;
}
SHELL_EXPORT_CMD(sdc_soft, sdc_soft_example, sdc soft example);
