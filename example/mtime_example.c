/**
 * @file mtime_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-07-09
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"

#define MTIMECMPLO    (0xE0000004)
#define MTIMECMPHI    (0xE0000008)
#define MTIMELO       (0xE000000C)
#define MTIMEHI       (0xE0000010)

int mtime_example(void)
{
	int prev_count = 0;
	int count = 0;
	int diff[100] = {0};
	int i = 0;

	REG32(MTIMECMPLO) = 0x10;
	REG32(MTIMECMPHI) = 0x00;
	REG32(MTIMELO)    = 0x00;
	REG32(MTIMEHI)    = 0x00;

	SoftTrigIRQ();

	count = REG32(MTIMELO);

	for(i=0; i<100; i++)
	{
		count = REG32(MTIMELO);
		diff[i] = count - prev_count;
		printf("%d, %d\n", count, diff[i]);
		prev_count = count;
	}

    return count;
}
SHELL_EXPORT_CMD(mtime_example, mtime_example, mtime example);



