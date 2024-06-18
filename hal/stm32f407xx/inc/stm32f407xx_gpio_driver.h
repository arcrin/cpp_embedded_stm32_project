#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

namespace STM32F407 {

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

    enum class GPIOPinMode {
        INPUT = 0,
        OUTPUT,
        ALT,
        ANALOG,
        INPUT_FT,
        INPUT_RT,
        INPUT_RFT
    };
    
    enum class GPIOPinOutputType {
        PUSH_PULL,
        OPEN_DRAIN
    };

    enum class GPIOPinSpeed {
        LOW,
        MEDIUM,
        HIGH,
        VERY_HIGH
    };

    enum class GPIOPinPuPdControl {
        NO_PUPD,
        PULL_UP,
        PULL_DOWN
    };
    
    // Forward declaration of GPIO register definition structure
    struct GPIO_RegDef_t;

    class GPIO_PinConfig {
        public:
            volatile GPIOPinNumber PinNumber;
            volatile GPIOPinMode PinMode;
            volatile GPIOPinSpeed PinSpeed;
            volatile GPIOPinPuPdControl PinPuPdControl;
            volatile GPIOPinOutputType PinOPType;
            volatile uint8_t PinAltFunMode;

            GPIO_PinConfig(
                GPIOPinNumber pinNumber,
                GPIOPinMode pinMode, 
                GPIOPinSpeed pinSpeed,
                GPIOPinPuPdControl pupdControl,
                GPIOPinOutputType opType,
                uint8_t altFunctionMode
            ): PinNumber(pinNumber), 
               PinMode(pinMode), 
               PinSpeed(pinSpeed), 
               PinPuPdControl(pupdControl), 
               PinOPType(opType), 
               PinAltFunMode(altFunctionMode) {}
    };

    class GPIO_Handle {
        private:
            GPIO_RegDef_t* pGPIOx;
            GPIO_PinConfig PinConfig;

        public:
            GPIO_Handle(GPIO_RegDef_t* gpioRegDef, const GPIO_PinConfig& pinConfig): 
                pGPIOx(gpioRegDef), PinConfig(pinConfig) {};
            
            void init();
            void deInit();
            
            void periClockControl(ClockStatus status);

            uint8_t readFromInputPin();
            uint16_t readFromInputPort();
            void writeToOutputPin(GPIOPinNumber pinNumber, uint8_t value);
            void writeOutputPort(uint16_t value);
            void toggleOutputPin(GPIOPinNumber pinNumber);

            static void irqConfig(uint8_t IRQNumber, bool enable);
            static void irqPriorityConfig(uint8_t IRQNumber, uint8_t priority);
            static void irqHandling(uint8_t pinNumber);
    };
}

#endif