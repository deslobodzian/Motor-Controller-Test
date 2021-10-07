//
// Created by dslobodzian on 10/5/2021.
//

#ifndef STM32_H7_AS5247U_H
#define STM32_H7_AS5247U_H

#include "stm32h7xx_hal.h"

// Volatile Memory Registers:
#define NOP             0x0000
#define ERRFL           0x0001
#define PROG            0x0001
#define DIA             0x3FF5
#define AGC             0x3FF9
#define SIN_DATA        0x3FFA
#define COS_DATA        0x3FFB
#define VEL             0x3FFC
#define MAG             0x3FFD
#define ANGLEUNC        0x3FFE
#define ANGLECOM        0x3FFF
#define ECC_CHECKSUM    0x00D1

// Non-Volatile Memory Registers
#define DISABLE         0x0015
#define ZPOSM           0x0016
#define ZPOSL           0x0017
#define SETTINGS_ONE    0x0018
#define SETTINGS_TWO    0x0019
#define SETTINGS_THREE  0x001A
#define ECC             0x001B

// Other
#define TIMEOUT 1000
typedef struct {
    SPI_HandleTypeDef *spiHandle;
    GPIO_TypeDef  *csPinBankTop;
    GPIO_TypeDef  *csPinBankBottom;
    uint16_t csPinTop;
    uint16_t csPinBottom;
    // use 16-bit SPI frame for now, add CRC frames once basic function is working
    union {
        uint8_t txBuf[2];
        uint16_t txControlWord;
    };
    // use 16-bit SPI frame for now, add CRC frames once basic function is working
    union {
        uint8_t rxBuf[2];
        uint16_t rxControlWord;
    };

    uint16_t rawPosition;
    uint16_t velocity;
} AS5247U;

uint8_t AS5247U_Initialize(AS5247U *enc,
                           SPI_HandleTypeDef *spiHandle,
                           GPIO_TypeDef *csPinBankTop,
                           GPIO_TypeDef *csPinBankBottom,
                           uint16_t csPinTop,
                           uint16_t csPinBottom);
uint16_t AS5247U_ReadSPI(AS5247U *enc, uint16_t addr);
uint16_t AS5247U_GetVelocity(AS5247U *enc);



#endif //STM32_H7_AS5247U_H
