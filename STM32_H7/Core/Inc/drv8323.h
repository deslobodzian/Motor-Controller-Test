//
// Created by DSlobodzian on 9/4/2021.
//

#ifndef STM32_H7_DRV8323_H
#define STM32_H7_DRV8323_H

#include "stm32h7xx_hal.h"
#include "stdbool.h"

// Registers:
#define FS1     0x00 // Fault Status Register 1 (R)
#define FS2     0x01 // Fault Status Register 2 (R)
#define DCR     0x02 // Drive Control Register (R/W)
#define GD_HS   0x03 // Gate Drive HS Register (R/W)
#define GD_LS   0x04 // Gate Drive LS Register (R/W)
#define OCP     0x05 // OCP Control Register (R/W)
#define CSA     0x06 // CSA Control Register (R/W)

// Drive Control Field Description
#define DIS_CPUV_ENABLE         0x00 // Charge pump UVLO fault is enabled
#define DIS_CPUV_DISABLE        0x01 // Charge pump UVLO fault is disabled
#define DIS_GDF_ENABLE          0x00 // Gate Drive Fault is enabled
#define DIS_GDF_DISABLE         0x01 // Gate Drive Fault is disabled
#define OTW_REP_ENABLE          0x01 // OTW reported on nFault and FAULT bit
#define OTW_REP_DISABLE         0x00 // OTW not reported on nFault and FAULT bit
#define PMW1_COM_SYNC           0x00 // 1x PWM uses synchronous rectification
#define PMW1_COM_ASYNC          0x00 // 1x PWM uses asynchronous rectification
#define COAST_OFF               0x00 // MOSFETs Hi-Z off
#define COAST_ON                0x01 // MOSFETs Hi-Z on
#define CLEAR_FAULT             0x01 // Clear latched fault bits. Resets after being written.

#define TIMEOUT 1000

typedef struct {
    bool fault;
    bool vds_ocp;
    bool gdf;
    bool uvlo;
    bool vds_ha;
    bool vds_la;
    bool vds_hb;
    bool vds_lb;
    bool vds_hc;
    bool vds_lc;
} Fault_Status_One;

typedef struct {

};

enum PWM_MODE{
    k6x = 0x00,
    k3x = 0x01,
    k1x = 0x02,
    kIndependent = 0x03
};

enum I_DRIVE_P {
    k10mA_P = 0x00,
    k30mA_P = 0x01,
    k60mA_P = 0x02,
    k80mA_P = 0x03,
    k120mA_P = 0x04,
    k140mA_P = 0x05,
    k170mA_P = 0x06,
    k190mA_P = 0x07,
    k260mA_P = 0x08,
    k330mA_P = 0x09,
    k370mA_P = 0x0A,
    k440mA_P = 0x0B,
    k570mA_P = 0x0C,
    k680mA_P = 0x0D,
    k820mA_P = 0x0E,
    k1000mA_P = 0x0F
};

enum I_DRIVE_N {
    k20mA_N = 0x00,
    k60mA_N = 0x01,
    k120mA_N = 0x02,
    k160mA_N = 0x03,
    k240mA_N = 0x04,
    k280mA_N = 0x05,
    k340mA_N = 0x06,
    k380mA_N = 0x07,
    k520mA_N = 0x08,
    k660mA_N = 0x09,
    k740mA_N = 0x0A,
    k880mA_N = 0x0B,
    k1140mA_N = 0x0C,
    k1360mA_N = 0x0D,
    k1640mA_N = 0x0E,
    k2000mA_N = 0x0F
};

enum VDS_LEVEL {
    k0V06= 0x00, // 0V06 stands for 0.06V where V is the decimal point as well as indicating the unit.
    k0V13 = 0x01,
    k0V20 = 0x02,
    k0V26 = 0x03,
    k0V31 = 0x04,
    k0V45 = 0x05,
    k0V53 = 0x06,
    k0V60 = 0x07,
    k0V68 = 0x08,
    k0V75 = 0x09,
    k0V94 = 0x0A,
    k1V12 = 0x0B,
    k1V30 = 0x0C,
    k1V50 = 0x0D,
    k1V70 = 0x0E,
    k1V88 = 0x0F
};

typedef struct {
   SPI_HandleTypeDef *spiHandler;
   GPIO_TypeDef *csPinBank;
   uint16_t csPin;
   uint16_t txBuf[10];
   uint16_t rxBuf[10];
} DRV8323;

uint8_t DRV_Init(DRV8323 *drv, SPI_HandleTypeDef *spiHandler, GPIO_TypeDef *csPinBank, uint16_t csPin);

uint8_t DRV_WriteRegister(DRV8323 *drv, uint8_t regAddr);

uint8_t DRV_ReadRegister(DRV8323 *drv, uint8_t regAddr);


#endif //STM32_H7_DRV8323_H
