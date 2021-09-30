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
    fs2.VGS_HB = CHECK_BIT(val, 4);
    fs2.VGS_LB = CHECK_BIT(val, 3);
    fs2.VGS_HC = CHECK_BIT(val, 2);
    fs2.VGS_LC = CHECK_BIT(val, 1);
    return fs2;
}

void DRV_WriteRegister(DRV8323 *drv, uint8_t regAddr, uint16_t value) {
    // Set which address we will be reading
    DRV_WriteSPI(drv, (regAddr << 11) | value);
}
void DRV_WriteDCR(DRV8323 *drv,
                  int DIS_CPUV,
                  int DIS_GDF,
                  int ODW_REP,
                  int PWM_MODE,
                  int PWM_COM,
                  int PWM_DIR,
                  int COAST,
                  int BREAK,
                  int CLR_FLT) {
    uint16_t ctrWord =
            (DIS_CPUV << 9) | (DIS_GDF << 8) | (ODW_REP << 7) |
            (PWM_MODE << 5) | (PWM_COM << 4) | (PWM_DIR << 3) |
            (COAST << 2) | (BREAK << 1) | CLR_FLT;
    DRV_WriteRegister(drv, DCR, ctrWord);
}

void DRV_WriteGD_HS(DRV8323 *drv, int LOCK, int IDRIVEP_HS, int IDRIVEN_HS) {
    uint16_t ctrWord = (LOCK << 8) | (IDRIVEP_HS << 4) | IDRIVEN_HS;
    DRV_WriteRegister(drv, GD_HS, ctrWord);
}

void DRV_WriteGD_LS(DRV8323 *drv, int CBC, int TDRIVE, int IDRIVEP_LS, int IDRIVEN_LS) {
    uint16_t ctrWord = (CBC << 10) | (TDRIVE << 8) | (IDRIVEP_LS << 4) | IDRIVEN_LS;
    DRV_WriteRegister(drv, GD_LS, ctrWord);
}

void DRV_WriteOCP(DRV8323 *drv, int TRETRY, int DEAD_TIME, int OCP_MODE, int OCP_DEG, int VDS_LVL) {
    uint16_t ctrWord = (TRETRY << 10) | (DEAD_TIME << 8) | (OCP_MODE << 6) | (OCP_DEG) | VDS_LVL;
    DRV_WriteRegister(drv, OCP, ctrWord);
}

void DRIV_WriteCSA(DRV8323 *drv,
                   int CSA_FET,
                   int VREF_DIF,
                   int LS_REF,
                   int CSA_GAIN,
                   int DIS_SEN,
                   int CSA_CAL_A,
                   int CSA_CAL_B,
                   int CSA_CAL_C,
                   int SEN_LVL) {
    uint16_t ctrWord =
            (CSA_FET << 10) | (VREF_DIF << 9) | (LS_REF << 8) |
            (CSA_GAIN << 6) | (DIS_SEN << 5) | (CSA_CAL_A << 4) |
            (CSA_CAL_B << 3) | (CSA_CAL_C << 2) | SEN_LVL;
    DRV_WriteRegister(drv, CSA, ctrWord);
}
