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


    /****************************************************
     * NVIC
     ****************************************************/
    struct NVICRegDef {
        volatile uint32_t ISER[8U];
                 uint32_t Reserved0[24U];
        volatile uint32_t ICER[8U];
                 uint32_t Reserved1[24U];
        volatile uint32_t ISPR[8U];
                 uint32_t Reserved2[24U];
        volatile uint32_t ICPR[8U];
                 uint32_t Reserved3[24U];
        volatile uint32_t IABR[8U];
                 uint32_t Reserved4[56U];
        volatile uint8_t IPR[240U];
                 uint32_t Reserved5[644U];
        volatile uint32_t STIR;
    };

    inline NVICRegDef* NVIC = reinterpret_cast<NVICRegDef*>(0xE000E100U);

    void NVICSetPriority(int8_t IRQn, uint8_t priority);

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

    /******************************* 
    * UART Peripheral
    ********************************/

    // Register
    struct USARTRegDef {
        volatile uint32_t SR;
        volatile uint32_t DR;
        volatile uint32_t BRR;
        volatile uint32_t CR1;
        volatile uint32_t CR2;
        volatile uint32_t CR3;
        volatile uint32_t GTPR;
    };

    // USART_CR1 bit position
    constexpr const uint8_t USART_CR1_SBK = 0;
    constexpr const uint8_t USART_CR1_RWU = 1;
    constexpr const uint8_t USART_CR1_RE = 2;
    constexpr const uint8_t USART_CR1_TE = 3;
    constexpr const uint8_t USART_CR1_IDLEIE = 4;
    constexpr const uint8_t USART_CR1_RXNEIE = 5;
    constexpr const uint8_t USART_CR1_TCIE = 6;
    constexpr const uint8_t USART_CR1_TXEIE = 7;
    constexpr const uint8_t USART_CR1_PEIE = 8;
    constexpr const uint8_t USART_CR1_PS = 9;
    constexpr const uint8_t USART_CR1_PCE = 10;
    constexpr const uint8_t USART_CR1_WAKE = 11;
    constexpr const uint8_t USART_CR1_M = 12;
    constexpr const uint8_t USART_CR1_UE = 13;
    constexpr const uint8_t USART_CR1_OVER8 = 15;

    // USART_CR2 bit position
    constexpr const uint8_t USART_CR2_ADD = 0;
    constexpr const uint8_t USART_CR2_LBDL = 5;
    constexpr const uint8_t USART_CR2_LBDIE = 6;
    constexpr const uint8_t USART_CR2_LBCL = 8;
    constexpr const uint8_t USART_CR2_CPHA = 9;
    constexpr const uint8_t USART_CR2_CPOL = 10;
    constexpr const uint8_t USART_CR2_CLKEN = 11;
    constexpr const uint8_t USART_CR2_STOP = 12;
    constexpr const uint8_t USART_CR2_LINEN = 14;

    // USART_CR3 bit position
    constexpr const uint8_t USART_CR3_EIE = 0;
    constexpr const uint8_t USART_CR3_IREN = 1;
    constexpr const uint8_t USART_CR3_IRLP = 2;
    constexpr const uint8_t USART_CR3_HDSEL = 3;
    constexpr const uint8_t USART_CR3_NACK = 4;
    constexpr const uint8_t USART_CR3_SCEN = 5;
    constexpr const uint8_t USART_CR3_DMAR = 6;
    constexpr const uint8_t USART_CR3_DMAT = 7;
    constexpr const uint8_t USART_CR3_RTSE = 8;
    constexpr const uint8_t USART_CR3_CTSE = 9;
    constexpr const uint8_t USART_CR3_CTSIE = 10;
    constexpr const uint8_t USART_CR3_ONEBIT = 11;

    // USART_SR bit position    
    constexpr const uint8_t USART_SR_PE = 0;
    constexpr const uint8_t USART_SR_FE = 1;
    constexpr const uint8_t USART_SR_NF = 2;
    constexpr const uint8_t USART_SR_ORE = 3;
    constexpr const uint8_t USART_SR_IDLE = 4;
    constexpr const uint8_t USART_SR_RXNE = 5;
    constexpr const uint8_t USART_SR_TC = 6;
    constexpr const uint8_t USART_SR_TXE = 7;
    constexpr const uint8_t USART_SR_LBD = 8;
    constexpr const uint8_t USART_SR_CTS = 9;


    constexpr uint32_t USART1_BASEADDR = (APB2PERIPH_BASEADDR + 0x1000U);
    constexpr uint32_t USART2_BASEADDR = (APB1PERIPH_BASEADDR + 0x4400U);
    constexpr uint32_t USART3_BASEADDR = (APB1PERIPH_BASEADDR + 0x4800U);
    constexpr uint32_t UART4_BASEADDR = (APB1PERIPH_BASEADDR + 0x4C00U);
    constexpr uint32_t UART5_BASEADDR = (APB1PERIPH_BASEADDR + 0x5000U);
    constexpr uint32_t USART6_BASEADDR = (APB2PERIPH_BASEADDR + 0x1400U);   

    inline USARTRegDef* USART1 = reinterpret_cast<USARTRegDef*>(USART1_BASEADDR);
    inline USARTRegDef* USART2 = reinterpret_cast<USARTRegDef*>(USART2_BASEADDR);
    inline USARTRegDef* USART3 = reinterpret_cast<USARTRegDef*>(USART3_BASEADDR);
    inline USARTRegDef* UART4 = reinterpret_cast<USARTRegDef*>(UART4_BASEADDR);
    inline USARTRegDef* UART5 = reinterpret_cast<USARTRegDef*>(UART5_BASEADDR);
    inline USARTRegDef* USART6 = reinterpret_cast<USARTRegDef*>(USART6_BASEADDR);

    // UASRT Clock functions
    inline void enableUSART1Clock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 4);
    }   

    inline void enableUSART2Clock() {
        RCC->APB1ENR = RCC->APB1ENR | (1 << 17);
    }

    inline void enableUSART3Clock() {
        RCC->APB1ENR = RCC->APB1ENR | (1 << 18);
    }

    inline void enableUART4Clock() {
        RCC->APB1ENR = RCC->APB1ENR | (1 << 19);
    }

    inline void enableUART5Clock() {
        RCC->APB1ENR = RCC->APB1ENR | (1 << 20);
    }

    inline void enableUSART6Clock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 5);
    }   

    inline void disableUSART1Clock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 4);
    }

    inline void disableUSART2Clock() {
        RCC->APB1ENR = RCC->APB1ENR & ~(1 << 17);
    }

    inline void disableUSART3Clock() {
        RCC->APB1ENR = RCC->APB1ENR & ~(1 << 18);
    }

    inline void disableUART4Clock() {
        RCC->APB1ENR = RCC->APB1ENR & ~(1 << 19);
    }

    inline void disableUART5Clock() {
        RCC->APB1ENR = RCC->APB1ENR & ~(1 << 20);
    }

    inline void disableUSART6Clock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 5);
    }
};  // namespace 

#include "stm32f407xx_gpio_driver.h"



#endif /* INC_STM32F407XX_H_ */