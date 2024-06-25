#ifndef INC_STM32F103XX_GPIO_DRIVER_H_
#define INC_STM32F103XX_GPIO_DRIVER_H_

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
        ANALOG = 0x0,
        FLOAT = 0x1,
        INPUT_PUPD = 0x2,
        OUTPUT_PP = 0x0,
        OUTPUT_OD = 0x1,
        AF_PP = 0x2,
        AF_OD = 0x3
    };

    enum class GPIOPinMode : uint8_t {
        INPUT,
        OUTPUT_10MHZ,
        OUTPUT_2MHZ,
        OUTPUT_50MHZ,
    };
    
    class GPIOPinConfig {
        public:
            volatile GPIOPinNumber m_pinNumber;
            volatile GPIOPinMode m_pinMode;
            volatile GPIOPinIOConfig m_pinIOConfig;

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
            GPIOHandle(GPIORegDef* gpioRegDef, const GPIOPinConfig& pinConfig) :
                m_pGPIOx(gpioRegDef), m_pinConfig(pinConfig) {};

            void init();
            void deInit();

            void periClockControl(ClockStatus status); 

            uint8_t readFromInputPin();
            uint16_t readFromInputPort();
            void writeToOutputPin(GPIOPinState pinState);
            void writeOutputPort(uint16_t value);
            void toggleOutputPin();
    };
}

#endif