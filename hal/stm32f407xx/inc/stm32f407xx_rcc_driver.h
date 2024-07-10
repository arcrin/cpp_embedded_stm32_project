#pragma once
#include "stm32f407xx.h"

namespace stm32f407 {
    enum class RCCClockSource : uint8_t {
        HSI,
        HSE,
        PLL
    };  

    class RCCUtil {
        public:
            static void RCCSetClockSource(RCCClockSource clockSource);

            // APB1 clock value
            static uint32_t RCCGetPCLK1Value();

            // APB2 clock value
            static uint32_t RCCGetPCLK2Value();

            static uint32_t RCCGetPLLOutputClock();
    };
}