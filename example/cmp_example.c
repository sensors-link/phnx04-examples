/**
 * @file cmp_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-07-2
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"


int cmp_example(int hyssel, int vinsel, int vipsel, int inv)
{
	int l_hyssel = 0;
	int l_vinsel = 0;
	int l_vipsel = 0;
	int l_inv    = 0;
	int temp     = 0;

	l_hyssel = hyssel;
    l_vinsel = vinsel;
	l_vipsel = vipsel;
	l_inv    = inv;

	printf("hyssel %d, vinsel %d, vipsel %d, inv %d\n", l_hyssel, l_vinsel, l_vipsel, l_inv);

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	CMP->CFG &= ~BITS(8,9);        // Step1： 配置 CMP.CFG.HYSSEL， 设置迟滞功能和迟滞大小。
	CMP->CFG |= (hyssel << 8);

	CMP->CFG &= ~BIT(0);           // Step2： 配置 CMP.CFG.INV， 设置比较器输出结果是反向还是正向。

	CMP->CFG |= (vinsel << 5);     // Step3： 配置 CMP.CFG.VINSEL， 选择比较器负端输入信号。
	switch(vinsel)                 // 根据输入项不同，需要进行额外配置，如GPIO等
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
    default:
	    break;
	}

	CMP->CFG |= (vipsel << 2);     // Step4： 配置 CMP.CFG.VIPSEL， 选择比较器正端输入信号。
	switch(vipsel)                 // 根据输入项不同，需要进行额外配置，如GPIO等
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
    default:
	    break;
	}

	CMP->CFG |= BIT(0);            // Step5： 设置 CMP.CFG.CMP_EN 为 1， 开启比较器模块。
	temp = CMP->ANAC_FLAG;         // Step6： 查询 SDC.ANAC_FLAG.CMP_OUT， 获取比较器输出结果。

    return temp;
}
SHELL_EXPORT_CMD(cmp, cmp_example, hys<0-3> vin<0-7> vip<0-7> inv<0-1>);
