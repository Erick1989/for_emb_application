#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RunTimeError.hpp"
#include "LedDriver.hpp"

const uint16_t PORT_A = 0;
const uint16_t PORT_B = 1;
const uint16_t PORT_K = 10;
const uint16_t PORT_INVALID = 0xFF;

const uint32_t GPIO_LEN = 0x0400UL;
const uint16_t ODR_OFFSET = 5;

const uint16_t POS_DUMMY = 3;
const uint16_t PIN_POS_0 = 0;
const uint16_t PIN_POS_8 = 8;
const uint16_t PIN_POS_15 = 15;
const uint16_t PIN_POS_INVALID = 0xFF;

extern uint32_t v_pGpioSpace[10240];
extern uint32_t v_pRccAhb1enr;

using ::testing::_;
using ::testing::AtLeast;

int get_bit_val(uint32_t pos, uint32_t val)
{
    uint32_t mask = (1 << pos);
    return (val & mask) >> pos;
}

RuntimeError gErrorLogger;

TEST(Ledctor, LedInit_SETS_RCC_FOR_PORTA_RCC_NOT_0)
{
    v_pRccAhb1enr = 10;
    auto my_led = led(PORT_A, POS_DUMMY);
    ASSERT_EQ(get_bit_val(PORT_A, v_pRccAhb1enr), 1);
}

TEST(Ledctor, LedInit_SETS_RCC_FOR_PORTB)
{
    v_pRccAhb1enr = 0;
    auto my_led = led(PORT_B, POS_DUMMY);
    ASSERT_EQ(get_bit_val(PORT_B, v_pRccAhb1enr), 1);
}

TEST(Ledctor, LedInit_SETS_RCC_FOR_PORTK)
{
    v_pRccAhb1enr = 0;
    auto my_led = led(PORT_K, POS_DUMMY);
    ASSERT_EQ(get_bit_val(PORT_K, v_pRccAhb1enr), 1);
}

TEST(Ledctor, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA_PIN0)
{
    v_pGpioSpace[0] = 0;
    auto my_led = led(PORT_A, PIN_POS_0);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0, v_pGpioSpace[0]), 1);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0 + 1, v_pGpioSpace[0]), 0);
}

TEST(Ledctor, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA_PIN8)
{
    v_pGpioSpace[0] = 0;
    auto my_led = led(PORT_A, PIN_POS_8);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_8, v_pGpioSpace[0]), 1);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_8 + 1, v_pGpioSpace[0]), 0);
}

TEST(Ledctor, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA_PIN15)
{
    v_pGpioSpace[0] = 0;
    auto my_led = led(PORT_A, PIN_POS_15);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_15, v_pGpioSpace[0]), 1);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_15 + 1, v_pGpioSpace[0]), 0);
}

TEST(Ledctor, LedInit_SETS_GPIOMODER_OUT_FOR_PORTB_PIN0)
{
    v_pGpioSpace[PORT_B * GPIO_LEN] = 0;
    auto my_led = led(PORT_B, PIN_POS_0);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0, v_pGpioSpace[PORT_B * GPIO_LEN]), 1);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0 + 1, v_pGpioSpace[PORT_B * GPIO_LEN]), 0);
}

TEST(Ledctor, LedInit_SETS_GPIOMODER_OUT_FOR_PORTK_PIN0)
{
    v_pGpioSpace[PORT_K * GPIO_LEN] = 0;
    auto my_led = led(PORT_K, PIN_POS_0);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0, v_pGpioSpace[PORT_K * GPIO_LEN]), 1);
    ASSERT_EQ(get_bit_val(2 * PIN_POS_0 + 1, v_pGpioSpace[PORT_K * GPIO_LEN]), 0);
}

TEST(Ledctor, LedInit_CLEARS_ODR_FOR_PORTA_PIN0)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_A, PIN_POS_0);
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Ledctor, LedInit_CLEARS_ODR_FOR_PORTA_PIN8)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    auto my_led = led(PORT_A, PIN_POS_8);
    ASSERT_EQ(get_bit_val(PIN_POS_8, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Ledctor, LedInit_CLEARS_ODR_FOR_PORTA_PIN15)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    auto my_led = led(PORT_A, PIN_POS_15);
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Ledctor_Invalid, Ledctor_Logs_Error_On_Invalid_PORT)
{
    gErrorLogger.num_errors = 0;
    auto my_led = led(PORT_INVALID, PIN_POS_0);
    ASSERT_EQ(gErrorLogger.num_errors, 1);
}

TEST(Ledctor_Invalid, Ledctor_Logs_Error_On_Invalid_PIN)
{
    gErrorLogger.num_errors = 0;
    auto my_led = led(PORT_A, PIN_POS_INVALID);
    ASSERT_EQ(gErrorLogger.num_errors, 1);
}

TEST(Ledctor, LedInit_SETS_RCC_FOR_PORTA)
{
    v_pRccAhb1enr = 0;
    auto my_led = led(PORT_A, POS_DUMMY);
    ASSERT_EQ(get_bit_val(0, v_pRccAhb1enr), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTA_PIN0)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_A, PIN_POS_0);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTA_PIN8)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_A, PIN_POS_8);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_8, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTA_PIN15)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_A, PIN_POS_15);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTB_PIN0)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_B, PIN_POS_0);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_B * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTB_PIN8)
{
    v_pGpioSpace[PORT_B * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_B, PIN_POS_8);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_8, v_pGpioSpace[PORT_B * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_On, Led_On_SET_ODR_FOR_PORTB_PIN15)
{
    v_pGpioSpace[PORT_B * GPIO_LEN + ODR_OFFSET] = 0;
    auto my_led = led(PORT_B, PIN_POS_15);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_B * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_Off, Led_Off_CLEARS_ODR_FOR_PORTA_PIN0)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    auto my_led = led(PORT_A, PIN_POS_0);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
    my_led.off();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Led_Off, Led_Off_CLEARS_ODR_FOR_PORTA_PIN8)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    auto my_led = led(PORT_A, PIN_POS_8);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_8, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
    my_led.off();
    ASSERT_EQ(get_bit_val(PIN_POS_8, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Led_Off, Led_Off_CLEARS_ODR_FOR_PORTA_PIN15)
{
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    auto my_led = led(PORT_A, PIN_POS_15);
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
    my_led.off();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
}

TEST(Led_toggle, Led_Toggle_INVERT_STATE_FOR_ODR_FOR_PORTA_PIN0)
{
    auto my_led = led(PORT_A, PIN_POS_0);
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
    my_led.toggle();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
    my_led.off();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
    my_led.toggle();
    ASSERT_EQ(get_bit_val(PIN_POS_0, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
}

TEST(Led_toggle, Led_Toggle_INVERT_STATE_FOR_ODR_FOR_PORTA_PIN15)
{
    auto my_led = led(PORT_A, PIN_POS_15);
    v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET] = 0xFF;
    my_led.on();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
    my_led.toggle();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
    my_led.off();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 0);
    my_led.toggle();
    ASSERT_EQ(get_bit_val(PIN_POS_15, v_pGpioSpace[PORT_A * GPIO_LEN + ODR_OFFSET]), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}