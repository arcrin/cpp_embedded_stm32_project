//
// Created by andy- on 2021-10-26.
//

#include "stm32f407xx.h"
using namespace stm32f407;
void delay() {
    for(uint32_t i = 0; i < 500000; i++);
}




int main() {
    GPIOPinConfig pinConfig(
        GPIOPinNumber::PIN12,
        GPIOPinMode::OUTPUT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::NO_PUPD,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT0
    );
    GPIOHandle ledGPIOHandle(GPIOD, pinConfig);
    ledGPIOHandle.init();
    while(1) {
        ledGPIOHandle.toggleOutputPin();
        delay();
    }
}