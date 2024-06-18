#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <cstdint>
namespace STM32F407{
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
    struct RCC_RegDef_t {
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
        uint16_t Reserved2[2];
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
    inline RCC_RegDef_t* RCC = reinterpret_cast<RCC_RegDef_t*>(RCC_BASEADDR);

    /****************************************************************
     * GPIO 
     ****************************************************************/

    /*
     * GPIO register definition structure
     */
    struct GPIO_RegDef_t {
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

    inline GPIO_RegDef_t* GPIOA = reinterpret_cast<GPIO_RegDef_t*>(GPIOA_BASEADDR);
    inline GPIO_RegDef_t* GPIOB = reinterpret_cast<GPIO_RegDef_t*>(GPIOB_BASEADDR);
    inline GPIO_RegDef_t* GPIOC = reinterpret_cast<GPIO_RegDef_t*>(GPIOC_BASEADDR);
    inline GPIO_RegDef_t* GPIOD = reinterpret_cast<GPIO_RegDef_t*>(GPIOD_BASEADDR);
    inline GPIO_RegDef_t* GPIOE = reinterpret_cast<GPIO_RegDef_t*>(GPIOE_BASEADDR);
    inline GPIO_RegDef_t* GPIOF = reinterpret_cast<GPIO_RegDef_t*>(GPIOF_BASEADDR);
    inline GPIO_RegDef_t* GPIOG = reinterpret_cast<GPIO_RegDef_t*>(GPIOG_BASEADDR);
    inline GPIO_RegDef_t* GPIOH = reinterpret_cast<GPIO_RegDef_t*>(GPIOH_BASEADDR);
    inline GPIO_RegDef_t* GPIOI = reinterpret_cast<GPIO_RegDef_t*>(GPIOI_BASEADDR);

};  // namespace STM32F407



#endif /* INC_STM32F407XX_H_ */