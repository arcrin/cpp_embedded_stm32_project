#pragma once
#include <cstdint>
namespace stm32f407{
    enum class ClockStatus
    {
        ENABLE,
        DISABLE,
    };

    enum class BitStatus : uint8_t {
        CLEAR,
        SET,
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


    /***************************************************************
     * SCB
     ***************************************************************/
    struct SCBRegDef {
        volatile uint32_t CPUID;
        volatile uint32_t ICSR;
        volatile uint32_t VTOR;
        volatile uint32_t AIRCR;
        volatile uint32_t SCR;
        volatile uint32_t CCR;
        volatile uint8_t SHPR[12];
        volatile uint32_t SHCSR;
        volatile uint32_t CFSR;
        volatile uint32_t MMSR;
        volatile uint32_t BFSR;
        volatile uint32_t UFSR;
        volatile uint32_t HFSR;
        volatile uint32_t MMAR;
        volatile uint32_t BFAR;
        volatile uint32_t AFSR;
    };

    inline SCBRegDef* SCB = reinterpret_cast<SCBRegDef*>(0xE000ED00U);

    /****************************************************
     * SysTick
     ****************************************************/
    struct SysTickRegDef {
        volatile uint32_t CTRL;
        volatile uint32_t LOAD;
        volatile uint32_t VAL;
        volatile uint32_t CALIB; 
    };
    
    inline SysTickRegDef* SysTick = reinterpret_cast<SysTickRegDef*>(0xE000E010U);

    extern volatile uint32_t g_sysTickCounter;

    void SysTickInit(uint32_t load_value);

    uint32_t getTicks();

    void delay_ms(uint32_t delay_ms);


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

    enum class NVICIRQNumbers : int8_t {
        MemManage = -12,
        BusFault = -11,
        UsageFault = -11,
        SVCall = -5,
        PendSV = -2,
        SysTick = -1,
        EXTI0 = 6,
        EXTI1 = 7,
        EXTI2 = 8,
        EXTI3 = 9,
        EXTI4 = 10,
        EXTI9_5 = 23,
        EXTI15_10 = 40,
        USART2 = 38,
    };

    const uint8_t NVIC_PRIORITY_BITS = 4U;


    inline NVICRegDef* NVIC = reinterpret_cast<NVICRegDef*>(0xE000E100U);


    inline void nvicEnableIRQ(NVICIRQNumbers irqNumber){
        if (static_cast<uint8_t>(irqNumber) <= 32) {
            NVIC->ISER[0] = NVIC->ISER[0] | (1 << static_cast<uint8_t>(irqNumber));
        } else if (static_cast<uint8_t>(irqNumber) > 32 && static_cast<uint8_t>(irqNumber) <= 64) {
            NVIC->ISER[1] = NVIC->ISER[1] | (1 << (static_cast<uint8_t>(irqNumber) % 32));
        } else if (static_cast<uint8_t>(irqNumber) > 64 && static_cast<uint8_t>(irqNumber) <= 96) {
            NVIC->ISER[2] = NVIC->ISER[2] | (1 << (static_cast<uint8_t>(irqNumber) % 64));
        }
    }

    inline void nvicDisableIRQ(NVICIRQNumbers irqNumber) {
        if (static_cast<uint8_t>(irqNumber) <= 32) {
            NVIC->ICER[0] = NVIC->ICER[0] | (1 << static_cast<uint8_t>(irqNumber));
        } else if (static_cast<uint8_t>(irqNumber) > 32 && static_cast<uint8_t>(irqNumber) <= 64) {
            NVIC->ICER[1] = NVIC->ICER[1] | (1 << (static_cast<uint8_t>(irqNumber) % 32));
        } else if (static_cast<uint8_t>(irqNumber) > 64 && static_cast<uint8_t>(irqNumber) <= 96) {
            NVIC->ICER[2] = NVIC->ICER[2] | (1 << (static_cast<uint8_t>(irqNumber) % 64));
        }
    }

