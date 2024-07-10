#ifndef INC_STM32F103V8_H_
#define INC_STM32F103V8_H_

#include <cstdint>
namespace stm32f103{
    enum class ClockStatus
    {
        ENABLE,
        DISABLE,
    };

    constexpr uint32_t PERIPH_BASEADDR = 0x40000000U; /*!< Peripheral base address */
    constexpr uint32_t APB1PERIPH_BASEADDR = PERIPH_BASEADDR;
    constexpr uint32_t APB2PERIPH_BASEADDR = 0x40010000U;
    constexpr uint32_t AHBPERIPH_BASEADDR = 0x40018000U;




    /***************************************************************
     * RCC 
     ***************************************************************/

    struct RCCRegDef {
        volatile uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
        volatile uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x04 */
        volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x08 */
        volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
        volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
        volatile uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                    Address offset: 0x14 */
        volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
        volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
        volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x20 */
        volatile uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x24 */
    } ;

    constexpr uint32_t RCC_BASEADDR =  0x40021000U;
    inline RCCRegDef* RCC = reinterpret_cast<RCCRegDef*>(RCC_BASEADDR);


    /***************************************************************
     * GPIO 
     ***************************************************************/
    // clock enable
    inline void enableGPIOAClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 2);
    }

    inline void enableGPIOBClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 3);
    }

    inline void enableGPIOCClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 4);
    }

    inline void enableGPIODClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 5);
    }

    inline void enableGPIOEClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 6);
    }

    inline void enableGPIOFClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 7);
    }

    inline void enableGPIOGClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 8);
    }

    // clock disable
    inline void disableGPIOAClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 2);
    }   

    inline void disableGPIOBClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 3);
    }

    inline void disableGPIOCClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 4);
    }

    inline void disableGPIODClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 5);
    }

    inline void disableGPIOEClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 6);
    }

    inline void disableGPIOFClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 7);
    }

    inline void disableGPIOGClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 8);
    }

    /*
     * GPIO register definition structure
     */
    struct GPIORegDef {
        volatile uint32_t CR[2];    /*~< GPIO port configuration and mode register  Address offset: 0x00 */
        volatile uint32_t IDR;      /*!< GPIO port input data register,             Address offset: 0x08 */
        volatile uint32_t ODR;      /*!< GPIO port output data register,            Address offset: 0x0C */
        volatile uint32_t BSRR;     /*!< GPIO port bit set/reset register,          Address offset: 0x10 */
        volatile uint32_t BRR;      /*!< GPIO port bit reset register,              Address offset: 0x14 */
        volatile uint32_t LCKR;     /*!< GPIO port configuration lock register,     Address offset: 0x18 */
    } ;

    /*
     * GPIO base addresses
     */
    constexpr uint32_t GPIOA_BASEADDR = 0x40010800U;
    constexpr uint32_t GPIOB_BASEADDR = 0x40010C00U;
    constexpr uint32_t GPIOC_BASEADDR = 0x40011000U;
    constexpr uint32_t GPIOD_BASEADDR = 0x40011400U;
    constexpr uint32_t GPIOE_BASEADDR = 0x40011800U;
    constexpr uint32_t GPIOF_BASEADDR = 0x40011C00U;
    constexpr uint32_t GPIOG_BASEADDR = 0x40012000U;

    inline GPIORegDef* GPIOA = reinterpret_cast<GPIORegDef*>(GPIOA_BASEADDR);
    inline GPIORegDef* GPIOB = reinterpret_cast<GPIORegDef*>(GPIOB_BASEADDR);
    inline GPIORegDef* GPIOC = reinterpret_cast<GPIORegDef*>(GPIOC_BASEADDR);
    inline GPIORegDef* GPIOD = reinterpret_cast<GPIORegDef*>(GPIOD_BASEADDR);
    inline GPIORegDef* GPIOE = reinterpret_cast<GPIORegDef*>(GPIOE_BASEADDR);
    inline GPIORegDef* GPIOF = reinterpret_cast<GPIORegDef*>(GPIOF_BASEADDR);
    inline GPIORegDef* GPIOG = reinterpret_cast<GPIORegDef*>(GPIOG_BASEADDR);

    /*
     * GPIO reset functions
     */
    inline void resetGPIOA() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 2);
        RCC->APB2RSTR = RCC->APB2RSTR &~(1 << 2);
    }

    inline void resetGPIOB() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 3);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 3);
    }

    inline void resetGPIOC() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 4);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 4);
    }

    inline void resetGPIOD() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 5);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 5);
    }

    inline void resetGPIOE() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 6);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 6);
    }

    inline void resetGPIOF() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 7);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 7);
    }

    inline void resetGPIOG() {
        RCC->APB2RSTR = RCC->APB2RSTR | (1 << 8);
        RCC->APB2RSTR = RCC->APB2RSTR & ~(1 << 8);
    }
}

#include "stm32f103xx_gpio_driver.h"
#endif