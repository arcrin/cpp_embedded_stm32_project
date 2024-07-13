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
    m_pUSARTx->CR2 = m_pUSARTx->CR2 | (static_cast<uint8_t>(m_usartConfig.m_stopBits) << static_cast<uint8_t>(USARTCR2Bit::STOP));

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
    setBaudRate();
    m_txState = USARTLineStatus::Ready;
    m_rxState = USARTLineStatus::Ready;
    peripheralControl(true);
}

void USARTHandle::sendData(uint8_t* pTxBuffer, uint32_t txLength) {
    uint16_t* pData;
    // Loop over until "txLength" number of bytes are transferred   
    for (uint32_t i = 0; i < txLength; i++) {
        while (!static_cast<uint8_t>(getFlagStatus(USARTStatusFlags::TransmitDataRegisterEmpty)));
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
        while(!static_cast<uint8_t>(getFlagStatus(USARTStatusFlags::TransmissionComplete)));
    }
}

void USARTHandle::receiveData(uint8_t* pRxBuffer, uint32_t rxLength) {
    for (uint32_t i = 0; i < rxLength; i++) {
        while(static_cast<uint8_t>(getFlagStatus(USARTStatusFlags::ReceiveDataRegisterNotEmtpy)));
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

BitStatus USARTHandle::getFlagStatus(USARTStatusFlags statusFlag) {
    if (m_pUSARTx->SR & (1 << static_cast<uint8_t>(statusFlag))) {
        return BitStatus::SET;  
    }
    return BitStatus::CLEAR;   
}

void USARTHandle::clearFlag(USARTStatusFlags statusFlag) {
    m_pUSARTx->SR = m_pUSARTx->SR & ~(1 << static_cast<uint8_t>(statusFlag));
}   

void USARTHandle::peripheralControl(bool enable) {
    if (enable) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::UE));
    } else {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::UE));
    }
}

USARTLineStatus USARTHandle::receiveDataWithInterrupt(uint8_t* pRxBuffer, uint32_t rxLength){
    USARTLineStatus rxState = m_rxState;
    if (rxState != USARTLineStatus::BusyInRx) {
        m_rxLen = rxLength;
        m_pRxBuffer = pRxBuffer;
        m_rxState = USARTLineStatus::BusyInRx;
        (void) m_pUSARTx->DR;

        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));
    }
    return rxState;
}

USARTLineStatus USARTHandle::sendDataWithInterrupt(uint8_t* pTxBuffer, uint32_t txLength) {
    USARTLineStatus txState = m_txState;
    if (txState != USARTLineStatus::BusyInTx) {
        m_txLen = txLength;
        m_pTxBuffer = pTxBuffer;
        m_rxState = USARTLineStatus::BusyInTx;

        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::TXEIE));          

        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::TCIE));
    }

    return txState;
}

