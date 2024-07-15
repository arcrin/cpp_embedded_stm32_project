#include "stm32f103xx_rcc_driver.h"

using namespace stm32f103;

uint16_t AHB_PRE_SCALER[8] = {2, 4, 8, 16, 64, 128, 256, 512};  
uint16_t APB_PRE_SCALER[4] = {2, 4, 8, 16};

void RCCUtil::RCCSetClockSource(RCCClockSource clockSource) {
    if (clockSource == RCCClockSource::HSI) {
        RCC->CFGR = RCC->CFGR & ~(0x3);
    }
}   

// APB1 clock value 
uint32_t RCCUtil::RCCGetPCLK1Value() {
    uint32_t peripheral1Clock, systemClock;
    uint8_t clockSource, temp, ahbPrescaler, abpPrescaler;
    clockSource = ((RCC->CFGR >> 2) & 0x3);

    // TODO: Add other clock sources
    if (clockSource == static_cast<uint8_t>(RCCClockSource::HSI)) {
        systemClock = 8000000;
    }

    // AHB bus frequency
    // AHB prescaler
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8) {
        ahbPrescaler = 1;
    } else {
        ahbPrescaler = AHB_PRE_SCALER[temp - 8];
    }

    // APB1 bus frequency
    // APB1 prescaler
    temp = ((RCC->CFGR >> 8) & 0x7);
    if (temp < 4) {
        abpPrescaler = 1;
    } else {
        abpPrescaler = APB_PRE_SCALER[temp - 4];
    }
    peripheral1Clock = (systemClock / ahbPrescaler) / abpPrescaler;
    return peripheral1Clock;
}

uint32_t RCCUtil::RCCGetPCLK2Value() {
    uint32_t peripheralClock, systemClock;
    uint8_t clockSource, temp, ahbPrescaler, abpPrescaler;  
    clockSource = ((RCC->CFGR >> 2) & 0x3);

    // TODO: Add other clock sources
    if (clockSource == static_cast<uint8_t>(RCCClockSource::HSI)) {
        systemClock = 8000000;
    }

    // AHB prescaler
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8) {
        ahbPrescaler = 1;
    } else {
        ahbPrescaler = AHB_PRE_SCALER[temp - 8];
    }

    // APB2 prescaler
    temp = ((RCC->CFGR >> 11) & 0x7);
    if (temp < 4) {
        abpPrescaler = 1;
    } else {
        abpPrescaler = APB_PRE_SCALER[temp - 4];
    }
    peripheralClock = (systemClock / ahbPrescaler) / abpPrescaler;
    return peripheralClock;
}

// TODO: Implement this function
uint32_t RCCUtil::RCCGetPLLOutputClock() {
    return 0;
}