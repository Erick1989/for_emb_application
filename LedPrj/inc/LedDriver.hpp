#pragma once

#include <stdint.h>

class led{
    public:
    led(uint32_t port,uint32_t pos) ;
    void init() const;
    //on()  ;
    //off()  ;
    //toggle();
    private:
    uint32_t port;
    uint32_t pos;
};