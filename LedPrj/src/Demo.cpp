
#include "LedDriver.hpp"
#include "RunTimeError.hpp"

const uint16_t PORT_A = 0;
const uint16_t PORT_B = 1;
const uint16_t PORT_C = 2;
const uint16_t PORT_D = 3;
const uint16_t PORT_K = 10;
const uint16_t POS_DUMMY = 3;
const uint16_t PIN_POS_1 = 0;
const uint16_t PIN_POS_12 = 12;
const uint16_t PIN_POS_13 = 13;
const uint16_t PIN_POS_14 = 14;
const uint16_t PIN_POS_15 = 15;

#define LED_GREEN  12
#define LED_ORANGE 13
#define LED_RED    14
#define LED_BLUE   15

RuntimeError gErrorLogger;

int main(){
    auto led_green = led(PORT_D, PIN_POS_12);
    auto led_orange = led(PORT_D, PIN_POS_13);
    auto led_red = led(PORT_D, PIN_POS_14);
    auto led_blue = led(PORT_D, PIN_POS_15);
    led_green.on();
    led_orange.on();
    led_red.on();
    led_blue.on();
}