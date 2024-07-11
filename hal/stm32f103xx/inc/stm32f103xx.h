#pragma once

#include <cstdint>
namespace stm32f103 {
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


    /*****************************************************************
     * SysTick
     *****************************************************************/
    struct SysTickRegDef {
        volatile uint32_t CTRL;
        volatile uint32_t LOAD;
        volatile uint32_t VAL;
        volatile uint32_t CALIB;
    };

    inline SysTickRegDef* SysTick = reinterpret_cast<SysTickRegDef*>(0xE000E010U);

    extern volatile uint32_t g_sysTickCounter;

    void SysTickInit(uint32_t loadValue);
    
    uint32_t getTicks();

    void delayInMs(uint32_t ms);

    /***************************************************************
     * NVIC
     ***************************************************************/
    struct NVICRegDef {
        volatile uint32_t ISER[8U]; /*!< NVIC interrupt set-enable register, Address offset: 0x00 */
                 uint32_t RESERVED0[24U];
        volatile uint32_t ICER[8U]; /*!< NVIC interrupt clear-enable register, Address offset: 0x80 */
                 uint32_t RSERVED1[24U];
        volatile uint32_t ISPR[8U]; /*!< NVIC interrupt set-pending register, Address offset: 0x100 */
                 uint32_t RESERVED2[24U];
        volatile uint32_t ICPR[8U]; /*!< NVIC interrupt clear-pending register, Address offset: 0x180 */
                 uint32_t RESERVED3[24U];
        volatile uint32_t IABR[8U]; /*!< NVIC interrupt active bit register, Address offset: 0x200 */
                 uint32_t RESERVED4[56U];
        volatile uint8_t IPR[60U];  /*!< NVIC interrupt priority register, Address offset: 0x300 */
        volatile uint32_t STIR;     /*!< Software trigger interrupt register, Address offset: 0xE00 */
    };
    
    inline NVICRegDef* NVIC = reinterpret_cast<NVICRegDef*>(0xE000E100U);

    enum class NVICIRQNumbers: int8_t {        
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
    };

    const uint8_t NVIC_PRIORITY_BITS = 4;

    inline void nvicEnableIRQ(NVICIRQNumbers irqNumber) {
        if (static_cast<int8_t>(irqNumber) <= 32) {
            NVIC->ISER[0] = NVIC->ISER[0] | (1 << static_cast<int8_t>(irqNumber));
        } else if (static_cast<int8_t>(irqNumber) > 32 && static_cast<int8_t>(irqNumber) <= 64) {
            NVIC->ISER[1] = NVIC->ISER[1] | (1 << (static_cast<int8_t>(irqNumber) % 32));
        } 
    }


    inline void nvicDisableIRQ(NVICIRQNumbers irqNumber) {
        if (static_cast<int8_t>(irqNumber) <= 32) {
            NVIC->ICER[0] = NVIC->ICER[0] | (1 << static_cast<int8_t>(irqNumber));
        } else if (static_cast<int8_t>(irqNumber) > 32 && static_cast<int8_t>(irqNumber) <= 64) {
            NVIC->ICER[1] = NVIC->ICER[1] | (1 << (static_cast<int8_t>(irqNumber) % 32));
        } 
    }

    inline void nvicSetPriority(NVICIRQNumbers irqNumber, uint8_t priority) {
        if (static_cast<int8_t>(irqNumber) >= 0) {
            NVIC->IPR[static_cast<int8_t>(irqNumber)] = (priority << (8 - NVIC_PRIORITY_BITS));    
        } else {
            int8_t exceptionIrqPosition = (static_cast<int8_t>(irqNumber) & 0xf) - 4;
            SCB->SHPR[exceptionIrqPosition] = priority << (8 - NVIC_PRIORITY_BITS);
        }
    }


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
        }
        return -1;
    }

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

    /***********************************************
     * AFIO
     ***********************************************/
    struct AFIORegDef {
        volatile uint32_t EVCR;        /*!< AFIO Event control register (AFIO_EVCR),                 Address offset: 0x00 */
        volatile uint32_t MAPR;        /*!< AFIO MAP control register (AFIO_MAPR),                   Address offset: 0x04 */
        volatile uint32_t EXTICR[4];   /*!< AFIO External interrupt configuration registers,         Address offset: 0x08-0x14 */
        volatile uint32_t MAPR2;       /*!< AFIO MAP control register 2,                             Address offset: 0x18 */
    };

    inline AFIORegDef* AFIO = reinterpret_cast<AFIORegDef*>(0x40010000U);

    inline void enebleAFIOClock() {
        RCC->APB2ENR = RCC->APB2ENR | (1 << 0);
    }

    /***********************************************
     * EXTI
     ***********************************************/
    struct EXTIRegDef {
        volatile uint32_t IMR; /*!< EXTI Interrupt mask register, Address offset: 0x00 */
        volatile uint32_t EMR; /*!< EXTI Event mask register, Address offset: 0x04 */
        volatile uint32_t RTSR; /*!< EXTI Rising trigger selection register, Address offset: 0x08 */
        volatile uint32_t FTSR; /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
        volatile uint32_t SWIER; /*!< EXTI Software interrupt event register, Address offset: 0x10 */
        volatile uint32_t PR; /*!< EXTI Pending register, Address offset: 0x14 */
    };
    
    inline EXTIRegDef* EXTI = reinterpret_cast<EXTIRegDef*>(0x40010400U);
}

#define disable_irq()       do{asm volatile("cpsid i");} while(0)
#define enable_irq()        do{asm volatile("cpsie i");} while(0)

#include "stm32f103xx_gpio_driver.h"