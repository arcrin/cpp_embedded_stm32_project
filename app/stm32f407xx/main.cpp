//
// Created by andy- on 2021-10-26.
//

#include "stm32f407xx.h"
#include "stm_discovery_board.h"
#include <cstring>

char msg_buffer[1024] = "UART Tx testing...\n\r";

int main() {
    disable_irq();
    RCCUtil::RCCSetClockSource(RCCClockSource::HSI);
    nvicSetPriority(NVICIRQNumbers::SysTick, 0); // Set priority group to 0

    SysTickInit(16000);
    ledHandleInit();
    buttonHandleInit();
    usart2Init();


    enable_irq();

    while(1) {
        delay_ms(1000);
        // ledHandle.toggleOutputPin();
        usart2Handle.sendData((uint8_t*)msg_buffer, strlen(msg_buffer));
    }
}



