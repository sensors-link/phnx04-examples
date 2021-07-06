/**
 * @file spi_slave_example.c
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

int spi_slave_example(void)
{
	//configure gpio
	GPIO_PinSelect(GPIO_PIN14 | GPIO_PIN15 | GPIO_PIN18 | GPIO_PIN19, PIN_FUNC_2);

	SPI_Init(SPI_SLAVE, SPI_CPOL_HIGH, SPI_CPHA_FIST, 10000);

	SPI_ClrCSN();

	//TODO

	SPI_SetCSN();

    return 0;
}
SHELL_EXPORT_CMD(spi_slave_example, spi_slave_example, spi slave example);
