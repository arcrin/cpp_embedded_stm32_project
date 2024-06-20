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
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 0);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOB) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 1);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOC) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 2);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOD) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 3);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOE) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 4);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOF) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 5);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOG) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 6);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOH) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 7);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOI) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 8);
            RCC->AHB1ENR = temp;
        }
    } 
    else if (status == ClockStatus::DISABLE) {
        if (m_pGPIOx == GPIOA) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 0);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOB) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 1);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOC) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 2);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOD) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 3);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOE) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 4);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOF) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 5);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOG) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 6);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOH) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 7);
            RCC->AHB1ENR = temp;
        } else if (m_pGPIOx == GPIOI) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 8);
            RCC->AHB1ENR = temp;
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
        // interrupt mode (later)
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
uint8_t GPIOHandle::readFromInputPin() {
    return (m_pGPIOx->IDR & (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber)) >> static_cast<uint8_t>(m_pinConfig.m_pinNumber));
}

/**
 * @brief Reads the input data from the GPIO port.
 *
 * This function reads the input data from the GPIO port associated with the GPIO handle.
 *
 * @return The input data read from the GPIO port.
 */
uint16_t GPIOHandle::readFromInputPort() {
    return (uint16_t) m_pGPIOx->IDR;
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
void GPIOHandle::writeToOutputPin(GPIOPinState pinState) {
    if (pinState == GPIOPinState::CLEAR) {
        m_pGPIOx->ODR = m_pGPIOx->ODR & ~(0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
    } else {
        m_pGPIOx->ODR = m_pGPIOx->ODR | (0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
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
void GPIOHandle::writeOutputPort(uint16_t value) {
    m_pGPIOx->ODR = value;
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
void GPIOHandle::toggleOutputPin() {
    m_pGPIOx->ODR = m_pGPIOx->ODR ^ (0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
}