    inline void nvicSetPriority(NVICIRQNumbers irqNumber, uint8_t priority) {
        if (static_cast<int8_t>(irqNumber) >= 0) {
            NVIC->IPR[static_cast<int8_t>(irqNumber)] = priority << NVIC_PRIORITY_BITS;
        } else {
            SCB->SHPR[(static_cast<int8_t>(irqNumber) & 0xF) - 4] = priority << (8 - NVIC_PRIORITY_BITS);
        }
    }

    /***************************************************************
     * EXTI
     ***************************************************************/
    struct EXTIRegDef {
        volatile uint32_t IMR;
        volatile uint32_t EMR;
        volatile uint32_t RTSR;
        volatile uint32_t FTSR;
        volatile uint32_t SWIER;
        volatile uint32_t PR;
    };

    inline EXTIRegDef* EXTI = reinterpret_cast<EXTIRegDef*>(0x40013C00U);

    /****************************************************************
     * RCC register structure
     ****************************************************************/
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

    /****************************************************************
     * SYSCFG register structure
     ****************************************************************/
    struct SYSCFGRegDef {
        volatile uint32_t MEMRMP;
        volatile uint32_t PMC;
        volatile uint32_t EXTICR[4];
                 uint32_t Reserved1[2];
        volatile uint32_t CMPCR;
    };

    inline SYSCFGRegDef* SYSCFG = reinterpret_cast<SYSCFGRegDef*>(0x40013800U);

    inline void enableSYSCFGClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 14);
    }

    inline void disableSYSCFGClock() {
        RCC->APB2ENR = RCC->APB2ENR & ~(1 << 14);
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
    const uint32_t GPIOA_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0000U);
    const uint32_t GPIOB_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0400U);
    const uint32_t GPIOC_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0800U);
    const uint32_t GPIOD_BASEADDR = (AHB1PERIPH_BASEADDR + 0x0C00U);
    const uint32_t GPIOE_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1000U);
    const uint32_t GPIOF_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1400U);
    const uint32_t GPIOG_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1800U);
    const uint32_t GPIOH_BASEADDR = (AHB1PERIPH_BASEADDR + 0x1C00U);
    const uint32_t GPIOI_BASEADDR = (AHB1PERIPH_BASEADDR + 0x2000U);

    inline GPIORegDef* GPIOA = reinterpret_cast<GPIORegDef*>(GPIOA_BASEADDR);
    inline GPIORegDef* GPIOB = reinterpret_cast<GPIORegDef*>(GPIOB_BASEADDR);
    inline GPIORegDef* GPIOC = reinterpret_cast<GPIORegDef*>(GPIOC_BASEADDR);
    inline GPIORegDef* GPIOD = reinterpret_cast<GPIORegDef*>(GPIOD_BASEADDR);
    inline GPIORegDef* GPIOE = reinterpret_cast<GPIORegDef*>(GPIOE_BASEADDR);
    inline GPIORegDef* GPIOF = reinterpret_cast<GPIORegDef*>(GPIOF_BASEADDR);
    inline GPIORegDef* GPIOG = reinterpret_cast<GPIORegDef*>(GPIOG_BASEADDR);
    inline GPIORegDef* GPIOH = reinterpret_cast<GPIORegDef*>(GPIOH_BASEADDR);
    inline GPIORegDef* GPIOI = reinterpret_cast<GPIORegDef*>(GPIOI_BASEADDR);

    inline int8_t getGPIOPortCode(GPIORegDef* pGPIOx) {
        if (pGPIOx == GPIOA) {
            return 0;
        } else if (pGPIOx == GPIOB) {
            return 1;
        } else if (pGPIOx == GPIOC) {
            return 2;
        } else if (pGPIOx == GPIOD) {
            return 3;
        } else if (pGPIOx == GPIOE) {
            return 4;
        } else if (pGPIOx == GPIOF) {
            return 5;
        } else if (pGPIOx == GPIOG) {
            return 6;
        } else if (pGPIOx == GPIOH) {
            return 7;
        } else if (pGPIOx == GPIOI) {
            return 8;
        } 
        return -1;
    }

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

#define disable_irq()       do{asm volatile("cpsid i");} while(0)
#define enable_irq()        do{asm volatile("cpsie i");} while(0)

#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_usart_driver.h"
#include "stm32f407xx_rcc_driver.h"


