/
// Created by DSlobodzian on 9/4/2021.
//

#ifndef STM32_H7_DRV8323_H
#define STM32_H7_DRV8323_H

#include "stm32h7xx_hal.h"
#include "stdbool.h"

// Registers:
#define FS1     0x0 // Fault Status Register 1 (R)
#define FS2     0x1 // Fault Status Register 2 (R)
#define DCR     0x2 // Drive Control Register (R/W)
#define GD_HS   0x3 // Gate Drive HS Register (R/W)
#define GD_LS   0x4 // Gate Drive LS Register (R/W)
#define OCP     0x5 // OCP Control Register (R/W)
#define CSA     0x6 // CSA Control Register (R/W)

// Drive Control Field Description
#define DIS_CPUV_ENABLE         0x0 // Charge pump UVLO fault is enabled
#define DIS_CPUV_DISABLE        0x1 // Charge pump UVLO fault is disabled
#define DIS_GDF_ENABLE          0x0 // Gate Drive Fault is enabled
#define DIS_GDF_DISABLE         0x1 // Gate Drive Fault is disabled
#define OTW_REP_ENABLE          0x1 // OTW reported on nFault and FAULT bit
#define OTW_REP_DISABLE         0x0 // OTW not reported on nFault and FAULT bit
#define PMW1_COM_SYNC           0x0 // 1x PWM uses synchronous rectification
#define PMW1_COM_ASYNC          0x0 // 1x PWM uses asynchronous rectification
#define COAST_OFF               0x0 // MOSFETs Hi-Z off
#define COAST_ON                0x1 // MOSFETs Hi-Z on
#define CLEAR_FAULT             0x1 // Clear latched fault bits. Resets after being written.

// OCP Control Field Descriptions
#define TRETRY_4ms              0x0 // VDS_OCP and SEN_OCP retry time is 4 ms
#define TRETRY_50us             0x1 // VDS_OCP and SEN_OCP retry time is 50 us

// CSA Control Field
#define CSA_FET_SPx             0x0 // Current sense amplifier positive input is SPx
#define CSA_FET_SHx             0x1 // Current sense amplifier positive input is SHx (also automatically sets the LS_REF bit to 1
#define VREF_DIV_U              0x0 // Current sense amplifier reference voltage is VREF (unidirectional mode)
#define VREF_DIV                0x1 // Current sense amplifier reference voltage is VREF divided by 2.
#define LS_REF_SPx              0x0 // low-side MOSFET is measured across SHx to SPx
#define LS_REF_SNx              0x1 // low-side MOSFET is measured across SHx to SNx
#define DIS_SEN_ENABLE          0x0 // Sense over-current fault is enabled
#define DIS_SEN_DISABLE         0x1 // Sense over-current fault is disabled
#define CSA_CAL_A_NORMAL        0x0 // Normal current sense amplifier A operation
#define CSA_CAL_A_SHORT         0x1 // Short inputs to current sense amplifier A for offset calibration
#define CSA_CAL_B_NORMAL        0x0 // Normal current sense amplifier B operation
#define CSA_CAL_B_SHORT         0x1 // Short inputs to current sense amplifier A for offset calibration
#define CSA_CAL_C_NORMAL        0x0 // Normal current sense amplifier C operation
#define CSA_CAL_C_SHORT         0x1 // Short inputs to current sense amplifier A for offset calibration

#define TIMEOUT 1000
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

typedef struct {
    bool FAULT;   // Logic OR of FAULT status registers. Mirrors nFAULT pin.
    bool VDS_OCP; // VDS monitor over-current fault condition.
    bool GDF;     // Gate drive fault.
    bool UVLO;    // Under-voltage lockout fault.
    bool OTSD;    // Over-temperature shutdown.
    bool VDS_HA;  // VDS over-current fault on A high-side MOSFET.
    bool VDS_LA;  // VDS over-current fault on A low-side MOSFET.
    bool VDS_HB;  // VDS over-current fault on B high-side MOSFET.
    bool VDS_LB;  // VDS over-current fault on B low-side MOSFET.
    bool VDS_HC;  // VDS over-current fault on C high-side MOSFET.
    bool VDS_LC;  // VDS over-current fault on C low-side MOSFET.
} FAULT_STATUS_ONE;

typedef struct {
    bool SA_OC;  // Over current on phase A sense amplifier.
    bool SB_OC;  // Over current on phase B sense amplifier.
    bool SC_OC;  // Over current on phase C sense amplifier.
    bool OTW;    // Over temperature warning
    bool CPU_V;  // Charge pump under-voltage fault condition
    bool VGS_HA; // Gate drive fault on A high-side MOSFET.
    bool VGS_LA; // Gate drive fault on A low-side MOSFET.
    bool VGS_HB; // Gate drive fault on B high-side MOSFET.
    bool VGS_LB; // Gate drive fault on B low-side MOSFET.
    bool VGS_HC; // Gate drive fault on C high-side MOSFET.
    bool VGS_LC; // Gate drive fault on C low-side MOSFET.
} FAULT_STATUS_TWO;

typedef enum PWM_MODE{
    k6x = 0x00,
    k3x = 0x01,
    k1x = 0x02,
    kIndependent = 0x03
} PWM_MODE;

