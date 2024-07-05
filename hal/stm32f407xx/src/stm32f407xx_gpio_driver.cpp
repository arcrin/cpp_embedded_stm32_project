#include "stm32f407xx_gpio_driver.h"

using namespace stm32f407;

/**
 * @brief Controls the peripheral clock for a GPIO port.
 * 
 * This function enables or disables the peripheral clock for a GPIO port.
 * 
 * @param status The status of the clock, either ENABLE or DISABLE.
 * 
 * @note This function modifies the AHB1ENR register of the RCC peripheral.
 */

inline void GPIOHandle::periClockControl(ClockStatus status) {
    if (status == ClockStatus::ENABLE) {
        if (m_pGPIOx == GPIOA) {
            enableGPIOAClock();
        } else if (m_pGPIOx == GPIOB) {
            enableGPIOBClock();
        } else if (m_pGPIOx == GPIOC) {
            enableGPIOCClock();
        } else if (m_pGPIOx == GPIOD) {
            enableGPIODClock();
        } else if (m_pGPIOx == GPIOE) {
            enableGPIOEClock();
        } else if (m_pGPIOx == GPIOF) {
            enableGPIOFClock();
        } else if (m_pGPIOx == GPIOG) {
            enableGPIOAClock();
        } else if (m_pGPIOx == GPIOH) {
            enableGPIOHClock();
        } else if (m_pGPIOx == GPIOI) {
            enableGPIOIClock();
        }
    } 
    else if (status == ClockStatus::DISABLE) {
        if (m_pGPIOx == GPIOA) {
            disableGPIOAClock();
        } else if (m_pGPIOx == GPIOB) {
            disableGPIOAClock();
        } else if (m_pGPIOx == GPIOC) {
            disableGPIOCClock();
        } else if (m_pGPIOx == GPIOD) {
            disableGPIODClock();
        } else if (m_pGPIOx == GPIOE) {
            disableGPIOEClock();
        } else if (m_pGPIOx == GPIOF) {
            disableGPIOFClock();
        } else if (m_pGPIOx == GPIOG) {
            disableGPIOAClock();
        } else if (m_pGPIOx == GPIOH) {
            disableGPIOHClock();
        } else if (m_pGPIOx == GPIOI) {
            disableGPIOAClock();
        }
    }
}


/**
 * @brief Initializes the GPIO pin according to the configuration settings.
 * 
 * This function enables the clock for the GPIO port, configures the pin mode, speed, pull-up/pull-down settings,
 * output type, and alternate function (if applicable).
 * 
 * @note For interrupt mode, this function does not configure the interrupt settings.
 */
