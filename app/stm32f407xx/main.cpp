//
// Created by andy- on 2021-10-26.
//

#include "stm32f407xx.h"
using namespace stm32f407;
void delay() {
    for(uint32_t i = 0; i < 50000; i++);
}



int main() {
    GPIOPinConfig ledPinConfig(
        GPIOPinNumber::PIN12,
        GPIOPinMode::OUTPUT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::NO_PUPD,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT0
    );
    GPIOHandle ledGPIOHandle(GPIOD, ledPinConfig);



    GPIOPinConfig buttonPinConfig(
        GPIOPinNumber::PIN0,
        GPIOPinMode::INPUT_RT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::NO_PUPD,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT0
    );

    GPIOHandle buttonGPIOHandle(GPIOA, buttonPinConfig);

    ledGPIOHandle.init();
    buttonGPIOHandle.init();
    nvicSetPriority(NVICIRQNumbers::EXTI0, 15); 
    nvicEnableIRQ(NVICIRQNumbers::EXTI0);

    while(1) {
        
    }
}


extern "C" {
    void EXTI0_IRQHandler() {
        if (EXTI->PR & (1 << 0)) {
            GPIOHandle::toggleOutputPin(GPIOD, GPIOPinNumber::PIN12);
            EXTI->PR = EXTI->PR | (1 << 0);
            delay();
        }
    }
}