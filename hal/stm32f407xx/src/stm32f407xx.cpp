#include "stm32f407xx.h"

namespace stm32f407{
    volatile uint32_t g_sysTickCounter = 0;

    void SysTickInit(uint32_t load_value) {
        SysTick->CTRL = 0UL;
        SysTick->LOAD = load_value;
        SysTick->VAL = 0UL;
        SysTick->CTRL = 7UL;
    }   

    uint32_t get_ticks(){
        return g_sysTickCounter;
    }

    void delay(uint32_t delay_ms) {
        uint32_t start_tick = get_ticks();
        uint32_t wait = delay_ms;
        while ((get_ticks() - start_tick) < wait);
    }

    extern "C" {
        void SysTick_Handler() {
            g_sysTickCounter = g_sysTickCounter + 1;
        }
    }  
}

