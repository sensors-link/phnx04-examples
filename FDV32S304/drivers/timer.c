/**
 * @file timer.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"
#include "timer.h"
#include "iom.h"

/**
 * @brief  timer init
 *
 * @param pTim :TIM1-2
 * @param del :us
 */
void TIM_TimerInit(TIM_Type *pTim, int del)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    SystemCoreClockUpdate();
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2))
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;

    if (pTim == TIM1)
    {
        int pclk = SYSC_GetAPBCLK() / ((SYSC->TIMCLKDIV & 0xff) + 1);
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        int cnt = (long long)del * pclk / 1000000;
        PARAM_CHECK(cnt < 1);
        if (cnt > 0xffff)
        {
            TIMERS->CON &= ~TIM_CON_TM_TIM1;
            TIM1->CTCG1 = cnt & 0xffff;
            TIM1->CTCG2 = cnt >> 16;
        }
        else
        {
            TIMERS->CON |= TIM_CON_TM_TIM1;
            TIM1->CTCG1 = cnt;
        }
        // TIMERS->CON |= TIM_CON_TE_TIM1;
    }
    else if (pTim == TIM2)
    {
        int pclk = SYSC_GetAPBCLK() / ((SYSC->TIMCLKDIV >> 8) + 1);
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        int cnt = (long long)del * pclk / 1000000;
        PARAM_CHECK(cnt < 1);
        if (cnt > 0xffff)
        {
            TIMERS->CON &= ~TIM_CON_TM_TIM2;
            TIM2->CTCG1 = cnt & 0xffff;
            TIM2->CTCG2 = cnt >> 16;
        }
        else
        {
            TIMERS->CON |= TIM_CON_TM_TIM2;
            TIM2->CTCG1 = cnt;
        }
        // TIMERS->CON |= TIM_CON_TE_TIM2;
    }
}

/**
 * @brief counter init
 *
 * @param pTim :TIM1-2
 * @param cntPolarity :TIM_CNT_POLARITY_HIGH , TIM_CNT_POLARITY_LOW
 * @param portSel :TIM1_CNT_PORT_P6_P7 , TIM2_CNT_PORT_P12_P13
 */
void TIM_CounterInit(TIM_Type *pTim, int cntPolarity, int portSel)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2))
    if (pTim == TIM1)
    {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM1;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH)
        {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
        }
        else
        {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM1;
        }
        PARAM_CHECK(portSel != TIM1_CNT_PORT_P6_P7);
        IOM->AF0 &= ~IOM_AF0_P06_SEL;
        IOM->AF0 |= (2 << 12);
        IOM->AF0 &= ~IOM_AF0_P07_SEL;
        IOM->AF0 |= (2 << 14);
        TIMERS->CON |= TIM_CON_EXTEN_TIM1;
        // TIMERS->CON |= TIM_CON_TE_TIM1;
    }
    else if (pTim == TIM2)
    {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        TIMERS->CON &= ~TIM_CON_TM_TIM2;
        PARAM_CHECK((cntPolarity != TIM_CNT_POLARITY_HIGH) && (cntPolarity != TIM_CNT_POLARITY_LOW));
        if (cntPolarity == TIM_CNT_POLARITY_HIGH)
        {
            TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
        }
        else
        {
            TIMERS->CON |= TIM_CON_EXTPOL_TIM2;
        }
        PARAM_CHECK(portSel != TIM2_CNT_PORT_P12_P13);
        IOM->AF0 &= ~IOM_AF0_P12_SEL;
        IOM->AF0 |= (2 << 24);
        IOM->AF0 &= ~IOM_AF0_P13_SEL;
        IOM->AF0 |= (2 << 26);

        TIMERS->CON |= TIM_CON_EXTEN_TIM2;
        // TIMERS->CON |= TIM_CON_TE_TIM2;
    }
}

/**
 * @brief pwm init
 *
 * @param pTim :TIM1-2
 * @param pwmPolarity :TIM_PMW_POL_xxxx;
 * @param freq : Hz
 * @param duty :exp:duty=50 (50%)
 * @param portSel :TIMN_PWM_PORT_xxxx;
 * @param dtGap :us
 */
