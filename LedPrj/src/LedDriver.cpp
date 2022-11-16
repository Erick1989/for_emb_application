#include "LedDriver.hpp"
#include "mcal_reg.hpp"
#include <stdint.h>
#include <iostream>

led::led(uint32_t port,uint32_t pos):port(port),pos(pos){
    return;
}

void led::init() const{
    uint32_t * pRccAhb1enr =reinterpret_cast<uint32_t *>(addr_pRccAhb1enr);
    uint32_t * pGpioModeReg =reinterpret_cast<uint32_t *>(addr_pGpiodModeReg);
    uint32_t * pGpioOdrReg =reinterpret_cast<uint32_t *>(addr_pGpioOdrReg);
    
    *pRccAhb1enr|=(1<<port);
    *pGpioModeReg|=(1<<(port*2));
    *pGpioModeReg&=~(1<<(port*2+1));
    *pGpioOdrReg=1;
    return;
}