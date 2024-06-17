#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#define _vo     volatile
#define _ro     volatile const
#define __weak  __attribute__((weak))

#define FLASH_BASEADDR  0x08000000U
#define SRAM1_BASEADDR  0x20000000U
#define SRAM            SRAM1_BASEADDR
#define SRAM2_BASEADDR  (SRAM1_BASEADDR + 0x0001c000)
#define ROM_BASEADDR    0x1FFF0000U // System memory

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR             0x40000000U
#define APB1PERIPH_BASEADDR         PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR         0x40010000U
#define AHB1PERIPH_BASEADDR         0x40020000U
#define AHB2PERIPH_BASEADDR         0x50000000U

/*
* Peripherals on AHB1 Bus
*/
#define GPIOA_BASEADDR              (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR              (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR              (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR              (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR              (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR              (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR              (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR              (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR              (AHB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR              (AHB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR              (AHB1PERIPH_BASEADDR + 0x2800)

/*
* GPIO register structure
*/
typedef struct {
    _vo uint32_t MODER;
    _vo uint32_t OTYPER;
    _vo uint32_t OSPEEDR;
    _vo int32_t PUPDR;
    _vo int32_t IDR;
    _vo int32_t ODR;
    _vo int32_t BSRR;
    _vo int32_t LCKR;
    _vo int32_t AFR[2];
} GPIO_Regdef_t, *pGPIO_Regdef_t;

#define GPIOA   ((pGPIO_RegDef_t) GPIOA_BASEADDR)
#define GPIOB   ((pGPIO_RegDef_t) GPIOB_BASEADDR)
#define GPIOC   ((pGPIO_RegDef_t) GPIOC_BASEADDR)
#define GPIOD   ((pGPIO_RegDef_t) GPIOD_BASEADDR)
#define GPIOE   ((pGPIO_RegDef_t) GPIOE_BASEADDR)
#define GPIOF   ((pGPIO_RegDef_t) GPIOF_BASEADDR)
#define GPIOG   ((pGPIO_RegDef_t) GPIOG_BASEADDR)
#define GPIOH   ((pGPIO_RegDef_t) GPIOH_BASEADDR)
#define GPIOI   ((pGPIO_RegDef_t) GPIOI_BASEADDR)
#define GPIOJ   ((pGPIO_RegDef_t) GPIOJ_BASEADDR)
#define GPIOK   ((pGPIO_RegDef_t) GPIOK_BASEADDR)


#endif /* INC_STM32F407XX_H_ */