void TIM_PWMInit(TIM_Type *pTim, int pwmPolarity, int freq, int duty, int portSel, int dtGap)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2))
    SystemCoreClockUpdate();
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_IOM;
    if (pTim == TIM1)
    {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM1_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM1;
        TIMERS->CON |= TIM_CON_PWM_TIM1;
        PARAM_CHECK((portSel != TIM1_PWM_PORT_P12_P16) && (portSel != TIM1_PWM_PORT_P14_P16));
        if (portSel == TIM1_PWM_PORT_P12_P16)
        {
            IOM->AF0 &= ~IOM_AF0_P12_SEL;
            IOM->AF0 |= (1 << 24);
            IOM->AF1 &= ~IOM_AF1_P16_SEL;
            IOM->AF1 |= (1 << 0);
        }
        else
        {
            IOM->AF0 &= ~IOM_AF0_P14_SEL;
            IOM->AF0 |= (3 << 28);
            IOM->AF1 &= ~IOM_AF1_P16_SEL;
            IOM->AF1 |= (1 << 0);
        }
        int div = SYSC->TIMCLKDIV & 0xff;
        int tcnt, pclk;
        while (1)
        {
            pclk = SYSC_GetAPBCLK() / (div + 1);
            tcnt = pclk / (freq);
            if (tcnt > 0xffff)
            {
                ++div;
            }
            else
            {
                if (tcnt < 1)
                    --div;
                PARAM_CHECK(div < 0);
                break;
            }
        }
        SYSC->TIMCLKDIV &= ~SYSC_TIM1CLKDIV;
        SYSC->TIMCLKDIV |= div;
        TIM1->CTCG2 = tcnt * (duty) / 100;
        TIM1->CTCG1 = tcnt - (TIM1->CTCG2);
        TIM1->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
        {
            TIM1->PWCON |= (1 << 17);
        }
        else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
        {
            TIM1->PWCON |= (2 << 17);
        }
        else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
        {
            TIM1->PWCON |= (3 << 17);
        }
        if (dtGap > 0)
        {
            TIM1->PWCON |= (1 << 16);
            tcnt = (long long )pclk * dtGap / 1000000 ;
            PARAM_CHECK(tcnt > 0xffff);
            TIM1->PWCON &= ~0xffff;
            TIM1->PWCON |= tcnt;
        }
        else
        {
            TIM1->PWCON &= ~(1 << 16);
        }
        // TIMERS->CON |= TIM_CON_TE_TIM1;
    }
    else if (pTim == TIM2)
    {
        SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM2_CNT;
        TIMERS->CON |= TIM_CON_TM_TIM2;
        TIMERS->CON |= TIM_CON_PWM_TIM2;
        PARAM_CHECK((portSel != TIM2_PWM_PORT_P13_P17) && (portSel != TIM2_PWM_PORT_P15_P17));
        if (portSel == TIM2_PWM_PORT_P13_P17)
        {
            IOM->AF0 &= ~IOM_AF0_P13_SEL;
            IOM->AF0 |= (1 << 26);
            IOM->AF1 &= ~IOM_AF1_P17_SEL;
            IOM->AF1 |= (1 << 2);
        }
        else
        {
            IOM->AF0 &= ~IOM_AF0_P15_SEL;
            IOM->AF0 |= (3 << 30);
            IOM->AF1 &= ~IOM_AF1_P17_SEL;
            IOM->AF1 |= (1 << 2);
        }
        int div = SYSC->TIMCLKDIV >> 8;
        int tcnt, pclk;
        while (1)
        {
            pclk = SYSC_GetAPBCLK() / (div + 1);
            tcnt = pclk / (freq);
            if (tcnt > 0xffff)
            {
                ++div;
            }
            else
            {
                if (tcnt < 1)
                    --div;
                PARAM_CHECK(div < 0);
                break;
            }
        }
        SYSC->TIMCLKDIV &= ~SYSC_TIM2CLKDIV;
        SYSC->TIMCLKDIV |= div << 8;
        TIM2->CTCG2 = tcnt * (duty) / 100;
        TIM2->CTCG1 = tcnt - (TIM2->CTCG2);

        TIM2->PWCON &= ~TIM_PWCON_PWMCPOL;
        PARAM_CHECK((pwmPolarity != TIM_PWM_POL_PWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_PWM0_NPWM1) &&
                    (pwmPolarity != TIM_PWM_POL_NPWM0_PWM1) && (pwmPolarity != TIM_PWM_POL_NPWM0_NPWM1));
        if (pwmPolarity == TIM_PWM_POL_NPWM0_PWM1)
        {
            TIM2->PWCON |= (1 << 17);
        }
        else if (pwmPolarity == TIM_PWM_POL_PWM0_NPWM1)
        {
            TIM2->PWCON |= (2 << 17);
        }
        else if (pwmPolarity == TIM_PWM_POL_NPWM0_NPWM1)
        {
            TIM2->PWCON |= (3 << 17);
        }
        if (dtGap > 0)
        {
            TIM2->PWCON |= (1 << 16);
            tcnt =  (long long )pclk * dtGap / 1000000 ;
            PARAM_CHECK(tcnt > 0xffff);
            TIM2->PWCON &= ~0xffff;
            TIM2->PWCON |= tcnt;
        }
        else
        {
            TIM2->PWCON &= ~(1 << 16);
        }
        // TIMERS->CON |= TIM_CON_TE_TIM2;
    }
}
/**
 * @brief Timer deinit
 *
 * @param pTim:TIM1-2
 */
