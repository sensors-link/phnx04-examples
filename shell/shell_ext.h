/**
 * @file shell_ext.h
 * @author Letter (NevermindZZT@gmail.com)
 * @brief shell extensions
 * @version 1.0.0
 * @date 2019-01-05
 * 
 * @Copyright (c) 2019 Letter
 * 
 */

#ifndef __SHELL_EXT_H__
#define __SHELL_EXT_H__

#include "shell.h"

/**
 * @brief ��������
 * 
 */
typedef enum
{
    NUM_TYPE_INT,                                           /**< ʮ�������� */
    NUM_TYPE_BIN,                                           /**< ���������� */
    NUM_TYPE_OCT,                                           /**< �˽������� */
    NUM_TYPE_HEX,                                           /**< ʮ���������� */
    NUM_TYPE_FLOAT                                          /**< ������ */
} NUM_Type;

unsigned int shellExtParsePara(char *string);
int shellExtRun(shellFunction function, int argc, char *argv[]);

#endif
