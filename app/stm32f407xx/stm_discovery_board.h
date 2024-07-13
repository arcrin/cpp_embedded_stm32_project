#pragma once
#include "stm32f407xx.h"
using namespace stm32f407;


char usartRxBuffer[100];


GPIOPinConfig ledPinConfig(
    GPIOPinNumber::PIN12,
    GPIOPinMode::OUTPUT,
    GPIOPinSpeed::HIGH,
    GPIOPinPuPdControl::NO_PUPD,
    GPIOPinOutputType::PUSH_PULL,
    GPIOPinAltMode::ALT0
);

GPIOHandle ledHandle(GPIOD, ledPinConfig);



GPIOPinConfig buttonPinConfig(
    GPIOPinNumber::PIN0,
    GPIOPinMode::INPUT_FT,
    GPIOPinSpeed::HIGH,
    GPIOPinPuPdControl::NO_PUPD,
    GPIOPinOutputType::PUSH_PULL,
    GPIOPinAltMode::ALT0
);

GPIOHandle buttonHandle(GPIOA, buttonPinConfig);


GPIOPinConfig usartTxPinConfig(
    GPIOPinNumber::PIN2,
    GPIOPinMode::ALT,
    GPIOPinSpeed::HIGH,
    GPIOPinPuPdControl::PULL_UP,
    GPIOPinOutputType::PUSH_PULL,
    GPIOPinAltMode::ALT7
);
GPIOHandle usartTxGPIOHandle(GPIOA, usartTxPinConfig);


    GPIOPinConfig usartRxPinConfig(
    GPIOPinNumber::PIN3,
    GPIOPinMode::ALT,
    GPIOPinSpeed::HIGH,
    GPIOPinPuPdControl::PULL_UP,
    GPIOPinOutputType::PUSH_PULL,
    GPIOPinAltMode::ALT7
);
GPIOHandle usartRxGPIOHandle(GPIOA, usartRxPinConfig);


USARTConfig usartConfig(
    USARTMode::RX,
    USARTBaud::BAUD_9600,
    USARTStopBits::ONE,
    USARTWordLength::EIGHT_BITS,
    USARTParity::NONE,
    USARTFlowControl::NONE
);

USARTHandle usart2Handle(USART2, usartConfig);




extern "C" {
    void EXTI0_IRQHandler() {
        if (EXTI->PR & (1 << 0)) {
            EXTI->PR = EXTI->PR | (1 << 0);
            ledHandle.toggleOutputPin();
            delay_ms(400);
        }
    }

    void USART2_IRQHandler(void) {
        usart2Handle.irqHandler();
    }
}

void USARTHandle::applicationEventCallback(USARTAppStatus appStatus) {
    if (appStatus == USARTAppStatus::TX_COMPLETE) {
        
    }
}