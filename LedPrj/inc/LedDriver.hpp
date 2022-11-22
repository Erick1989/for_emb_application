#pragma once
#include <stdint.h>

#define MAX_PORT 10
#define MAX_PIN_POS 15

class iled
{
public:
    virtual void on() const=0;
    virtual void off() const=0;
    virtual void toggle() const=0;
    //virtual bool getState() const=0;
};

class led:iled
{
public:
    led(uint32_t port, uint32_t pin_pos);
    void on() const;
    void off() const;
    void toggle() const;
    //bool getState() const;

private:
    volatile uint32_t *pGpioBase = nullptr;
    uint32_t port;
    uint32_t pin_pos;
};