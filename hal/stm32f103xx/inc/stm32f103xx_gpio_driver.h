#pragma once

#include "stm32f103xx.h"

namespace stm32f103 {
    enum class GPIOPinNumber : uint8_t {
        PIN0,
        PIN1,
        PIN2,
        PIN3,
        PIN4,
        PIN5,
        PIN6,
        PIN7,
        PIN8,
        PIN9,
        PIN10,
        PIN11,
        PIN12,
        PIN13,
        PIN14,
        PIN15
    };

    enum class GPIOPinState : uint8_t {
        CLEAR,
        SET,
    };

    enum class GPIOPinIOConfig : uint8_t {
        ANALOG,
        FLOAT,
        INPUT_PUPD,
        OUTPUT_PP,
        OUTPUT_OD,
        AF_PP,
        AF_OD
    };

    enum class GPIOPinMode : uint8_t {
        INPUT,
        OUTPUT_10MHZ,
        OUTPUT_2MHZ,
        OUTPUT_50MHZ,
        INPUT_RT,
        INPUT_FT,
        INPUT_RFT
    };
    
    class GPIOPinConfig {
        public:
            volatile GPIOPinNumber m_pinNumber;
            volatile GPIOPinMode m_pinMode;
            volatile GPIOPinIOConfig m_pinIOConfig;

            GPIOPinConfig() = default;
            GPIOPinConfig(
                GPIOPinNumber pinNumber,
                GPIOPinMode pinMode,
                GPIOPinIOConfig pinIOConfig
            ) : m_pinNumber(pinNumber), 
                m_pinMode(pinMode), 
                m_pinIOConfig(pinIOConfig) {}
            
    };

    class GPIOHandle {
        private:
            GPIORegDef* m_pGPIOx;
            GPIOPinConfig m_pinConfig;

        public:
            GPIOHandle() = default;
            GPIOHandle(GPIORegDef* gpioRegDef, const GPIOPinConfig& pinConfig) :
                m_pGPIOx(gpioRegDef), m_pinConfig(pinConfig) {};

            void periClockControl(ClockStatus status); 

            void init();
            void deInit();

            uint8_t readFromInputPin();
            uint16_t readFromInputPort();
            void writeToOutputPin(GPIOPinState pinState);
            void writeOutputPort(uint16_t value);
            void toggleOutputPin();
    };
}
