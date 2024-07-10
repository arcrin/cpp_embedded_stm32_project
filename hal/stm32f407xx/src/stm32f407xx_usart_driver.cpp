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
    } else if (m_usartConfig.m_flowControl == USARTFlowControl::RTS_CTS) {
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_CTSE);
        m_pUSARTx->CR3 = m_pUSARTx->CR3 | (1 << USART_CR3_RTSE);
    }
    // set baud rate
    setBaudRate();
}

void USARTHandle::sendData(uint8_t* pTxBuffer, uint32_t txLength) {
    uint16_t* pData;
    // Loop over until "txLength" number of bytes are transferred   
    for (uint32_t i = 0; i < txLength; i++) {
        while (!getFlagStatus(USART_SR_TXE));
        if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
            // if 9-bit load the DR with 2 bytes masking the bits other than first 9 bits
            pData = (uint16_t*) pTxBuffer;
            m_pUSARTx->DR = (*pData & (uint16_t) 0x01ff);

            if (m_usartConfig.m_parity == USARTParity::NONE) {
                pTxBuffer++;
                pTxBuffer++;
            } else {
                pTxBuffer++;
            }
        } else {
            // This is 8 bit data transfer
            m_pUSARTx->DR = (*pTxBuffer & (uint8_t) 0xff);
            // Increment the buffer address
            pTxBuffer++;
        }
        while(!getFlagStatus(USART_SR_TC));
    }
}

void USARTHandle::receiveData(uint8_t* pRxBuffer, uint32_t rxLength) {
    for (uint32_t i = 0; i < rxLength; i++) {
        while(getFlagStatus(USART_SR_RXNE));
        if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
            if (m_usartConfig.m_parity == USARTParity::NONE) {
                *((uint16_t*) pRxBuffer) = (m_pUSARTx->DR & (uint16_t) 0x01ff);
                pRxBuffer++;
                pRxBuffer++;
            } else {
                *pRxBuffer = (m_pUSARTx->DR & (uint8_t) 0xff);
                pRxBuffer++;
            }
        } else {
            if (m_usartConfig.m_parity == USARTParity::NONE) {
                *pRxBuffer = (uint8_t)(m_pUSARTx->DR & (uint8_t) 0xff);
            } else {
                *pRxBuffer = (uint8_t)(m_pUSARTx->DR & (uint8_t) 0x7f);
            }
            pRxBuffer++;
        }
    }
}

void USARTHandle::setBaudRate() {
    uint32_t peripheralClock;
    uint32_t usartDiv;
    uint32_t mantissa, fraction;    
    uint32_t tempreg = 0;

    // Get the value of APB bus clock into the variable peripheralClock
    if (m_pUSARTx == USART1 || m_pUSARTx == USART6)  {
        // USART1 and USART6 are on AOB2 bus
        peripheralClock = RCCUtil::RCCGetPCLK2Value();
    } else {
        // USART2, USART3, UART4, UART5 are on APB1 bus
        peripheralClock = RCCUtil::RCCGetPCLK1Value();
    }

    // check for OVER8 (oversampling setting)   
    if (m_pUSARTx->CR1 & (1 << USART_CR1_OVER8)) {
        usartDiv = ((25 * peripheralClock) / (2 * static_cast<uint32_t>(m_usartConfig.m_baud)));
    } else {
        usartDiv = ((25 * peripheralClock) / (4 * static_cast<uint32_t>(m_usartConfig.m_baud))); 
    }

    mantissa = usartDiv / 100;

    // place the mantissa part in appropriate bit position
    tempreg |= mantissa << 4;

    fraction = (usartDiv - (mantissa * 100));   

    // calculate the final fraction
    if (m_pUSARTx->CR1 & (1 << USART_CR1_OVER8)) {
        fraction = (((fraction * 8) + 50) / 100) & (uint8_t)0x07;
    } else {
        fraction = (((fraction * 16) + 50) / 100) & (uint8_t)0x0F;
    }
    // Place the fraction part in appropriate bit position.
    tempreg |= fraction;

    // copy the value of tempreg in to BRR register
    m_pUSARTx->BRR = tempreg;
}

uint8_t USARTHandle::getFlagStatus(uint8_t statusFlagBit) {
    if (m_pUSARTx->SR & (1 << statusFlagBit)) {
        return 1;
    }
    return 0;   
}

void USARTHandle::clearFlag(uint8_t statusFlagBit) {
    m_pUSARTx->SR = m_pUSARTx->SR & ~(1 << statusFlagBit);
}   

void USARTHandle::peripheralControl(bool enable) {
    if (enable) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << USART_CR1_UE);
    } else {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << USART_CR1_UE);
    }
}