#include "stm32f407xx.h"
using namespace stm32f407;


GPIOHandle ledHandle;
GPIOHandle buttonHandle;
GPIOHandle usartTxGPIOHandle;
GPIOHandle usartRxGPIOHandle;
USARTHandle usart2Handle;

void ledHandleInit() {
    GPIOPinConfig ledPinConfig(
        GPIOPinNumber::PIN12,
        GPIOPinMode::OUTPUT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::NO_PUPD,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT0
    );

    ledHandle = GPIOHandle(GPIOD, ledPinConfig);
    ledHandle.init();

}

void buttonHandleInit() {
    GPIOPinConfig buttonPinConfig(
        GPIOPinNumber::PIN0,
        GPIOPinMode::INPUT_FT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::NO_PUPD,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT0
    );

    buttonHandle = GPIOHandle(GPIOA, buttonPinConfig);
    buttonHandle.init();
    nvicSetPriority(NVICIRQNumbers::EXTI0, 15); 
    nvicEnableIRQ(NVICIRQNumbers::EXTI0);
}

void usartGPIOInit() {
    GPIOPinConfig usartTxPinConfig(
        GPIOPinNumber::PIN2,
        GPIOPinMode::ALT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::PULL_UP,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT7
    );
    usartTxGPIOHandle = GPIOHandle(GPIOA, usartTxPinConfig);
    usartTxGPIOHandle.init();


        GPIOPinConfig usartRxPinConfig(
        GPIOPinNumber::PIN3,
        GPIOPinMode::ALT,
        GPIOPinSpeed::HIGH,
        GPIOPinPuPdControl::PULL_UP,
        GPIOPinOutputType::PUSH_PULL,
        GPIOPinAltMode::ALT7
    );
    usartRxGPIOHandle = GPIOHandle(GPIOA, usartRxPinConfig);
    usartRxGPIOHandle.init();
}

void usart2Init() {
    usartGPIOInit();
    USARTConfig usartConfig(
        USARTMode::TX,
        USARTBaud::BAUD_9600,
        USARTStopBits::ONE,
        USARTWordLength::EIGHT_BITS,
        USARTParity::NONE,
        USARTFlowControl::NONE
    );

    usart2Handle = USARTHandle(USART2, usartConfig);
    usart2Handle.init();
    usart2Handle.peripheralControl(true);
    // nvicEnableIRQ(NVICIRQNumbers::USART2);
    // nvicSetPriority(NVICIRQNumbers::USART2, 14);
}


extern "C" {
    void EXTI0_IRQHandler() {
        if (EXTI->PR & (1 << 0)) {
            EXTI->PR = EXTI->PR | (1 << 0);
            ledHandle.toggleOutputPin();
            delay_ms(400);
        }
    }
}
