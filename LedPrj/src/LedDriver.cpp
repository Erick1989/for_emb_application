#include "RunTimeError.hpp"
#include "LedDriver.hpp"
#include "mcal_reg.hpp"
#include <stdint.h>

extern RuntimeError gErrorLogger;
u_char error_invalid_port[] = "Invalid port value";
u_char error_invalid_pin[] = "Invalid pin value";
u_char file_name[] = __FILE__;

led::led(uint32_t port, uint32_t pin_pos) : port(port), pin_pos(pin_pos)
{
    if(port>MAX_PORT){
        gErrorLogger.log_error(error_invalid_port,file_name,__LINE__);
        return;
    }
    if(pin_pos>MAX_PIN_POS){
        gErrorLogger.log_error(error_invalid_pin,file_name,__LINE__);
        return;
    }
    this->port=port;
    this->pin_pos=pin_pos;
    pGpioBase = reinterpret_cast<uint32_t *>(addr_pGpioBaseReg + port * GPIO_LEN);
    uint32_t *pRccAhb1enr = reinterpret_cast<uint32_t *>(addr_pRccAhb1enr);
    *pRccAhb1enr |= (1 << port);

    *(pGpioBase + MODER_OFFSET) |= (1 << (pin_pos * 2));
    *(pGpioBase + MODER_OFFSET) &= ~(1 << (pin_pos * 2 + 1));
    this->off();
    return;
}

void led::on() const
{
    *(pGpioBase + ODR_OFFSET) |= (1 << (pin_pos));
    return;
}

void led::off() const
{
    *(pGpioBase + ODR_OFFSET) &= ~(1 << (pin_pos));
    return;
}

void led::toggle() const{
    *(pGpioBase + ODR_OFFSET) ^= (1 << (pin_pos));
    return;
}