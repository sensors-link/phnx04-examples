/**
 * @file   platform.h
 * @author
 * @brief
 * @version 1.0
 * @date 2021-06-30
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "phnx04.h"

#define TIME_DIFF(s,e) ((s)-(int)(e))

int hal_init(void);
void DelayNus(u32 delay);

#endif/*__PLATFORM_H__*/
