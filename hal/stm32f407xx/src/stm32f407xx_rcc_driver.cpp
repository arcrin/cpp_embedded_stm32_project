#include "stm32f407xx_rcc_driver.h"

using namespace stm32f407;

uint16_t AHB_PRE_SCALER[8] = {2, 4, 8, 16, 64, 128, 256, 512};  
uint16_t APB1_PRE_SCALER[4] = {2, 4, 8, 16};

uint32_t RCCUtil::RCCGetPLLOutputClock() {
    return 0;
}

void RCCUtil::RCCSetClockSource(RCCClockSource clockSource) {
    if (clockSource == RCCClockSource::HSI) {
        RCC->CFGR = RCC->CFGR & ~(0x3 << 1);
    }
}

// APB1 clock value
uint32_t RCCUtil::RCCGetPCLK1Value() {
    uint32_t  periphera1Clock, systemClock; 
    uint8_t clockSource, temp, ahbPrescaler, abpPrescaler;
    clockSource = ((RCC->CFGR >> 2) & 0x3);

    if (clockSource == static_cast<uint8_t>(RCCClockSource::HSI)) {
        systemClock = 16000000;
    } else if (clockSource == static_cast<uint8_t>(RCCClockSource::HSE)) {
        systemClock = 8000000;
    } else if (clockSource == static_cast<uint8_t>(RCCClockSource::PLL)) {
        systemClock = RCCGetPLLOutputClock();
    }

    // for AHB 
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8) {
        ahbPrescaler = 1;
    } else {
        ahbPrescaler = AHB_PRE_SCALER[temp - 8];
    }

    // APB1
    temp = ((RCC->CFGR >> 10) & 0x7);   

    if (temp < 4) {
        abpPrescaler = 1;
    } else {
        abpPrescaler = APB1_PRE_SCALER[temp - 4];
    }
    periphera1Clock = (systemClock / ahbPrescaler) / abpPrescaler;   

    return periphera1Clock;
}

// APB2 clock value
uint32_t RCCUtil::RCCGetPCLK2Value() {
    uint32_t systemClock = 0, temp, peripheral2Clock;
    uint8_t clockSource = (RCC->CFGR >> 2) & 0x3;
    uint8_t ahpPrescaler, apb2Prescaler; 

    if (clockSource == static_cast<uint8_t>(RCCClockSource::HSI)) {
        systemClock = 16000000;
    } else if (clockSource == static_cast<uint8_t>(RCCClockSource::HSE)) {
        systemClock = 8000000;
    } 

    temp = (RCC->CFGR >> 4) & 0xF;
    if (temp < 0x08) {
        ahpPrescaler = 1;   
    } else {
        apb2Prescaler = AHB_PRE_SCALER[temp - 8];   
    }

    temp = (RCC->CFGR >> 13) & 0x7;
    if (temp < 0x04) {
        apb2Prescaler = 1; 
    } else {
        apb2Prescaler = APB1_PRE_SCALER[temp - 4];
    }

    peripheral2Clock = (systemClock / ahpPrescaler) / apb2Prescaler;    
    return peripheral2Clock;
        
}

