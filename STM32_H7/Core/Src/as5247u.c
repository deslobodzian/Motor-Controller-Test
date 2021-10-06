//
// Created by dslobodzian on 10/6/2021.
//

#include <as5247u.h>

uint16_t AS5247U_ReadSPI(AS5247U *enc, uint16_t addr, uint16_t val) {
    enc->txControlWord = 0x4000 | addr;
    HAL_GPIO_WritePin(enc->csPinBankBottom, enc->csPinBottom, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(
            enc->spiHandle,
            (uint8_t*) enc->txBuf,
            (uint8_t*) enc->rxBuf,
            1, TIMEOUT);

    HAL_GPIO_WritePin(enc->csPinBankBottom, enc->csPinBottom, GPIO_PIN_SET);

    return enc->rxControlWord;
}