void TIM_DeInit(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        TIMERS->CON &= ~(TIM_CON_TE_TIM1 | TIM_CON_TM_TIM1 | TIM_CON_PWM_TIM1 | TIM_CON_EXTEN_TIM1 //|TIM_CON_IE_TIM1
                         | TIM_CON_EXTPOL_TIM1 | TIM_CON_PAUSE_TIM1);
    }
    else if (pTim == TIM2)
    {
        TIMERS->CON &= ~(TIM_CON_TE_TIM2 | TIM_CON_TM_TIM2 | TIM_CON_PWM_TIM1 | TIM_CON_EXTEN_TIM1 | //|TIM_CON_IE_TIM1
                         TIM_CON_EXTPOL_TIM1 | TIM_CON_PAUSE_TIM1);
    }
    if ((TIMERS->CON & TIM_CON_TE) == 0)
    {
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIM_PCK;
    }
}
/**
 * @brief 使能控制
 *
 * @param pTim : TIM1-2
 * @param iCtrl ：ENABLE or DISABLE
 */
void TIM_EnableControl(TIM_Type *pTim, int iCtrl)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (iCtrl == ENABLE)
    {
        switch ((int)pTim)
        {
        case (int)TIM1:
            TIMERS->CON |= TIM_CON_TE_TIM1;
            break;
        case (int)TIM2:
            TIMERS->CON |= TIM_CON_TE_TIM2;
            break;
        }
    }
    else
    {
        switch ((int)pTim)
        {
        case (int)TIM1:
            TIMERS->CON &= ~TIM_CON_TE_TIM1;
            break;
        case (int)TIM2:
            TIMERS->CON &= ~TIM_CON_TE_TIM2;
            break;
        }
    }
}
/**
 * @brief Timer interrupt enable
 *
 * @param pTim :TIM1-2
 */
void TIM_EnableIRQ(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        TIMERS->CON |= (1 << 8);
    }
    else if (pTim == TIM2)
    {
        TIMERS->CON |= (1 << 9);
    }
}

/**
 * @brief Timer interrupt disable
 *
 * @param pTim:TIM1-2
 */
void TIM_DisableIRQ(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        TIMERS->CON &= ~(1 << 8);
    }
    else if (pTim == TIM2)
    {
        TIMERS->CON &= ~(1 << 9);
    }
}

/**
 * @brief Timer stop counter
 *
 * @param pTim :TIM1-2
 * @param ctr :ENABLE , DISABLE
 */
void TIM_PauseCntControl(TIM_Type *pTim, ControlStatus ctl)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    PARAM_CHECK((ctl != ENABLE) && (ctl != DISABLE));
    if (pTim == TIM1)
    {
        if (ctl == ENABLE)
        {
            TIMERS->CON |= (1 << 24);
        }
        else
        {
            TIMERS->CON &= ~(1 << 24);
        }
    }
    else if (pTim == TIM2)
    {
        if (ctl == ENABLE)
        {
            TIMERS->CON |= (1 << 25);
        }
        else
        {
            TIMERS->CON &= ~(1 << 25);
        }
    }
}

/**
 * @brief get timer interrupt flag
 *
 * @param pTim :TIM1-2
 * @return FlagStatus : SET , RESET
 */
FlagStatus TIM_GetIntFlag(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        return (TIMERS->INTFLAG & (1 << 0)) ? SET : RESET;
    }
    else if (pTim == TIM2)
    {
        return (TIMERS->INTFLAG & (1 << 1)) ? SET : RESET;
    }
}
/**
 * @brief clear timer interrupt flag
 *
 * @param pTim :TIM1-2
 */
void TIM_ClrIntFlag(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        TIMERS->INTCLR = (1 << 0);
    }
    else if (pTim == TIM2)
    {
        TIMERS->INTCLR = (1 << 1);
    }
}
/**
 * @brief 获得当前计数值
 *
 * @param pTim TIM1、TIM2
 * @return u32 计数结果
 */
u32 TIM_GetCurentCounter(TIM_Type *pTim)
{
    PARAM_CHECK((pTim != TIM1) && (pTim != TIM2));
    if (pTim == TIM1)
    {
        return TIM1->CTVAL;
    }
    else if (pTim == TIM2)
    {
        return TIM2->CTVAL;
    }
}
