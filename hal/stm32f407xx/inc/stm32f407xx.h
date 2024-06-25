#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <cstdint>
namespace stm32f407{
    enum class ClockStatus
    {
        ENABLE,
        DISABLE,
    };

    constexpr uint32_t FLASH_BASE_ADDR = 0x08000000U; /*!< Flash memory base address */
    constexpr uint32_t SRAM1_BASE_ADDR = 0x20000000U; /*!< SRAM1 base address */
    constexpr uint32_t SRAM = SRAM1_BASE_ADDR; /*!< SRAM2 base address */
    constexpr uint32_t SRAM2_BASE_ADDR = SRAM1_BASE_ADDR + 0x0001C000U;
    constexpr uint32_t ROM_BASE_ADDR = 0x1FFF0000U;

    constexpr uint32_t PERIPH_BASEADDR = 0x40000000U; /*!< Peripheral base address */
    constexpr uint32_t APB1PERIPH_BASEADDR = PERIPH_BASEADDR;
    constexpr uint32_t APB2PERIPH_BASEADDR = 0x40010000U;
    constexpr uint32_t AHB1PERIPH_BASEADDR = 0x40020000U;
    constexpr uint32_t AHB2PERIPH_BASEADDR = 0x50000000U;

    /*
     * RCC register structure
     */
    struct RCCRegDef {
        volatile uint32_t CR;
        volatile uint32_t PLLCFGR;
        volatile uint32_t CFGR;
        volatile uint32_t CIR;
        volatile uint32_t AHB1RSTR;
        volatile uint32_t AHB2RSTR;
        volatile uint32_t AHB3RSTR;
        uint32_t Reserved1;
        volatile uint32_t APB1RSTR;
        volatile uint32_t APB2RSTR;
        uint32_t Reserved2[2];
        volatile uint32_t AHB1ENR;
        volatile uint32_t AHB2ENR;
        volatile uint32_t AHB3ENR;
        uint32_t Reserved3;
        volatile uint32_t APB1ENR;
        volatile uint32_t APB2ENR;
        uint32_t Reserved4[2];
        volatile uint32_t AHB1LPENR;
        volatile uint32_t AHB2LPENR;
        volatile uint32_t AHB3LPENR;
        uint32_t Reserved5;
        volatile uint32_t APB1LPENR;
        volatile uint32_t APB2LPENR;
        uint32_t Reserved6[2];
    };

    constexpr uint32_t RCC_BASEADDR = (AHB1PERIPH_BASEADDR + 0x3800U);
    inline RCCRegDef* RCC = reinterpret_cast<RCCRegDef*>(RCC_BASEADDR);

    /****************************************************************
     * GPIO 
     ****************************************************************/

    /*
     * GPIO clock control
     */
    // clock enable
    inline void enableGPIOAClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 0);
    }

    inline void enableGPIOBClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 1);
    }

    inline void enableGPIOCClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 2);
    }

    inline void enableGPIODClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 3);
    }   

    inline void enableGPIOEClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 4);
    }

    inline void enableGPIOFClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 5);
    }

    inline void enableGPIOGClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 6);
    }

    inline void enableGPIOHClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 7);
    }

    inline void enableGPIOIClock() {
        RCC->AHB1ENR = RCC->AHB1ENR | (1 << 8);
    }

    // clock disable
    inline void disableGPIOAClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 0);
    }

    inline void disableGPIOBClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 1);
    }

    inline void disableGPIOCClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 2);
    }

    inline void disableGPIODClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 3);
    }

    inline void disableGPIOEClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 4);
    }

    inline void disableGPIOFClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 5);
    }

    inline void disableGPIOGClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 6);
    }

    inline void disableGPIOHClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 7);
    }

    inline void disableGPIOIClock() {
        RCC->AHB1ENR = RCC->AHB1ENR & ~(1 << 8);
    }


    /*
     * GPIO register definition structure
     */
    struct GPIORegDef {
        volatile uint32_t MODER;
        volatile uint32_t OTYPER;
        volatile uint32_t OSPEEDR;
        volatile uint32_t PUPDR;
        volatile uint32_t IDR;
        volatile uint32_t ODR;
        volatile uint32_t BSRR;
        volatile uint32_t LCKR;
        volatile uint32_t AFR[2];
    };

    /*
     * GPIO base addresses
     */
    constexpr uint32_t GPIOA_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0000U);
    constexpr uint32_t GPIOB_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0400U);
    constexpr uint32_t GPIOC_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0800U);
    constexpr uint32_t GPIOD_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0C00U);
    constexpr uint32_t GPIOE_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1000U);
    constexpr uint32_t GPIOF_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1400U);
    constexpr uint32_t GPIOG_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1800U);
    constexpr uint32_t GPIOH_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1C00U);
    constexpr uint32_t GPIOI_BASEADDR = (AHB1PERIPH_BASEADDR + 0x2000U);

    inline GPIORegDef* GPIOA = reinterpret_cast<GPIORegDef*>(GPIOA_BASEADDR);
    inline GPIORegDef* GPIOB = reinterpret_cast<GPIORegDef*>(GPIOB_BASEADDR);
    inline GPIORegDef* GPIOC = reinterpret_cast<GPIORegDef*>(GPIOC_BASEADDR);
    inline GPIORegDef* GPIOD = reinterpret_cast<GPIORegDef*>(GPIOD_BASEADDR);
    inline GPIORegDef* GPIOE = reinterpret_cast<GPIORegDef*>(GPIOE_BASEADDR);
    inline GPIORegDef* GPIOF = reinterpret_cast<GPIORegDef*>(GPIOF_BASEADDR);
    inline GPIORegDef* GPIOG = reinterpret_cast<GPIORegDef*>(GPIOG_BASEADDR);
    inline GPIORegDef* GPIOH = reinterpret_cast<GPIORegDef*>(GPIOH_BASEADDR);
    inline GPIORegDef* GPIOI = reinterpret_cast<GPIORegDef*>(GPIOI_BASEADDR);

    /*
     * GPIO reset functions
     */
    inline void resetGPIOA() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 0);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 0);
    }

    inline void resetGPIOB() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 1);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 1);
    
    }

    inline void resetGPIOC() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 2);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 2);
    }

    inline void resetGPIOD() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 3);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 3);
    }

    inline void resetGPIOE() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 4);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 4);
    }

    inline void resetGPIOF() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 5);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 5);
    }

    inline void resetGPIOG() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 6);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 6);
    }

    inline void resetGPIOH() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 7);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 7);
    }

    inline void resetGPIOI() {
        RCC->AHB1RSTR = RCC->AHB1RSTR | (1 << 8);
        RCC->AHB1RSTR = RCC->AHB1RSTR & ~(1 << 8);
    }
};  // namespace 

#include "stm32f407xx_gpio_driver.h"



#endif /* INC_STM32F407XX_H_ */