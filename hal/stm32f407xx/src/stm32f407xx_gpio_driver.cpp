#include "stm32f407xx_gpio_driver.h"

using namespace STM32F407;

/**
 * @brief Controls the peripheral clock for a GPIO port.
 * 
 * This function enables or disables the peripheral clock for a GPIO port.
 * 
 * @param status The status of the clock, either ENABLE or DISABLE.
 * 
 * @note This function modifies the AHB1ENR register of the RCC peripheral.
 */

inline void GPIO_Handle::periClockControl(ClockStatus status) {
    if (status == ClockStatus::ENABLE) {
        if (pGPIOx == GPIOA) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 0);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOB) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 1);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOC) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 2);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOD) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 3);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOE) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 4);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOF) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 5);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOG) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 6);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOH) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 7);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOI) {
            uint32_t temp = RCC->AHB1ENR;
            temp |= (1 << 8);
            RCC->AHB1ENR = temp;
        }
    } 
    else if (status == ClockStatus::DISABLE) {
        if (pGPIOx == GPIOA) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 0);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOB) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 1);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOC) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 2);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOD) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 3);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOE) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 4);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOF) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 5);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOG) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 6);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOH) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 7);
            RCC->AHB1ENR = temp;
        } else if (pGPIOx == GPIOI) {
            uint32_t temp = RCC->AHB1ENR;
            temp &= ~(1 << 8);
            RCC->AHB1ENR = temp;
        }
    }
}


void GPIO_Handle::init() {
    // Enable clock
    periClockControl(ClockStatus::ENABLE);
    
    // 1. Configure the mode of GPIO pin
    if (PinConfig.PinMode <= GPIOPinMode::ANALOG) {
        pGPIOx->MODER = pGPIOx->MODER & ~(0x3 << (static_cast<uint8_t>(PinConfig.PinNumber) * 2));
        pGPIOx->MODER = pGPIOx->MODER | (static_cast<uint8_t>(PinConfig.PinMode) << (static_cast<uint8_t>(PinConfig.PinNumber) * 2));
    }
}