// Gate drive high side
enum I_DRIVE_HS {
    LOCK = 0x6,
    UNLOCK = 0x3,
    k10mA_P_HS = 0x0, // P is turn on current
    k30mA_P_HS = 0x1,
    k60mA_P_HS = 0x2,
    k80mA_P_HS = 0x3,
    k120mA_P_HS = 0x4,
    k140mA_P_HS = 0x5,
    k170mA_P_HS = 0x6,
    k190mA_P_HS = 0x7,
    k260mA_P_HS = 0x8,
    k330mA_P_HS = 0x9,
    k370mA_P_HS = 0xA,
    k440mA_P_HS = 0xB,
    k570mA_P_HS = 0xC,
    k680mA_P_HS = 0xD,
    k820mA_P_HS = 0xE,
    k1000mA_P_HS = 0xF,
    k20mA_N_HS = 0x0, // N is turn off current
    k60mA_N_HS = 0x1,
    k120mA_N_HS = 0x2,
    k160mA_N_HS = 0x3,
    k240mA_N_HS = 0x4,
    k280mA_N_HS = 0x5,
    k340mA_N_HS = 0x6,
    k380mA_N_HS = 0x7,
    k520mA_N_HS = 0x8,
    k660mA_N_HS = 0x9,
    k740mA_N_HS = 0xA,
    k880mA_N_HS = 0xB,
    k1140mA_N_HS = 0xC,
    k1360mA_N_HS = 0xD,
    k1640mA_N_HS = 0xE,
    k2000mA_N_HS = 0xF
};

enum I_DRIVE_LS {
    TDRIVE_500ns = 0x0,
    TDRIVE_1000ns = 0x1,
    TDRIVE_2000ns = 0x2,
    TDRIVE_4000ns = 0x3,
    k10mA_P_LS = 0x0, // P is turn on current
    k30mA_P_LS = 0x1,
    k60mA_P_LS = 0x2,
    k80mA_P_LS = 0x3,
    k120mA_P_LS = 0x4,
    k140mA_P_LS = 0x5,
    k170mA_P_LS = 0x6,
    k190mA_P_LS = 0x7,
    k260mA_P_LS = 0x8,
    k330mA_P_LS = 0x9,
    k370mA_P_LS = 0xA,
    k440mA_P_LS = 0xB,
    k570mA_P_LS = 0xC,
    k680mA_P_LS = 0xD,
    k820mA_P_LS = 0xE,
    k1000mA_P_LS = 0xF,
    k20mA_N_LS = 0x0, // N is turn off current
    k60mA_N_LS = 0x1,
    k120mA_N_LS = 0x2,
    k160mA_N_LS = 0x3,
    k240mA_N_LS = 0x4,
    k280mA_N_LS = 0x5,
    k340mA_N_LS = 0x6,
    k380mA_N_LS = 0x7,
    k520mA_N_LS = 0x8,
    k660mA_N_LS = 0x9,
    k740mA_N_LS = 0xA,
    k880mA_N_LS = 0xB,
    k1140mA_N_LS = 0xC,
    k1360mA_N_LS = 0xD,
    k1640mA_N_LS = 0xE,
    k2000mA_N_LS = 0xF
};

enum DEAD_TIME {
    k50ns = 0x0,
    k100ns = 0x1,
    k200ns = 0x2,
    k400ns = 0x3
};

enum OCP_MODE {
    LATCHED_FAULT = 0x0,
    RETRY_FAULT = 0x1,
    REPORT_NO_ACTION = 0x2,
    NO_REPORT_OR_ACTION = 0x3
};

enum OCP_DEG {
    k2us = 0x0,
    k4us = 0x1,
    k6us = 0x2,
    k8us = 0x3
};

enum VDS_LEVEL {
    k0V06= 0x0, // 0V06 stands for 0.06V where V is the decimal point as well as indicating the unit.
    k0V13 = 0x1,
    k0V20 = 0x2,
    k0V26 = 0x3,
    k0V31 = 0x4,
    k0V45 = 0x5,
    k0V53 = 0x6,
    k0V60 = 0x7,
    k0V68 = 0x8,
    k0V75 = 0x9,
    k0V94 = 0xA,
    k1V12 = 0xB,
    k1V30 = 0xC,
    k1V50 = 0xD,
    k1V70 = 0xE,
    k1V88 = 0xF
};

enum CSA_GAIN { // Current sense amplifier gain.
    k5V = 0x0,
    k10V = 0x1,
    k20V = 0x2,
    k40V = 0x4
};

enum SEN_LVL {
    k0V25_OCP = 0x0,
    k0V5_OCP = 0x1,
    k0V75_OCP = 0x2,
    k1V0_OCP = 0x3,
};

typedef struct {
   SPI_HandleTypeDef *spiHandler;
   GPIO_TypeDef *csPinBank;
   uint16_t csPin;
   union {
       uint8_t txBuf[2];
       uint16_t tx_control_word;
   };
   union {
       uint8_t rxBuf[2];
       uint16_t rx_control_word;
   };
} DRV8323;

uint8_t DRV_Init(DRV8323 *drv, SPI_HandleTypeDef *spiHandler, GPIO_TypeDef *csPinBank, uint16_t csPin);
uint16_t DRV_WriteSPI(DRV8323 *drv, uint16_t value);
uint16_t DRV_ReadRegister(DRV8323 *drv, uint8_t regAddr);
void DRV_WriteRegister(DRV8323 *drv, uint8_t regAddr, uint16_t value);
void DRV_WriteDCR(DRV8323 *drv,
                  int DIS_CPUV,
                  int DIS_GDF,
                  int ODW_REP,
                  int PWM_MODE,
                  int PWM_COM,
                  int PWM_DIR,
                  int COAST,
                  int BREAK,
                  int CLR_FLT);
FAULT_STATUS_ONE DRV_ReadFaultStatusOne(DRV8323 *drv);
FAULT_STATUS_TWO DRV_ReadFaultStatusTwo(DRV8323 *drv);



#endif //STM32_H7_DRV8323_H
