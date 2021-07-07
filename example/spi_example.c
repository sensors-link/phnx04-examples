/**
 * @file spi_example.c
 * @author david.lin 
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "w25q16.h"
#include "platform.h"

const u8 gWrText[] = {"Ph04 SPIM TEST"};
u8 gRdText[sizeof(gWrText)];

int spi_example(void)
{
    int i;
    printf("spi write w25q16 example\r\n");
    SPI_Flash_Init();
    while (SPI_Flash_ReadID() != W25Q16 && SPI_Flash_ReadID() != W25Q32 &&
           SPI_Flash_ReadID() != W25Q64) {
        printf("read id error\r\n");
        while (1)
            ;
    }

    SPI_Flash_Write((u8 *)gWrText, 0, sizeof(gWrText));
    printf("write text:Ph04 SPIM TEST\r\n");
    SPI_Flash_Read(gRdText, 0, sizeof(gWrText));
    printf("read text:");
    for (i = 0; i < sizeof(gWrText) - 1; ++i) {
        printf("%c", gRdText[i]);
    }
    printf("\r\nend");
    // main loop
    while (1) {
    }
}
