#include "stm32f103xx.h"
#include "clc_board.h"

using namespace stm32f103;



int main() {
    disable_irq();

    SysTickInit(16000);

    ledRedInit();
    ledGreenInit(); 
    ledRelay1Init();
    swRelay1Init();
    
    ledRedGPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);
    ledGreenGPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);
    ledRelay1GPIOHandle.writeToOutputPin(GPIOPinState::CLEAR);

    nvicSetPriority(NVICIRQNumbers::SysTick, 1);

    enable_irq();

    while (1)
    {
        delayInMs(1000);
        // ledRelay1GPIOHandle.toggleOutputPin();
    }
    
}