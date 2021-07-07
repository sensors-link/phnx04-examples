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
#include "platform.h"
#include "shell.h"

static u8 spi_slave_read_write(u8 data)
{
    u8 temp = 0;
    u32 count = 0;

    while (((SPI_GetStatus() & SPI_SR_DONESR) == 0) && (count < 10000))
    {
        count++;
    }
    temp = SPI_RecieveData();

    SPI_SendData(data);

    return temp;
}

int spi_slave_example(u8 data)
{
	int temp = 0;
	int i = 0;

	//configure gpio
	GPIO_PinSelect(GPIO_PIN12 | GPIO_PIN13 | GPIO_PIN18 | GPIO_PIN19, PIN_FUNC_2);

	SPI_Init(SPI_SLAVE, SPI_CPOL_HIGH, SPI_CPHA_FIST, 10000);

	while(i < 100)
	{
	    temp = spi_slave_read_write(data);
	    DelayNus(100);
	    printf("slave recive data %x\n", temp);
	    i++;
	}

    return 0;
}
SHELL_EXPORT_CMD(spi_slave, spi_slave_example, spi slave send <data>);
