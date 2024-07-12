#pragma once

#include "stm32f407xx.h"    

namespace stm32f407 {

    enum class USARTMode : uint8_t {
        TX,
        RX,
        TX_RX
    };

    enum class USARTBaud : uint32_t {
        BAUD_1200 = 1200,
        BAUD_2400 = 2400,
        BAUD_9600 = 9600,
        BAUD_19200 = 19200,
        BAUD_38400 = 38400,
        BAUD_57600 = 57600,
        BAUD_115200 = 115200,
        BAUD_230400 = 230400,
        BAUD_460800 = 460800,
        BAUD_921600 = 921600,
        BAUD_2M = 2000000,
        BAUD_3M = 3000000
    };

    enum class USARTParity : uint8_t {
        NONE,
        EVEN,
        ODD
    };

    enum class USARTWordLength : uint8_t {
        EIGHT_BITS,
        NINE_BITS
    };  

    enum class USARTStopBits : uint8_t {
        ONE,
        HALF,
        TWO,
        ONE_HALF
    };

    enum class USARTFlowControl : uint8_t {
        NONE,
        RTS,
        CTS,
        RTS_CTS
    };

    enum class USARTStatusFlags : uint8_t {
        ParityError = 0x0U,
        FramingError = 0x1U,
        NoiseFlag = 0x2U,
        OverrunError = 0x3U,
        IdleDetected = 0x4U,
        ReceiveDataRegisterNotEmtpy = 0x5U,
        TransmissionComplete = 0x6U,
        TransmitDataRegisterEmpty = 0x7U,
        LINBreak = 0x08U,
        CTSFlag = 0x9U,
    };
    
    enum class USARTCR1Bit : uint8_t {
        SBK = 0,
        RWU = 1,
        RE = 2,
        TE = 3,
        IDLEIE = 4,
        RXNEIE = 5,
        TCIE = 6,
        TXEIE = 7,
        PEIE = 8,
        PS = 9,
        PCE = 10,
        WAKE = 11,
        M = 12,
        UE = 13,
        OVER8 = 15
    };

    enum class USARTCR2Bit : uint8_t {
        ADD = 0,
        LBDL = 5,
        LBDIE = 6,
        LBCL = 8,
        CPHA = 9,
        CPOL = 10,
        CLKEN = 11,
        STOP = 12,
        LINEN = 14
    };

    enum class USARTCR3Bit : uint8_t {
        EIE = 0,
        IREN = 1,
        IRLP = 2,
        HDSEL = 3,
        NACK = 4,
        SCEN = 5,
        DMAR = 6,
        DMAT = 7,
        RTSE = 8,
        CTSE = 9,
        CTSIE = 10,
        ONEBIT = 11
    };

    enum class USARTAppStatus : uint8_t {
        BUSY_IN_RX,
        BUSY_IN_TX,
        TX_COMPLETE,
        RX_COMPLETE,
        IDLE,
        CTS,
        ERR_PE,
        ERR_FE,
        ERR_NE,
        ERR_ORE
    };


    enum class USARTLineStatus : uint8_t {
        BusyInRx,
        BusyInTx,
        Ready,
    };  

   // Peripheral clock setup
    class USARTConfig {
        public:
            volatile USARTMode m_mode;
            volatile USARTBaud m_baud;
            volatile USARTStopBits m_stopBits;
            volatile USARTWordLength m_wordLength;
            volatile USARTParity m_parity;
            volatile USARTFlowControl m_flowControl;
            USARTConfig() = default;
            USARTConfig(
                USARTMode mode,
                USARTBaud baud,
                USARTStopBits stopBits,
                USARTWordLength wordLength,
                USARTParity parity,
                USARTFlowControl flowControl
            ): m_mode(mode), 
               m_baud(baud), 
               m_stopBits(stopBits), 
               m_wordLength(wordLength), 
               m_parity(parity), 
               m_flowControl(flowControl) {}
    };

    class USARTHandle {
        private:
            USARTRegDef* m_pUSARTx;
            USARTConfig m_usartConfig;
            uint8_t* m_pTxBUffer;
            uint8_t* m_pRxBUffer;
            uint32_t m_txLen;
            uint32_t m_rxLen;
            USARTLineStatus m_txSate;
            USARTLineStatus m_rxSate;

            void periClockControl(ClockStatus status);

            // USART status flags API
            BitStatus getFlagStatus(USARTStatusFlags statusFlag);
            void clearFlag(USARTStatusFlags statusFlag); 
            
        public:
            USARTHandle() = default;
            USARTHandle(USARTRegDef* usartRegDef, const USARTConfig& usartConfig): m_pUSARTx(usartRegDef), m_usartConfig(usartConfig) {};

            void init();    
            // void deInit();  
            
            void sendData(uint8_t* pTxBuffer, uint32_t txLength);
            void receiveData(uint8_t* pRxBuffer, uint32_t rxLength);

            // Other peripheral control APIs    
            void peripheralControl(bool enable);   
            void setBaudRate();

            void irqHandler();    
            void receiveDataWithInterrupt(uint8_t* pRxBuffer, uint32_t rxLength);
            void sendDataWithInterrupt(uint8_t* pTxBuffer, uint32_t txLength);
        
    };

}