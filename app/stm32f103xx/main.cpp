#include "stm32f103xx.h"

using namespace stm32f103;

void delay() {
    for(uint32_t i = 0; i < 500000; i++);
}

int main() {
    GPIOPinConfig ledRedPinConfig(
        GPIOPinNumber::PIN0,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    );

    GPIOHandle ledRedGPIOHandle(GPIOE, ledRedPinConfig);

    GPIOPinConfig ledGreenPinConfig(
        GPIOPinNumber::PIN1,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    
    );

    GPIOHandle ledGreenGPIOHandle(GPIOE, ledGreenPinConfig);

    GPIOPinConfig led1PinConfig(
        GPIOPinNumber::PIN8,
        GPIOPinMode::OUTPUT_10MHZ,
        GPIOPinIOConfig::OUTPUT_PP
    );

    GPIOHandle led1GPIOHandle(GPIOE, led1PinConfig);

    ledRedGPIOHandle.init();
    ledGreenGPIOHandle.init();    
    led1GPIOHandle.init();

    ledRedGPIOHandle.writeToOutputPin(GPIOPinState::SET);
    ledGreenGPIOHandle.writeToOutputPin(GPIOPinState::SET);

    while (1)
    {
        delay();
        led1GPIOHandle.toggleOutputPin();
    }
    
}