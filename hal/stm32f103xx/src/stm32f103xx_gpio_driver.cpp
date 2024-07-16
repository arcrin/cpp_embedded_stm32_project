#include "stm32f103xx_gpio_driver.h"

using namespace stm32f103;

/**
 * @brief Controls the peripheral clock for the GPIO port.
 * 
 * This function enables or disables the peripheral clock for the GPIO port based on the specified status.
 * 
 * @param status The status of the peripheral clock. It can be either ClockStatus::ENABLE or ClockStatus::DISABLE.
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
            enableGPIOGClock();
        }
    } 
    else if (status == ClockStatus::DISABLE) {
        if (m_pGPIOx == GPIOA) {
            disableGPIOAClock();
        } else if (m_pGPIOx == GPIOB) {
            disableGPIOBClock();
        } else if (m_pGPIOx == GPIOC) {
            disableGPIOCClock();
        } else if (m_pGPIOx == GPIOD) {
            disableGPIODClock();
        } else if (m_pGPIOx == GPIOE) {
            disableGPIOEClock();
        } else if (m_pGPIOx == GPIOF) {
            disableGPIOFClock();
        } else if (m_pGPIOx == GPIOG) {
            disableGPIOGClock();
        }
    }
}


/**
 * @brief Initializes the GPIO pin.
 *
 * This function enables the clock for the GPIO port and configures the mode and IO configuration of the GPIO pin.
 * It calculates the register level, offset, and value based on the pin number, pin IO configuration, and pin mode.
 * It then sets the corresponding bits in the control register to configure the GPIO pin.
 */
void GPIOHandle::init() {
    // Enable clock
    periClockControl(ClockStatus::ENABLE);  

    uint8_t reg_level = static_cast<uint8_t>(m_pinConfig.m_pinNumber) / 8;
    uint8_t reg_offest = static_cast<uint8_t>(m_pinConfig.m_pinNumber) % 8;

    // Configure the mode of the GPIO pin, and its IO configuration
    // There are essentially 2 modes: input and output; each mode has 4 configurations


    if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_FT || 
        m_pinConfig.m_pinMode == GPIOPinMode::INPUT_RT ||
        m_pinConfig.m_pinMode == GPIOPinMode::INPUT_RFT) {
            // For interrupt mode, the pin needs to be in input mode (0x0), configured as input_pupd (0x2) 
            uint8_t reg_value = (static_cast<uint8_t>(GPIOPinIOConfig::INPUT_PUPD) << 2) + static_cast<uint8_t>(GPIOPinMode::INPUT);
            m_pGPIOx->CR[reg_level] = m_pGPIOx->CR[reg_level] & ~(0xF << (reg_offest * 4));  // reest the bits  
            m_pGPIOx->CR[reg_level] = m_pGPIOx->CR[reg_level] | (reg_value << (reg_offest * 4));  // set the bits
            // configure the detection mode (rising of falling edge) in EXTI registers
            if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_RT) {
                EXTI->RTSR = EXTI->RTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
                EXTI->FTSR = EXTI->FTSR & ~(1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            } else if (m_pinConfig.m_pinMode == GPIOPinMode::INPUT_FT) {
                EXTI->FTSR = EXTI->FTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
                EXTI->RTSR = EXTI->RTSR & ~(1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            } else {
                EXTI->RTSR = EXTI->RTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
                EXTI->FTSR = EXTI->FTSR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
            }
            // map the port to the EXTI channel in AFIO registers; and enable AFIO clock
            enebleAFIOClock();
            uint8_t exti_reg_level = static_cast<uint8_t>(m_pinConfig.m_pinNumber) / 4;
            uint8_t exti_reg_offset = static_cast<uint8_t>(m_pinConfig.m_pinNumber) % 4;
            AFIO->EXTICR[exti_reg_level] = AFIO->EXTICR[exti_reg_level] & ~(0xF << (exti_reg_offset * 4));  // reset the bits
            uint8_t port_code = getGPIOPortCode(m_pGPIOx);
            AFIO->EXTICR[exti_reg_level] = (port_code << (exti_reg_offset * 4));  // set the bits

            // enable EXTI interrupt in EXTI->IMR
            EXTI->IMR = EXTI->IMR | (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));


        } else {
            // For regular IO mode, the pin mode and pin config enum can be directly mapped into the CR register
            uint8_t ioConfig = 0x0;

            switch (m_pinConfig.m_pinIOConfig) {
                case GPIOPinIOConfig::ANALOG:
                    ioConfig = 0x0;
                    break;
                case GPIOPinIOConfig::FLOAT:
                    ioConfig = 0x1;
                    break;
                case GPIOPinIOConfig::INPUT_PUPD:
                    ioConfig = 0x2;
                    break;
                case GPIOPinIOConfig::OUTPUT_PP:
                    ioConfig = 0x0;
                    break;
                case GPIOPinIOConfig::OUTPUT_OD:
                    ioConfig = 0x1;
                    break;
                case GPIOPinIOConfig::AF_PP:
                    ioConfig = 0x2;
                    break;
                case GPIOPinIOConfig::AF_OD:
                    ioConfig = 0x3;
                    break;
            }
            
            uint8_t reg_value = (ioConfig << 2) + static_cast<uint8_t>(m_pinConfig.m_pinMode);
            m_pGPIOx->CR[reg_level] = m_pGPIOx->CR[reg_level] & ~(0xF << (reg_offest * 4));  // reest the bits
            m_pGPIOx->CR[reg_level] = m_pGPIOx->CR[reg_level] | (reg_value << (reg_offest * 4));

        }
}

