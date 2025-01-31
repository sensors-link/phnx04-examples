/**
 * @file uart.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"
#include "uart.h"
#include "iom.h"

/**
 * @brief uart init
 *
 * @param iUartNo :UART1,UART2
 * @param
 * port:UART1_PORT_P14_P15,UART1_PORT_P18_P19,UART2_PORT_P04_P05,UART2_PORT_P06_P07
 * @param mode : UART_MODE_8B_SYNC , UART_MODE_10B_ASYNC , UART_MODE_11B_ASYNC
 * @param iBaud :baud:
 * @return: TURE , FALSE
 */
void UART_Init(UART_Type *psUart, int port, int mode, int iBaud)
{
    u32 pclk;
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    PARAM_CHECK((mode != UART_MODE_10B_ASYNC) && (mode != UART_MODE_8B_SYNC) && (mode != UART_MODE_11B_ASYNC));
    SystemCoreClockUpdate();
    pclk = SYSC_GetAPBCLK();
    SYSC->CLKENCFG |= SYSC_CLKENCFG_IOM;
    if (psUart == UART1)
    {
        PARAM_CHECK((port != UART1_PORT_P14_P15) && (port != UART1_PORT_P18_P19));
        if (port == UART1_PORT_P14_P15)
        {
        	IOM->PU |= GPIO_PIN14;
            IOM->AF0 &= ~IOM_AF0_P14_SEL;
            IOM->AF0 |= (1 << 28);
            IOM->AF0 &= ~IOM_AF0_P15_SEL;
            IOM->AF0 |= (1 << 30);
        }
        else
        {
        	IOM->PU |= GPIO_PIN18;
            IOM->AF1 &= ~IOM_AF1_P18_SEL;
            IOM->AF1 |= (3 << 4);
            IOM->AF1 &= ~IOM_AF1_P19_SEL;
            IOM->AF1 |= (3 << 6);
        }
        SYSC->CLKENCFG |= SYSC_CLKENCFG_UART1;
        if (mode == UART_MODE_8B_SYNC)
        {
            PARAM_CHECK(pclk / (2 * iBaud) < 1);
            psUart->BDIV = (pclk + iBaud) / (2 * iBaud) - 1;
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_8B_SYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
        else if (mode == UART_MODE_10B_ASYNC)
        {
            PARAM_CHECK(pclk / (16 * iBaud) < 1);
            psUart->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_10B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
        else
        {
            PARAM_CHECK(pclk / (16 * iBaud) < 1);
            psUart->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_11B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
    }
    else if (psUart == UART2)
    {
        PARAM_CHECK((port != UART2_PORT_P04_P05) && (port != UART2_PORT_P06_P07));
        if (port == UART2_PORT_P04_P05)
        {
        	IOM->PU |= GPIO_PIN4;
            IOM->AF0 &= ~IOM_AF0_P04_SEL;
            IOM->AF0 |= (2<< 8);
            IOM->AF0 &= ~IOM_AF0_P05_SEL;
            IOM->AF0 |= (2 << 10);
        }
        else
        {
        	IOM->PU |= GPIO_PIN6;
            IOM->AF0 &= ~IOM_AF0_P06_SEL;
            IOM->AF0 |= (3 << 12);
            IOM->AF0 &= ~IOM_AF0_P07_SEL;
            IOM->AF0 |= (3 << 14);
        }
        SYSC->CLKENCFG |= SYSC_CLKENCFG_UART2;
        if (mode == UART_MODE_8B_SYNC)
        {
            PARAM_CHECK(pclk / (2 * iBaud) < 1);
            psUart->BDIV = (pclk + iBaud) / (2 * iBaud);
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_8B_SYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
        else if (mode == UART_MODE_10B_ASYNC)
        {
            PARAM_CHECK(pclk / (16 * iBaud) < 1);
            psUart->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_10B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
        else
        {
            PARAM_CHECK(pclk / (16 * iBaud) < 1);
            psUart->BDIV = (pclk + 8 * iBaud) / (16 * iBaud) - 1;
            psUart->SCON &= ~UART_SCON_SM01;
            psUart->SCON |= ((UART_MODE_11B_ASYNC) << UART_SCON_SM01_pos) | UART_SCON_REN;
        }
    }
}

/**
 * @brief uart deinit
 *
 * @param psUart :UART1,UART2
 */
void UART_DeInit(UART_Type *psUart)
{
    int i;
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    if (psUart == UART1)
    {
        SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
        SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
        SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_UART1;
        for (i = 10; i > 0; --i)
            ;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_UART1;
    }
    else if (psUart == UART2)
    {
        SYSC->WRPROCFG = SYSC_WRPROCFG_V0;
        SYSC->WRPROCFG = SYSC_WRPROCFG_V1;
        SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_UART2;
        for (i = 10; i > 0; --i)
            ;
        SYSC->CLKENCFG &= ~SYSC_CLKENCFG_UART2;
    }
}

/**
 * @brief recieve date verify configure
 *
 * @param psUart :UART1,UART2
 * @param chk :UART_VERIFY_SEL_EVEN,UART_VERIFY_SEL_ODD
 */
void UART_RcvVerifyCfg(UART_Type *psUart, int chk)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    PARAM_CHECK((chk != UART_VERIFY_SEL_EVEN) && (chk != UART_VERIFY_SEL_ODD));
    if (chk == UART_VERIFY_SEL_EVEN)
    {
        psUart->SCON |= (1 << 11);
    }
    else
    {
        psUart->SCON &= ~(1 << 11);
    }
}
/**
 * @brief enable control
 *
 * @param psUart :UART1,UART2
 * @param enType :UART_EN_TYPE_SM2 | UART_EN_TYPE_REN | UART_EN_TYPE_SFD,支持或操作一次设置多个
 */
void UART_EnableControl(UART_Type *psUart, int enType)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    if (enType & UART_EN_TYPE_SM2)
        psUart->SCON |= (1 << 7);
    else
        psUart->SCON &= ~(1 << 7);
    if (enType & UART_EN_TYPE_REN)
        psUart->SCON |= (1 << 6);
    else
        psUart->SCON &= ~(1 << 6);
    if (enType & UART_EN_TYPE_SFD)
        psUart->SCON |= (1 << 0);
    else
        psUart->SCON &= ~(1 << 0);
}
/**
 * @brief enable interrupt
 *
 * @param psUart :UART1,UART2
 * @param type: UART_IRQ_TYPE_RXST | UART_IRQ_TYPE_RX | UART_IRQ_TYPE_TX,支持或操作一次设置多个
 */
void UART_EnableIRQ(UART_Type *psUart, int type)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    if (type & UART_IRQ_TYPE_RXST)
        psUart->SCON |= (1 << 3);
    if (type & UART_IRQ_TYPE_RX)
        psUart->SCON |= (1 << 2);
    if (type & UART_IRQ_TYPE_TX)
        psUart->SCON |= (1 << 1);
}
/**
 * @brief disable interrupt
 *
 * @param psUart :UART1,UART2,LPUART
 * @param type: UART_IRQ_TYPE_RXST | UART_IRQ_TYPE_RX | UART_IRQ_TYPE_TX,支持或操作一次设置多个
 */
void UART_DisableIRQ(UART_Type *psUart, int type)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    if (type & UART_IRQ_TYPE_RXST)
        psUart->SCON &= ~(1 << 3);
    if (type & UART_IRQ_TYPE_RX)
        psUart->SCON &= ~(1 << 2);
    if (type & UART_IRQ_TYPE_TX)
        psUart->SCON &= ~(1 << 1);
}
/**
 * @brief uart send one data
 *
 * @param psUart :UART1,UART2
 * @param u8Dat : send data
 */
void UART_Send(UART_Type *psUart, u8 u8Dat)
{
    psUart->SBUF = u8Dat;
    while ((psUart->ISR & UART_ISR_TI) != UART_ISR_TI)
        ;
    psUart->ISR = UART_ISR_TI;
}

/**
 * @brief uart recieve one data
 *
 * @param psUart :UART1,UART2
 * @return u8: rcv data
 */
u8 UART_Receive(UART_Type *psUart)
{
    while ((psUart->ISR & UART_ISR_RI) != UART_ISR_RI)
        ;
    psUart->ISR = UART_ISR_RI;
    return psUart->SBUF;
}

/**
 * @brief uart send a 9bit data
 *
 * @param psUart :UART1,UART2
 * @param dat : send data
 */
void UART_Send9BitData(UART_Type *psUart, u16 dat)
{
    if (dat & (1 << 8))
    {
        psUart->SCON |= UART_SCON_TB8;
    }
    else
    {
        psUart->SCON &= ~UART_SCON_TB8;
    }
    psUart->SBUF = dat;
    while ((psUart->ISR & UART_ISR_TI) != UART_ISR_TI)
        ;
    psUart->ISR = UART_ISR_TI;
}

/**
 * @brief uart recieve a 9bit data
 *
 * @param psUart :UART1,UART2
 * @return u16: rcv data
 */
u16 UART_Receive9BitData(UART_Type *psUart)
{
    while ((psUart->ISR & UART_ISR_RI) != UART_ISR_RI)
        ;
    psUart->ISR = UART_ISR_RI;
    if (psUart->SCON & UART_SCON_RB8)
        return psUart->SBUF | (1ul << 8);
    else
        return psUart->SBUF;
}
/**
 * @brief 写数据到发送寄存器包括bit8
 *
 * @param psUart:UART1,UART2
 * @param dat send data
 * @note 不查询发送完成标�? */
void UART_WriteData(UART_Type *psUart, u16 dat)
{
    if (dat & (1 << 8))
    {
        psUart->SCON |= UART_SCON_TB8;
    }
    else
    {
        psUart->SCON &= ~UART_SCON_TB8;
    }
    psUart->SBUF = dat;
}
/**
 * @brief 读接收寄存器数据包括bit8
 *
 * @param psUart UART1,UART2
 * @return u16 rcv data
 */
u16 UART_ReadData(UART_Type *psUart)
{
    if (psUart->SCON & UART_SCON_RB8)
        return psUart->SBUF | (1ul << 8);
    else
        return psUart->SBUF;
}
/**
 * @brief set address and address valid bits
 *
 * @param psUart:UART1,UART2
 * @param addr:val
 * @param addrCMPBits:val
 */
void UART_SetAddrAndMask(UART_Type *psUart, u8 addr, u8 addrCMPBits)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    psUart->SADDR = addr;
    psUart->SADEN = addrCMPBits;
}

/**
 * @brief read status regester value
 *
 * @param psUart:UART1,UART2
 * @return u32
 */
u32 UART_GetIntFlag(UART_Type *psUart)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    return psUart->ISR;
}
/**
 * @brief write status regester value
 *
 * @param psUart:UART1,UART2
 * @param val
 */
void UART_ClrIntFlag(UART_Type *psUart, u32 val)
{
    PARAM_CHECK((psUart != UART1) && (psUart != UART2));
    psUart->ISR = val;
}
