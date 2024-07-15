#pragma once
#include "stm32f103xx.h"

namespace stm32f103 {
    enum class RCCClockSource : uint8_t {
        HSI,
        HSE,
        PLL
    };

    class RCCUtil {
        public:
            static void RCCSetClockSource(RCCClockSource clockSource);

            static uint32_t RCCGetPCLK1Value();

            static uint32_t RCCGetPCLK2Value();

            static uint32_t RCCGetPLLOutputClock(); 
    };
}