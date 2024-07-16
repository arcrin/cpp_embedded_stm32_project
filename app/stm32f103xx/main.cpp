#include "stm32f103xx.h"
#include "clc_board.h"
#include <cstring>

using namespace stm32f103;


char msg[] = "USART Tx testing...\n\r";  

int main() {
    disable_irq();
    RCCUtil::RCCSetClockSource(RCCClockSource::HSI);
    SysTickInit(8000);
    nvicSetPriority(NVICIRQNumbers::SysTick, 0);

    ledRedGPIOHandle.init();
    ledGreenGPIOHandle.init();
    ledRelay1GPIOHandle.init();
    
    swRelay1GPIOHandle.init();
    nvicSetPriority(NVICIRQNumbers::EXTI9_5, 15);
    nvicEnableIRQ(NVICIRQNumbers::EXTI9_5);

    usart3TxGPIOHandle.init();
    usart3RxGPIOHandle.init();
    usart3Handle.init();
    nvicEnableIRQ(NVICIRQNumbers::USART3);
    nvicSetPriority(NVICIRQNumbers::USART3, 14);
    usart3Handle.receiveDataWithInterrupt((uint8_t*) usartRxBuffer, 5);
    
    
    ledRedGPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);
    ledGreenGPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);
    ledRelay1GPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);
    enable_irq();

    while (1)
    {
        delayInMs(1000);
        ledRelay1GPIOHandle.toggleOutputPin();
        // usart3Handle.sendData((uint8_t*) msg, (uint32_t)sizeof(msg));
        // while(usart3Handle.receiveDataWithInterrupt((uint8_t*) usartRxBuffer, 5) != USARTLineStatus::Ready);
    }
    
}