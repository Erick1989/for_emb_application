#pragma once
#include <stdint.h>

uint32_t v_pRccAhb1enr = 0;
#define addr_pRccAhb1enr &v_pRccAhb1enr

uint32_t v_pGpioSpace[10240];
uint32_t * addr_pGpioBaseReg=v_pGpioSpace;
#define GPIO_LEN (0x0400UL)

#define MODER_OFFSET            (0)
#define OTYPER_OFFSET           (1)
#define OSPEEDR_OFFSET          (2)
#define PUPDR_OFFSET            (3)
#define IDR_OFFSET              (4)
#define ODR_OFFSET              (5)
#define BSRR_OFFSET             (6)
#define LCKR_OFFSET             (7)
#define AFR1_OFFSET             (8)
#define AFR2_OFFSET             (9)
