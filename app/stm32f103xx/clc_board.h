#include "stm32f103xx.h"

using namespace stm32f103;

void delay() {
    for(uint32_t i = 0; i < 5000; i++);
}

GPIOHandle ledRedGPIOHandle;    
GPIOHandle ledGreenGPIOHandle;
GPIOHandle ledRelay1GPIOHandle;
GPIOHandle swRelay1GPIOHandle;

void ledRedInit() {
    GPIOPinConfig ledRedPinConfig(
        GPIOPinNumber::PIN0,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    );

    ledRedGPIOHandle = GPIOHandle(GPIOE, ledRedPinConfig);
    ledRedGPIOHandle.init();
}

void ledGreenInit() {
    GPIOPinConfig ledGreenPinConfig(
        GPIOPinNumber::PIN1,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    );

    ledGreenGPIOHandle = GPIOHandle(GPIOE, ledGreenPinConfig);
    ledGreenGPIOHandle.init();
    
}

void ledRelay1Init() {
    GPIOPinConfig ledRelay1PinConfig(
        GPIOPinNumber::PIN8,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    );

    ledRelay1GPIOHandle = GPIOHandle(GPIOE, ledRelay1PinConfig);
    ledRelay1GPIOHandle.init();
}

void swRelay1Init() {
    GPIOPinConfig swRelay1PinConfig(
        GPIOPinNumber::PIN8,
        GPIOPinMode::INPUT_FT,
        GPIOPinIOConfig::INPUT_PUPD
    );

    swRelay1GPIOHandle = GPIOHandle(GPIOC, swRelay1PinConfig);
    swRelay1GPIOHandle.init();
    nvicSetPriority(NVICIRQNumbers::EXTI9_5, 15);
    nvicEnableIRQ(NVICIRQNumbers::EXTI9_5);
}


extern "C" void EXTI9_5_IRQHandler() {
    if (EXTI->PR & (1 << 8)) {
        EXTI->PR = EXTI->PR | (1 << 8);
        delay();
        ledRelay1GPIOHandle.toggleOutputPin();
    }
}