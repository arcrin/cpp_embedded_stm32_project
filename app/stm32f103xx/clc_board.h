#include "stm32f103xx.h"

using namespace stm32f103;

char usartRxBuffer[100];

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
    
GPIOPinConfig ledRelay1PinConfig(
    GPIOPinNumber::PIN8,
    GPIOPinMode::OUTPUT_10MHZ,
    GPIOPinIOConfig::OUTPUT_PP
);

GPIOHandle ledRelay1GPIOHandle(GPIOE, ledRelay1PinConfig);


GPIOPinConfig swRelay1PinConfig(
    GPIOPinNumber::PIN8,
    GPIOPinMode::INPUT_FT,
    GPIOPinIOConfig::INPUT_PUPD
);

GPIOHandle swRelay1GPIOHandle(GPIOC, swRelay1PinConfig);

GPIOPinConfig usart3TxPinConfig(
    GPIOPinNumber::PIN10,
    GPIOPinMode::OUTPUT_2MHZ,
    GPIOPinIOConfig::AF_PP
);

GPIOHandle usart3TxGPIOHandle(GPIOB, usart3TxPinConfig);

GPIOPinConfig usart3RxPinConfig(
    GPIOPinNumber::PIN11,
    GPIOPinMode::INPUT,
    GPIOPinIOConfig::FLOAT
);

GPIOHandle usart3RxGPIOHandle(GPIOB, usart3RxPinConfig);

USARTConfig usart3Config(
    USARTMode::TX_RX,
    USARTBaud::BAUD_9600,
    USARTStopBits::ONE,
    USARTWordLength::EIGHT_BITS,
    USARTParity::NONE,
    USARTFlowControl::NONE
);

USARTHandle usart3Handle(USART3, usart3Config);


extern "C" {
    void EXTI9_5_IRQHandler() {
        if (EXTI->PR & (1 << 8)) {
            ledRelay1GPIOHandle.toggleOutputPin();
            delayInMs(200);
            EXTI->PR = EXTI->PR | (1 << 8);
        }
    }
} 

extern "C" {
    void USART3_IRQHandler(void) {
        usart3Handle.irqHandler();
    }
}

void USARTHandle::applicationEventCallback(USARTAppStatus appStatus) {
    usart3Handle.sendData((uint8_t*)usartRxBuffer, sizeof(usartRxBuffer));
}