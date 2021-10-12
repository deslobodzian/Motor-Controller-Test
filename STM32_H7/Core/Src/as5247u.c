//
// Created by dslobodzian on 10/6/2021.
//

#include <as5247u.h>

uint8_t AS5247U_Initialize(AS5247U *enc,
                           SPI_HandleTypeDef *spiHandle,
                           GPIO_TypeDef *csPinBankTop,
                           GPIO_TypeDef *csPinBankBottom,
                           uint16_t csPinTop,
                           uint16_t csPinBottom) {
    enc->spiHandle = spiHandle;
    enc->csPinBankTop = csPinBankTop;
    enc->csPinBankBottom = csPinBankBottom;
    enc->csPinTop = csPinTop;
    enc->csPinBottom = csPinBottom;
    enc->rawPosition = 0;
    enc->velocity = 0;

    //Todo: create the initialization step along with testing the encoder to see if we are reading values correctly.

    return 0;
}

uint16_t AS5247U_ReadSPI(AS5247U *enc, uint16_t addr) {
    enc->txData = 0x4000 | addr;

    HAL_GPIO_WritePin(enc->csPinBankBottom, enc->csPinBottom, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(
            enc->spiHandle,
            (uint8_t*) enc->txBuf,
            (uint8_t*) enc->rxBuf,
            1, TIMEOUT);

    HAL_GPIO_WritePin(enc->csPinBankBottom, enc->csPinBottom, GPIO_PIN_SET);

    return enc->rxData;
}

uint16_t AS5247U_GetVelocity(AS5247U *enc) {
    enc->velocity = AS5247U_ReadSPI(enc, VEL);
    return enc->velocity;
}

uint16_t AS5247U_GetDiagnostic(AS5247U *enc) {
//	return read(enc, DIA);
	return AS5247U_ReadSPI(enc, DIA);
}

uint16_t AS5247U_GetNOP(AS5247U *enc) {
    return AS5247U_ReadSPI(enc, NOP);
}

uint16_t AS5247U_GetPosition(AS5247U *enc) {
	return AS5247U_ReadSPI(enc, ANGLECOM);
}

uint16_t AS5247U_GetErrorReg(AS5247U *enc) {
	return AS5247U_ReadSPI(enc, ERRFL);
}







