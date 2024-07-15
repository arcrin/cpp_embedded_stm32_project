#include "stm32f103xx_usart_driver.h"

using namespace stm32f103;

void USARTHandle::periClockControl(ClockStatus status) {
    switch (status) {
        case ClockStatus::ENABLE:
            if (m_pUSARTx == USART1) {
                enableUSART1Clock();
            } else if (m_pUSARTx == USART2) {
                enableUSART2Clock();
            } else if (m_pUSARTx == USART3) {
                enableUSART3Clock();
            } 
        case ClockStatus::DISABLE:
            if (m_pUSARTx == USART1) {
                disableUSART1Clock();
            } else if (m_pUSARTx == USART2) {
                disableUSART2Clock();
            } else if (m_pUSARTx == USART3) {
                disableUSART3Clock();
            }
    }
}

void USARTHandle::init() {
    periClockControl(ClockStatus::ENABLE);

    // Mode select
    if (m_usartConfig.m_mode == USARTMode::RX) {
        m_pUSARTx->CR1 = (1 << static_cast<uint8_t>(USARTCR1Bit::RE));
    } else if (m_usartConfig.m_mode == USARTMode::TX) {
        m_pUSARTx->CR1 = (1 << static_cast<uint8_t>(USARTCR1Bit::TE));
    } else if (m_usartConfig.m_mode == USARTMode::TX_RX) {
        m_pUSARTx->CR1 = (1 << static_cast<uint8_t>(USARTCR1Bit::RE)) | (1 << static_cast<uint8_t>(USARTCR1Bit::TE));
    }

    // word length select
    m_pUSARTx->CR1 = m_pUSARTx->CR1 | (static_cast<uint8_t>(m_usartConfig.m_wordLength) << static_cast<uint8_t>(USARTCR1Bit::M));

    // parity control
    if (m_usartConfig.m_parity == USARTParity::EVEN) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::PCE));
        m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::PS));
    } else if (m_usartConfig.m_parity == USARTParity::ODD) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::PCE));
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::PS));
    } 

    // stop bits
    m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(m_usartConfig.m_stopBits) << static_cast<uint8_t>(USARTCR2Bit::STOP));

    // hardware flow control
    if (m_usartConfig.m_flowControl == USARTFlowControl::CTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << static_cast<uint8_t>(USARTCR3Bit::CTSE));
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << static_cast<uint8_t>(USARTCR3Bit::RTSE));
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS_CTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << static_cast<uint8_t>(USARTCR3Bit::CTSE));
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << static_cast<uint8_t>(USARTCR3Bit::RTSE));
    }

    // set baud rate
    
}

void USARTHandle::peripheralControl(bool status) {
    if (status) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::UE));
    } else {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::UE));
    }
}

void USARTHandle::setBaudRate() {
    uint32_t peripheralClock;
    uint32_t usartDiv;
    uint32_t mantissa, fraction;    
    uint32_t tempreg = 0;

    // Get the value of APB bus clock into the variable peripheralClock
    if (m_pUSARTx == USART1)  {
        // USART1 is on APB2 bus
        peripheralClock = RCCUtil::RCCGetPCLK2Value();
    } else {
        // USART2, USART3 are on APB1 bus
        peripheralClock = RCCUtil::RCCGetPCLK1Value();
    }

    // check for OVER8 (oversampling setting)   
    if (m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::OVER8))) {
        usartDiv = ((25 * peripheralClock) / (2 * static_cast<uint32_t>(m_usartConfig.m_baud)));
    } else {
        usartDiv = ((25 * peripheralClock) / (4 * static_cast<uint32_t>(m_usartConfig.m_baud))); 
    }

    mantissa = usartDiv / 100;

    // place the mantissa part in appropriate bit position
    tempreg |= mantissa << 4;

    fraction = (usartDiv - (mantissa * 100));   

    // calculate the final fraction
    if (m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::OVER8))) {
        fraction = (((fraction * 8) + 50) / 100) & (uint8_t)0x07;
    } else {
        fraction = (((fraction * 16) + 50) / 100) & (uint8_t)0x0F;
    }
    // Place the fraction part in appropriate bit position.
    tempreg |= fraction;

    // copy the value of tempreg in to BRR register
    m_pUSARTx->BRR = tempreg;
}