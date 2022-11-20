#pragma once


/*!< AHB1 peripherals */




#define AHB1PERIPH_BASE       (0x40000000UL + 0x00020000UL)
#define addr_pGpioBaseReg     (AHB1PERIPH_BASE)
#define GPIO_LEN              (0x0400UL)

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



#define addr_pRccAhb1enr      (0x40023830)



/*typedef struct
{
  __IO uint32_t MODER;    
  __IO uint32_t OTYPER;   
  __IO uint32_t OSPEEDR;  
  __IO uint32_t PUPDR;    
  __IO uint32_t IDR;      
  __IO uint32_t ODR;      
  __IO uint32_t BSRR;     
  __IO uint32_t LCKR;     
  __IO uint32_t AFR[2];   
} GPIO_TypeDef;
*/