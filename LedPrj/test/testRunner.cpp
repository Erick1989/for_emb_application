#include <iostream>
#include <gtest/gtest.h>
#include "LedDriver.hpp"

TEST(LedInit, Led_Is_Created)
{
    auto my_led=led(3,4);
    ASSERT_EQ(1, 1);
}

TEST(LedInit, LedInit_EN_RCC_FOR_PORTA)
{
    extern uint32_t v_pRccAhb1enr;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pRccAhb1enr=0;
    my_led.init();
    ASSERT_EQ(v_pRccAhb1enr, 1);
}

TEST(LedInit, LedInit_EN_RCC_FOR_PORTA_RCC_NOT_0)
{
    extern uint32_t v_pRccAhb1enr;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pRccAhb1enr=10;
    my_led.init();
    ASSERT_EQ(v_pRccAhb1enr, 11);
}

TEST(LedInit, LedInit_EN_RCC_FOR_PORTB)
{
    extern uint32_t v_pRccAhb1enr;
    const uint16_t PORT_B = 1;
    auto my_led=led(PORT_B,4);
    v_pRccAhb1enr=0;
    my_led.init();
    ASSERT_EQ(v_pRccAhb1enr, 2);
}

TEST(LedInit, LedInit_EN_RCC_FOR_PORTK)
{
    extern uint32_t v_pRccAhb1enr;
    const uint16_t PORT_K = 10;
    auto my_led=led(PORT_K,1);
    v_pRccAhb1enr=0;
    my_led.init();
    ASSERT_EQ(v_pRccAhb1enr, 1024);
}

TEST(LedInit, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA)
{
    extern uint32_t v_pGpiodModeReg;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pGpiodModeReg=0;
    my_led.init();
    ASSERT_EQ(v_pGpiodModeReg, 1);
}

TEST(LedInit, LedInit_SETS_GPIOMODER_OUT_FOR_PORTB)
{
    extern uint32_t v_pGpiodModeReg;
    const uint16_t PORT_B = 1;
    auto my_led=led(PORT_B,4);
    v_pGpiodModeReg=0;
    my_led.init();
    ASSERT_EQ(v_pGpiodModeReg, 4);
}

TEST(LedInit, LedInit_SETS_GPIOMODER_OUT_FOR_PORTK)
{
    extern uint32_t v_pGpiodModeReg;
    const uint16_t PORT_K = 10;
    auto my_led=led(PORT_K,4);
    v_pGpiodModeReg=0;
    my_led.init();
    ASSERT_EQ(v_pGpiodModeReg, 1048576);
}

TEST(LedInit, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA_MODER_18)
{
    extern uint32_t v_pGpiodModeReg;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pGpiodModeReg=18;
    my_led.init();
    ASSERT_EQ(v_pGpiodModeReg, 17);
}

TEST(LedInit, LedInit_SETS_GPIOMODER_OUT_FOR_PORTA_MODER_49)
{
    extern uint32_t v_pGpiodModeReg;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pGpiodModeReg=48;
    my_led.init();
    ASSERT_EQ(v_pGpiodModeReg, 49);
}

TEST(LedInit, LedInit_SETS_ODR_FOR_PORTA)
{
    extern uint32_t v_pGpioOdrReg;
    const uint16_t PORT_A = 0;
    auto my_led=led(PORT_A,4);
    v_pGpioOdrReg=0;
    my_led.init();
    ASSERT_EQ(v_pGpioOdrReg, 1);
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}