void USARTHandle::irqHandler() {
    uint32_t temp1, temp2;
    uint16_t* pData;    
    /********************Check for TC flag*****************************/
    // Check the stat of TC (Transmission Complete) flag in the SR
    temp1 = m_pUSARTx->SR & (1 << static_cast<uint8_t>(USARTStatusFlags::TransmissionComplete));
    // Check the state of TCIE (Transmission Complete Interrupt Enable) bit in the CR1
    temp2 = m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::TCIE));

    // When both TC and TCIE are set, the transmission complete interrupt is generated
    if (temp1 && temp2) {
        // Check the transmission line state
        if (m_txState == USARTLineStatus::BusyInTx) {
            // Check the m_txLen. If it is zero then close the data transmission
            if (!m_txLen) {
                // Clear the TC flag
                clearFlag(USARTStatusFlags::TransmissionComplete);
                // NOTE: Clear the TCIE bit ?? Wouldn't this disable the interrupt?
                m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::TCIE));
                // Reset the transmission state  
                m_txState = USARTLineStatus::Ready;
                // Reset buffer address to NULL
                m_pTxBuffer = nullptr;
                // Reset the transmission length to zero
                m_txLen = 0;

                // TODO: Call the application callback function with event USART_EVENT_TX_COMPLETE
            }
        }
    }

    /********************Check for TXE flag*****************************/
    // Check the state of TXE (Transmit Data Register Empty) flag in the SR 
    temp1 = m_pUSARTx->SR & (1 << static_cast<uint8_t>(USARTStatusFlags::TransmitDataRegisterEmpty));
    // Check the state of the TXEIE (Transmit Data Register Empty Interrupt Enable) bit in the CR1 
    temp2 = m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::TXEIE));

    // Transmit data register empty interrupt handling. 
    // TXE of SR is set when the content of the TDR register has been transferred into the shift register.
    if (temp1 && temp2) {
        // Check the transmission line state
        if (m_txState == USARTLineStatus::BusyInTx) {
            // Keep sending data until transmission length is zero  
            if (m_txLen > 0) {
                // data send logic based on the word length (8bit or 9bit)
                if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
                    // if 9-bit load the DR with 2 bytes masking the bits other than first 9 bits
                    pData = (uint16_t*) m_pTxBuffer;
                    m_pUSARTx->DR = (*pData & (uint16_t) 0x01ff);

                    // Check for parity bit
                    if (m_usartConfig.m_parity == USARTParity::NONE) {
                        // If there is not parity bit, 9 bits of user data will be sent 
                        // increment the buffer twice
                        m_pTxBuffer++;
                        m_pTxBuffer++;
                        m_txLen -= 2;
                    } else {
                        // If there is a parity bit, 8 bits of user data will be sent
                        // the 9th bit will be replaced by parity bit by the hardware
                        m_pTxBuffer++;
                        m_txLen--;
                    }
                } else {
                    // This is 8 bit data transfer
                    m_pUSARTx->DR = (*m_pTxBuffer & (uint8_t) 0xff);

                    // Increment the buffer address
                    m_pTxBuffer++;
                    m_txLen--;
                }
            }

            if (m_txLen == 0) {
                // transmission length is zero, transmission is complete
                // Clear TXEIE bit (disable the TXE flag)
                m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::TXEIE));
            }
        }
    }    
    /****************************Check for RXNE flag ************************************/
    temp1 = m_pUSARTx->SR & (1 << static_cast<uint8_t>(USARTStatusFlags::ReceiveDataRegisterNotEmtpy));
    temp2 = m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));

    if (temp1 && temp2) {
        // Receive data register not empty interrupt handling
        if (m_rxState == USARTLineStatus::BusyInRx) {
            if(m_rxLen > 0) {
                // Check the word length    
                if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
                    // Check the parity bit
                    if (m_usartConfig.m_parity == USARTParity::NONE) {
                        // If there is no parity bit, all 9 bits are user data
                        // Read only first 9 bits
                        *((uint16_t*) m_pRxBuffer) = m_pUSARTx->DR & (uint16_t) 0x01ff;

                        m_pRxBuffer++;
                        m_pRxBuffer++;
                        m_rxLen -= 2;
                    } else {
                        // Parity bit was used, 8 bits are user data and 1 parity bit
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t) 0xff;
                        m_pRxBuffer++;
                        m_rxLen--;
                    }
                } else {
                    // Receiving 8-bit data in a frame
                    // Need to check the parity bit
                    if (m_usartConfig.m_parity == USARTParity::NONE) {
                        // No parity bit used, all 8 bits are user data
                        // Read 8 bits from DR
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t) 0xff;
                    } else {
                        // Parity bit used, 7 bits user data, 1 bit parity
                        // Read 7 bits from DR
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t) 0x7f;
                    }
                    // Increment the buffer address
                    m_pRxBuffer++;
                    m_rxLen--;
                }
            }
            if (!m_rxLen) {
                // Data receive is complete
                // Disable RXNE
                m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));
                m_rxState = USARTLineStatus::Ready;
                applicationEventCallback(USARTAppStatus::RX_COMPLETE);
            }
        }
    }
}