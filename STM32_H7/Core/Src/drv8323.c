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

uint16_t DRV_WriteSPI(DRV8323 *drv, uint16_t value) {
    drv->tx_control_word = value;

    HAL_GPIO_WritePin(drv->csPinBank, drv->csPin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(
            drv->spiHandler,
            (uint8_t*) drv->txBuf,
            (uint8_t*) drv->rxBuf,
            1, TIMEOUT);

    HAL_GPIO_WritePin(drv->csPinBank, drv->csPin, GPIO_PIN_SET);

    return drv->rx_control_word;
}

uint16_t DRV_ReadRegister(DRV8323 *drv, uint8_t regAddr) {
    return DRV_WriteSPI(drv, (regAddr << 11) | 0x8000);
}

FAULT_STATUS_ONE DRV_ReadFaultStatusOne(DRV8323 *drv) {
    uint16_t val = DRV_ReadRegister(drv, FS1);
    FAULT_STATUS_ONE fs1;
    fs1.FAULT = CHECK_BIT(val, 11);
    fs1.VDS_OCP = CHECK_BIT(val, 10);
    fs1.GDF = CHECK_BIT(val, 9);
    fs1.UVLO = CHECK_BIT(val, 8);
    fs1.OTSD = CHECK_BIT(val, 7);
    fs1.VDS_HA = CHECK_BIT(val, 6);
    fs1.VDS_LA = CHECK_BIT(val, 5);
    fs1.VDS_HB = CHECK_BIT(val, 4);
    fs1.VDS_LB = CHECK_BIT(val, 3);
    fs1.VDS_HC = CHECK_BIT(val, 2);
    fs1.VDS_LC = CHECK_BIT(val, 1);
    return fs1;
}
FAULT_STATUS_TWO DRV_ReadFaultStatusTwo(DRV8323 *drv) {
    uint16_t val = DRV_ReadRegister(drv, FS2);
    FAULT_STATUS_TWO fs2;
    fs2.SA_OC = CHECK_BIT(val, 11);
    fs2.SB_OC = CHECK_BIT(val, 10);
    fs2.SC_OC = CHECK_BIT(val, 9);
    fs2.OTW = CHECK_BIT(val, 8);
    fs2.CPU_V = CHECK_BIT(val, 7);
    fs2.VGS_HA = CHECK_BIT(val, 6);
    fs2.VGS_LA = CHECK_BIT(val, 5);
    fs2.VGS_HB= CHECK_BIT(val, 4);
    fs2.VGS_LB= CHECK_BIT(val, 3);
    fs2.VGS_HC= CHECK_BIT(val, 2);
    fs2.VGS_LC= CHECK_BIT(val, 1);
    return fs2;
}

void DRV_WriteRegister(DRV8323 *drv, uint8_t regAddr) {
    // Set which address we will be reading
    DRV_WriteSPI(drv, (regAddr << 11) | 0x8000);
}


