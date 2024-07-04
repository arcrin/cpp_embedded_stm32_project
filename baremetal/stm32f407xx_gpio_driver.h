#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

namespace stm32f407 {

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

    enum class GPIOPinMode : uint8_t {
        INPUT = 0,
        OUTPUT,
        ALT,
        ANALOG,
        INPUT_FT,
        INPUT_RT,
        INPUT_RFT
    };
    
    enum class GPIOPinOutputType : uint8_t {
        PUSH_PULL,
        OPEN_DRAIN
    };

    enum class GPIOPinSpeed : uint8_t{
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };

    enum class GPIOPinPuPdControl : uint8_t {
        NO_PUPD,
        PULL_UP,
        PULL_DOWN
    };

    enum class GPIOPinAltMode : uint8_t {
        ALT0,
        ALT1,
        ALT2,
        ALT3,
        ALT4,
        ALT5,
        ALT6,
        ALT7,
        ALT8,
        ALT9,
        ALT10,
        ALT11,
        ALT12,
        ALT13,
        ALT14,
        ALT15
    };

    enum class GPIOPinState : uint8_t {
        CLEAR = 0,
        SET
    };
    
    // Forward declaration of GPIO register definition structure
    struct GPIORegDef;

    class GPIOPinConfig {
        public:
            volatile GPIOPinNumber m_pinNumber;
            volatile GPIOPinMode m_pinMode;
            volatile GPIOPinSpeed m_pinSpeed;
            volatile GPIOPinPuPdControl m_pinPuPdControl;
            volatile GPIOPinOutputType m_pinOPType;
            volatile GPIOPinAltMode m_pinAltMode;

            GPIOPinConfig(
                GPIOPinNumber pinNumber,
                GPIOPinMode pinMode, 
                GPIOPinSpeed pinSpeed,
                GPIOPinPuPdControl pupdControl,
                GPIOPinOutputType opType,
                GPIOPinAltMode altMode
            ): m_pinNumber(pinNumber), 
               m_pinMode(pinMode), 
               m_pinSpeed(pinSpeed), 
               m_pinPuPdControl(pupdControl), 
               m_pinOPType(opType), 
               m_pinAltMode(altMode) {}
    };

    class GPIOHandle {
        private:
            GPIORegDef* m_pGPIOx;
            GPIOPinConfig m_pinConfig;

        public:
            GPIOHandle(GPIORegDef* gpioRegDef, const GPIOPinConfig& pinConfig): 
                m_pGPIOx(gpioRegDef), m_pinConfig(pinConfig) {};
            
            void init();
            void deInit();
            
            void periClockControl(ClockStatus status);

            uint8_t readFromInputPin();
            uint16_t readFromInputPort();
            void writeToOutputPin(GPIOPinState pinState);
            void writeOutputPort(uint16_t value);
            void toggleOutputPin();

            static void irqConfig(uint8_t IRQNumber, bool enable);
            static void irqPriorityConfig(uint8_t IRQNumber, uint8_t priority);
            static void irqHandling(uint8_t pinNumber);
    };
}

#endif