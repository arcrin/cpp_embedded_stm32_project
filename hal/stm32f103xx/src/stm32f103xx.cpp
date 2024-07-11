#include "stm32f103xx.h"

namespace stm32f103 {
    volatile uint32_t g_sysTickCounter = 0;

    void SysTickInit(uint32_t load_value) {
        SysTick->CTRL = 0UL;
        SysTick->LOAD = load_value - 1;
        SysTick->VAL = 0UL;
        SysTick->CTRL = 7UL;
    }

    uint32_t getTicks() {
        return g_sysTickCounter;
    }

    void delayInMs(uint32_t delay_ms) {
        uint32_t start_tick = getTicks();
        uint32_t wait = delay_ms;
        while ((getTicks() - start_tick) < wait);
    }
}

extern "C" {
    void SysTick_Handler() {
        stm32f103::g_sysTickCounter = stm32f103::g_sysTickCounter + 1;
    }
}