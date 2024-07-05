#include "stm32f407xx.h"

using namespace stm32f407;

void USARTHandle::periClockControl(ClockStatus status) {
    if (status == ClockStatus::ENABLE) {
        if (m_pUSARTx == USART1) {
            enableUSART1Clock();
        } else if (m_pUSARTx == USART2) {
            enableUSART2Clock();    
        } else if (m_pUSARTx == USART3) {
            enableUSART3Clock();
        } else if (m_pUSARTx == UART4) {
            enableUART4Clock();
        } else if (m_pUSARTx == UART5) {
            enableUART5Clock();
        } else if (m_pUSARTx == USART6) {
            enableUSART6Clock();
        }
    } else if (status == ClockStatus::DISABLE) {
        if (m_pUSARTx == USART1) {
            disableUSART1Clock();
        } else if (m_pUSARTx == USART2) {
            disableUSART2Clock();    
        } else if (m_pUSARTx == USART3) {
            disableUSART3Clock();
        } else if (m_pUSARTx == UART4) {
            disableUART4Clock();
        } else if (m_pUSARTx == UART5) {
            disableUART5Clock();
        } else if (m_pUSARTx == USART6) {
            disableUSART6Clock();
        }
    }
}

void USARTHandle::init() {
    periClockControl(ClockStatus::ENABLE);

    // Transmit or receive mode
    if (m_usartConfig.m_mode == USARTMode::RX) {
        m_pUSARTx->CR1 = (1 << USART_CR1_RE);
    } else if (m_usartConfig.m_mode == USARTMode::TX) {
        m_pUSARTx->CR1 = (1 << USART_CR1_TE);
    } else if (m_usartConfig.m_mode == USARTMode::TX_RX) {
        m_pUSARTx->CR1 = (1 << USART_CR1_RE) | (1 << USART_CR1_TE);
    }

    // word length select
    m_pUSARTx->CR1 = m_pUSARTx->CR1 | (static_cast<uint8_t>(m_usartConfig.m_wordLength) << USART_CR1_M);

    // parity control
    if (m_usartConfig.m_parity == USARTParity::EVEN) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << USART_CR1_PCE);
        m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << USART_CR1_PS);
    } else if (m_usartConfig.m_parity == USARTParity::ODD) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << USART_CR1_PCE);
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << USART_CR1_PS);
    }  

    // stop bits
    m_pUSARTx->CR2 = m_pUSARTx->CR2 | (static_cast<uint8_t>(m_usartConfig.m_stopBits) << USART_CR2_STOP);

    // hardware flow control
    if (m_usartConfig.m_flowControl == USARTFlowControl::CTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_CTSE);
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_RTSE);
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::CTS_RTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_CTSE);
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_RTSE);
    }
    // set baud rate
}