/**
 * @brief Deinitializes the GPIO port.
 *
 * This function deinitializes the GPIO port associated with the GPIOHandle object.
 * It resets the GPIO port to its default state.
 *
 * @note This function should be called before reconfiguring or disabling the GPIO port.
 */
void GPIOHandle::deInit() {
    if (m_pGPIOx == GPIOA) {
        resetGPIOA();
    } else if (m_pGPIOx == GPIOB) {
        resetGPIOB();
    } else if (m_pGPIOx == GPIOC) {
        resetGPIOC();
    } else if (m_pGPIOx == GPIOD) {
        resetGPIOD();
    } else if (m_pGPIOx == GPIOE) {
        resetGPIOE();
    } else if (m_pGPIOx == GPIOF) {
        resetGPIOF();
    } else if (m_pGPIOx == GPIOG) {
        resetGPIOG();
    }
}

/**
 * @brief Reads the input value from a specific GPIO pin.
 *
 * This function reads the input value from the GPIO pin associated with the GPIOHandle object.
 *
 * @return The input value of the GPIO pin (0 or 1).
 */
uint8_t GPIOHandle::readFromInputPin() {
    // watch out for the operator precedence
    return ((m_pGPIOx->IDR & (1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber))) >> static_cast<uint8_t>(m_pinConfig.m_pinNumber));
}

/**
 * @brief Reads the input data from the GPIO port.
 *
 * @return The input data from the GPIO port.
 */
uint16_t GPIOHandle::readFromInputPort() {
    return (uint16_t) m_pGPIOx->IDR;
}

/**
 * @brief Writes the specified pin state to the output pin.
 *
 * This function sets or clears the output pin based on the provided `pinState` parameter.
 *
 * @param pinState The state to be written to the output pin.
 *                 - `GPIOPinState::CLEAR` to clear the pin (set it to low).
 *                 - `GPIOPinState::SET` to set the pin (set it to high).
 */
void GPIOHandle::writeToOutputPin(GPIOPinState pinState) {
    if (pinState == GPIOPinState::CLEAR) {
        // m_pGPIOx->ODR = m_pGPIOx->ODR & ~(0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
        m_pGPIOx->BSRR = m_pGPIOx->BSRR | (0x1 << (static_cast<uint8_t>(m_pinConfig.m_pinNumber) + 16));
    } else {
        // m_pGPIOx->ODR = m_pGPIOx->ODR | (0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
        m_pGPIOx->BSRR = m_pGPIOx->BSRR | (0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
    }
}

/**
 * @brief Writes the given value to the output data register of the GPIO port.
 * 
 * This function sets the output data register (ODR) of the GPIO port associated with the GPIOHandle object
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
 * This function toggles the output state of the GPIO pin associated with the GPIOHandle object.
 * It uses the XOR operator to toggle the specific pin in the GPIO port's output data register (ODR).
 *
 * @note This function assumes that the GPIOHandle object has been properly initialized and configured.
 *
 * @see GPIOHandle
 * @see GPIOHandle::initialize
 * @see GPIOHandle::configurePin
 */
void GPIOHandle::toggleOutputPin() {
    // the BSRR register is write only, can not get the current state of the pin fro BSRR
    // So, use ODR directly for toggle operation. Note ODR is only Word accessible
    m_pGPIOx->ODR = m_pGPIOx->ODR ^ (0x1 << static_cast<uint8_t>(m_pinConfig.m_pinNumber));
}