void GPIOHandle::init() {
    // Enable clock
    periClockControl(ClockStatus::ENABLE);
    
    // 1. Configure the mode of GPIO pin
    if (m_pinConfig.m_pinMode <= GPIOPinMode::ANALOG) {
        // non-interrupt mode
        m_pGPIOx->MODER = m_pGPIOx->MODER & ~(0x3 << (static_cast<uint8_t>(static_cast<uint8_t>(m_pinConfig.m_pinNumber)) * 2));
        m_pGPIOx->MODER = m_pGPIOx->MODER | (static_cast<uint8_t>(m_pinConfig.m_pinMode) << (static_cast<uint8_t>(m_pinConfig.m_pinNumber) * 2));
    }
    else {
        if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_RT) {
            // Enable rising edge trigger
            EXTI->RTSR = EXTI->RTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            // Disable falling edge trigger
            EXTI->FTSR = EXTI->FTSR & ~(1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
        } else if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_FT) {
            // Enable falling edge trigger
            EXTI->FTSR = EXTI->FTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            // Disable rising edge trigger
            EXTI->RTSR = EXTI->RTSR & ~(1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
        } else if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_RFT) {
            // Enable both rising and falling edge triggers
            EXTI->RTSR = EXTI->RTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            EXTI->FTSR = EXTI->FTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
        }
        // Route the GPIO port to the EXTI line
        // TODO: need to find a way to check this at compile time
        uint8_t portCode = getGPIOPortCode(m_pGPIOx);
        enableSYSCFGClock();
        SYSCFG->EXTICR[static_cast<uint8_t>(m_pinConfig.m_pinNumber) / 4] = (portCode << ((static_cast<uint8_t>(m_pinConfig.m_pinNumber) % 4) * 4));

        // Enable the EXTI interrupt
        EXTI->IMR = EXTI->IMR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));

    }

    // 2. Configure the speed
    m_pGPIOx->OSPEEDR = m_pGPIOx->OSPEEDR & ~(0x3 << (static_cast<uint8_t>(m_pinConfig.m_pinNumber) * 2)); // clear the bits before setting
    m_pGPIOx->OSPEEDR = m_pGPIOx->OSPEEDR | (static_cast<uint8_t>(m_pinConfig.m_pinSpeed) << (static_cast<uint8_t>(m_pinConfig.m_pinNumber) * 2));

    // 3. Configure the pull-up/pull-down settings
    m_pGPIOx->PUPDR = m_pGPIOx->PUPDR & ~(0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
    m_pGPIOx->PUPDR = m_pGPIOx->PUPDR | ((static_cast<uint8_t>(m_pinConfig.m_pinPuPdControl) << static_cast<uint8_t>(m_pinConfig.m_pinNumber)));

    // 4. Configure the output type
    m_pGPIOx->OTYPER = m_pGPIOx->OTYPER & ~(0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
    m_pGPIOx->OTYPER = m_pGPIOx->OTYPER | ((static_cast<uint8_t>(m_pinConfig.m_pinOPType) << static_cast<uint8_t>(m_pinConfig.m_pinNumber)));

    // 5. Configure the alternate function
    if (m_pinConfig.m_pinMode == GPIOPinMode::ALT){
        uint8_t reg_level = static_cast<uint8_t>(m_pinConfig.m_pinNumber) / 8;
        uint8_t reg_offset = static_cast<uint8_t>(m_pinConfig.m_pinNumber) % 8;
        m_pGPIOx->AFR[reg_level] = m_pGPIOx->AFR[reg_level] & ~(0xF << (reg_offset * 4));
        m_pGPIOx->AFR[reg_level] = m_pGPIOx->AFR[reg_level] | (static_cast<uint8_t>(m_pinConfig.m_pinAltMode) << (reg_offset * 4));
    }

}

/**
 * @brief De-initializes the GPIO peripheral.
 *
 * This function de-initializes the GPIO peripheral by resetting the corresponding GPIO port.
 * The GPIO port is determined based on the value of pGPIOx member variable.
 * 
 * @note This function should be called before reconfiguring the GPIO peripheral.
 */
void GPIOHandle::deInit() {
    if (m_pGPIOx == GPIOA){
        resetGPIOA();
    } else if (m_pGPIOx == GPIOB){
        resetGPIOB();
    } else if (m_pGPIOx == GPIOC){
        resetGPIOC();
    } else if (m_pGPIOx == GPIOD){
        resetGPIOD();
    } else if (m_pGPIOx == GPIOE){
        resetGPIOE();
    } else if (m_pGPIOx == GPIOF){
        resetGPIOF();
    } else if (m_pGPIOx == GPIOG){
        resetGPIOG();
    } else if (m_pGPIOx == GPIOH){
        resetGPIOH();
    } else if (m_pGPIOx == GPIOI){
        resetGPIOI();
    }
}

/**
 * @brief Reads the value from an input pin.
 *
 * This function reads the value from the input pin associated with the GPIO handle.
 *
 * @return The value read from the input pin.
 */
uint8_t GPIOHandle::readFromInputPin(GPIORegDef* pGPIOx, GPIOPinNumber pinNumber) {
    return (pGPIOx->IDR & (1 << static_cast<uint8_t>(pinNumber)) >> static_cast<uint8_t>(pinNumber));
}

/**
 * @brief Reads the input data from the GPIO port.
 *
 * This function reads the input data from the GPIO port associated with the GPIO handle.
 *
 * @return The input data read from the GPIO port.
 */
uint16_t GPIOHandle::readFromInputPort(GPIORegDef* pGPIOx) {
    return (uint16_t) pGPIOx->IDR;
}

/**
 * @brief Writes the specified pin state to the output pin.
 * 
 * This function sets or clears the specified pin based on the given pin state.
 * 
 * @param pinState The state to be written to the pin.
 * 
 * @return None.
 */
void GPIOHandle::writeToOutputPin(GPIORegDef* pGPIOx, GPIOPinNumber pinNumber, GPIOPinState pinState) {
    if (pinState == GPIOPinState::CLEAR) {
        pGPIOx->ODR = pGPIOx->ODR & ~(0x1 << static_cast<uint8_t>(pinNumber));
    } else {
        pGPIOx->ODR = pGPIOx->ODR | (0x1 << static_cast<uint8_t>(pinNumber));
    }
}

/**
 * @brief Writes the given value to the output data register of the GPIO port.
 *
 * This function sets the output data register (ODR) of the GPIO port associated with the GPIO handle
 * to the given value. The ODR determines the logic levels of the GPIO pins configured as output.
 *
 * @param value The value to be written to the output data register.
 */
void GPIOHandle::writeOutputPort(GPIORegDef* pGPIOx, uint16_t value) {
    pGPIOx->ODR = value;
}

/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * This function toggles the output state of the GPIO pin associated with the GPIO_Handle object.
 * It uses the XOR operator to toggle the specific pin in the ODR (Output Data Register) of the GPIO port.
 *
 * @note This function assumes that the GPIO pin is configured as an output pin.
 *
 * @return None.
 */
void GPIOHandle::toggleOutputPin(GPIORegDef* pGPIOx, GPIOPinNumber pinNumber) {
    pGPIOx->ODR = pGPIOx->ODR ^ (0x1 << static_cast<uint8_t>(pinNumber));
}
