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


int cmp_example(int hyssel, int inv, int vinsel, int vipsel)
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

	printf("hyssel %d, inv %d, vinsel %d, vipsel %d\n", l_hyssel, l_inv, l_vinsel, l_vipsel);

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;

	CMP->CFG &= ~BITS(8,9);          // Step1： 配置 CMP.CFG.HYSSEL， 设置迟滞功能和迟滞大小。
	CMP->CFG |= (hyssel << 8);

	switch(inv)                      // Step2： 配置 CMP.CFG.INV， 设置比较器输出结果是反向还是正向。
	{
	case 0:
		//比较器结果正向输出
		CMP->CFG &= ~BIT(1);
		break;
	case 1:
		//比较器结果反向输出
		CMP->CFG |= BIT(1);
		break;
	default:
		break;
	}

	CMP->CFG |= (vinsel << 5);       // Step3： 配置 CMP.CFG.VINSEL， 选择比较器负端输入信号。
	switch(vinsel)                   // 根据输入项不同，需要进行额外配置，如GPIO等
	{
	case 0:
		//外部pin VC1N0
		break;
	case 1:
		//外部pin VC1N1
		break;
	case 2:
		//外部pin VC1N2
		break;
	case 3:
		//voltRef输出vref
		break;
	case 4:
		//基准buf输出voltRef_vo
		break;
	case 5:
		//低功耗基准VBGS
		break;
	case 6:
		//模拟基准VBGA
		break;
	case 7:
		//SLDO输出V1P5S
		break;
    default:
	    break;
	}

	CMP->CFG |= (vipsel << 2);       // Step4： 配置 CMP.CFG.VIPSEL， 选择比较器正端输入信号。
	switch(vipsel)                   // 根据输入项不同，需要进行额外配置，如GPIO等
	{
	case 0:
		//VC1P0
		break;
	case 1:
		//VC1P1
		break;
	case 2:
		//VC1P2
		break;
	case 3:
		//VC1P3
		break;
	case 4:
		//模拟电压Vref_op
		break;
	case 5:
		//模拟基准VBGS
		break;
	case 6:
		//模拟基准VBGA
		break;
	case 7:
		//模拟电压Vbg4a_op
		break;
    default:
	    break;
	}

	CMP->CFG |= BIT(0);              // Step5： 设置 CMP.CFG.CMP_EN 为 1， 开启比较器模块。
	if((CMP->ANAC_FLAG) & BIT(10))   // Step6： 查询 SDC.ANAC_FLAG.CMP_OUT， 获取比较器输出结果。
	{
		temp = 1;
	}
	else
	{
		temp = 0;
	}

    return temp;
}
SHELL_EXPORT_CMD(cmp, cmp_example, hys<0-3> inv<0-1> vin<0-7> vip<0-7>);
