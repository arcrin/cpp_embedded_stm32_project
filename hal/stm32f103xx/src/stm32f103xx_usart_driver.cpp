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
            break;
        case ClockStatus::DISABLE:
            if (m_pUSARTx == USART1) {
                disableUSART1Clock();
            } else if (m_pUSARTx == USART2) {
                disableUSART2Clock();
            } else if (m_pUSARTx == USART3) {
                disableUSART3Clock();
            }
            break;
    }
}

void USARTHandle::init() {
    periClockControl(ClockStatus::ENABLE);

    // Mode select
    if (m_usartConfig.m_mode == USARTMode::RX) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::RE));
    } else if (m_usartConfig.m_mode == USARTMode::TX) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::TE));
    } else if (m_usartConfig.m_mode == USARTMode::TX_RX) {
        m_pUSARTx->CR1 = m_pUSARTx->CR1 | ((1 << static_cast<uint8_t>(USARTCR1Bit::RE)) | (1 << static_cast<uint8_t>(USARTCR1Bit::TE)));
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
    usartDiv = ((25 * peripheralClock) / (4 * static_cast<uint32_t>(m_usartConfig.m_baud))); 
    

    mantissa = usartDiv / 100;

    // place the mantissa part in appropriate bit position
    tempreg |= mantissa << 4;

    fraction = (usartDiv - (mantissa * 100));   

    // calculate the final fraction
    fraction = (((fraction * 16) + 50) / 100) & (uint8_t)0x0F;

    // Place the fraction part in appropriate bit position.
    tempreg |= fraction;

    // copy the value of tempreg in to BRR register
    m_pUSARTx->BRR = tempreg;
}

void USARTHandle::sendData(uint8_t* pTxBuffer, uint32_t txLength){
    uint16_t pData;
    for (uint32_t i = 0; i < txLength; i++) {
        // wait for the transmission data register becomes empty
        while(!static_cast<uint8_t>(getFlagStatus(USARTStatusFlags::TransmitDataRegisterEmpty)));
        if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
            pData = *((uint16_t*)pTxBuffer);
            m_pUSARTx->DR = pData & (uint16_t)0x01FF;

            // check if parity control is enabled
            if (m_usartConfig.m_parity == USARTParity::NONE) {
                pTxBuffer++;
                pTxBuffer++;
            } else {
                pTxBuffer++;
            }
        } else {
            m_pUSARTx->DR = *pTxBuffer;
            pTxBuffer++;
        }
        while (!static_cast<uint8_t>(getFlagStatus(USARTStatusFlags::TransmissionComplete)));   
    }
}

BitStatus USARTHandle::getFlagStatus(USARTStatusFlags statusFlag) {
    if(m_pUSARTx->SR & (1 << static_cast<uint8_t>(statusFlag))) {
        return BitStatus::SET;
    }
    return BitStatus::CLEAR;
}

void USARTHandle::clearFlag(USARTStatusFlags statusFlag) {
    m_pUSARTx->SR = m_pUSARTx->SR & ~(1 << static_cast<uint8_t>(statusFlag));
}

void USARTHandle::receiveDataWithInterrupt(uint8_t* pRxBuffer, uint32_t rxLength) {
    // USARTLineStatus rxState = m_rxState;
    // if (rxState != USARTLineStatus::BusyInRx) {
    //     m_rxLen = rxLength;
    //     m_pRxBuffer = pRxBuffer;
    //     m_rxState = USARTLineStatus::BusyInRx;
    //     (void) m_pUSARTx->DR;
    //     m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));
    // }
    // return rxState;
    m_rxLen = rxLength;
    m_pRxBuffer = pRxBuffer;    
    m_rxState = USARTLineStatus::BusyInRx;
    (void) m_pUSARTx->DR;
    m_pUSARTx->CR1 = m_pUSARTx->CR1 | (1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));
}

void USARTHandle::irqHandler(){
    uint32_t temp1, temp2;
    // uint16_t pData;

    /*********************Check for RXNE flag*********************************/
    temp1 = m_pUSARTx->SR & (1 << static_cast<uint8_t>(USARTStatusFlags::ReceiveDataRegisterNotEmtpy));
    temp2 = m_pUSARTx->CR1 & (1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));

    if (temp1 && temp2) {
        if (m_rxState == USARTLineStatus::BusyInRx) {
            if (m_rxLen > 0) {
                // check for word length
                if (m_usartConfig.m_wordLength == USARTWordLength::NINE_BITS) {
                    // check the parity bit
                    if (m_usartConfig.m_parity == USARTParity::NONE) {
                        *((uint16_t*)m_pRxBuffer) = m_pUSARTx->DR & (uint16_t)0x01ff;
                        m_pRxBuffer++;
                        m_pRxBuffer++;
                        m_rxLen -= 2;
                    } else {
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t)0xff;
                        m_pRxBuffer++;
                        m_rxLen--;
                    }
                } else {
                    // 8-bit data
                    if (m_usartConfig.m_parity == USARTParity::NONE) {
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t)0xff;
                    } else {
                        *m_pRxBuffer = m_pUSARTx->DR & (uint8_t)0x7f;
                    }
                    m_pRxBuffer++;
                    m_rxLen--;
                }
            }
            if (!m_rxLen) {
                // data receive is complete
                // disable RENE interrupt
                m_pUSARTx->CR1 = m_pUSARTx->CR1 & ~(1 << static_cast<uint8_t>(USARTCR1Bit::RXNEIE));
                m_rxState = USARTLineStatus::Ready;
                applicationEventCallback(USARTAppStatus::RX_COMPLETE);
            
            }
        }
    }
    
}