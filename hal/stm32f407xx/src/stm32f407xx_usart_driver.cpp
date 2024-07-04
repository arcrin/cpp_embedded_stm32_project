#include "stm32f407xx_usart_driver.h"

using namespace stm32f407;

/**
 * @brief Controls the peripheral clock for the USART.
 *
 * This function enables or disables the peripheral clock for the USART based on the specified status.
 *
 * @param status The status of the peripheral clock (ENABLE or DISABLE).
 */
inline void USARTHandle::periClockControl(ClockStatus status) {
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
    } 
    else if (status == ClockStatus::DISABLE) {
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
    uint32_t tempreg = 0;
    
    // CR1 Configuration
    // Enable clock
    periClockControl(ClockStatus::ENABLE);

    // Enable USART Tx and Rx engines according to the configuration
    if (m_usartConfig.m_mode == USARTMode::RX) {
        tempreg |= (1 << USART_CR1_RE);
    } else if (m_usartConfig.m_mode == USARTMode::TX) {
        tempreg |= (1 << USART_CR1_TE);
    } else if (m_usartConfig.m_mode == USARTMode::TX_RX) {
        tempreg |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
    }
    // Configure the word length
    tempreg |= (static_cast<uint8_t>(m_usartConfig.m_wordLength) << USART_CR1_M);

    // Configure the parity control bit fields
    if (m_usartConfig.m_parity == USARTParity::EVEN) {
        tempreg |= (1 << USART_CR1_PCE);
    } else if (m_usartConfig.m_parity == USARTParity::ODD) {
        tempreg |= static_cast<uint8_t>(((1 << USART_CR1_PCE) | (1 << USART_CR1_PS)));
    }

    m_pUSARTx->CR1 = tempreg;

    // stop bit configuration
    m_pUSARTx->CR2 = m_pUSARTx->CR2 | (static_cast<uint8_t>(m_usartConfig.m_stopBits) << USART_CR2_STOP);

    // Configure hardware flow control
    if (m_usartConfig.m_flowControl == USARTFlowControl::CTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_CTSE);
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_RTSE);
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS_CTS) {
        m_pUSARTx->CR3 = (m_pUSARTx->CR3 | ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE)));
    }
    setBaudRate(m_usartConfig.m_baud);
}

void setBaudRate(USARTBaud baudRate) {
    
}