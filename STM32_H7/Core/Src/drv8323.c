//
// Created by DSlobodzian on 9/10/2021.
//
#include "drv8323.h"

uint8_t DRV_Init(DRV8323 *drv, SPI_HandleTypeDef *spiHandler, GPIO_TypeDef *csPinBank, uint16_t csPin) {
    uint8_t status = 0;

    drv->spiHandler = spiHandler;
    drv->csPinBank = csPinBank;
    drv->csPin = csPin;
    return status;
}

uint8_t DRV_WriteRegister(DRV8323 *drv, uint8_t regAddr) {
    // Set which address we will be reading
    drv->txBuf[0] = (regAddr << 11) | 0x8000;

    HAL_GPIO_WritePin(drv->csPinBank, drv->csPin, GPIO_PIN_RESET);

    uint8_t status = (HAL_SPI_TransmitReceive(
            drv->spiHandler,
            (uint8_t*) drv->txBuf[0],
            (uint8_t*) drv->rxBuf[0],
           1, TIMEOUT)== HAL_OK);
    return status;
}