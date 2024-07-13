//
// Created by andy- on 2021-10-26.
//

#include "stm32f407xx.h"
#include <cstring>
#include "stm_discovery_board.h"


int main() {
    disable_irq();
    RCCUtil::RCCSetClockSource(RCCClockSource::HSI);
    nvicSetPriority(NVICIRQNumbers::SysTick, 0); // Set priority group to 0

    SysTickInit(16000);
    
    // NOTE: maybe I could include these nvic initializers inside the GPIOHandle::init() function

    
    ledHandle.init();

    buttonHandle.init();
    nvicSetPriority(NVICIRQNumbers::EXTI0, 15); 
    nvicEnableIRQ(NVICIRQNumbers::EXTI0);

    usartRxGPIOHandle.init();
    usartTxGPIOHandle.init();
    usart2Handle.init();
    nvicEnableIRQ(NVICIRQNumbers::USART2);
    nvicSetPriority(NVICIRQNumbers::USART2, 14);

    enable_irq();

    while(1) {
        delay_ms(200);
        while(usart2Handle.receiveDataWithInterrupt((uint8_t*) usartRxBuffer, 10) != USARTLineStatus::Ready);
    }
}