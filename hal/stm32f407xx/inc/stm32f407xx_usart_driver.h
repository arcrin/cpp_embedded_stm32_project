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

    enum class USARTFlags : uint8_t {
        TXE = 0x7U,
        TC = 0x6U,
        RXNE = 0x5U,
        IDLE = 0x4U,
        ORE = 0x3U,
        NF = 0x2U,
        FE = 0x1U,
        PE = 0x0U
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

    /**********************************
    * API
    ***********************************/
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
            // uint8_t* pTxBUffer;
            // uint8_t* pRxBUffer;
            // uint32_t txLen;
            // uint32_t rxLen;
            // bool txBusySatte;
            // bool rxBusySatte;

            void periClockControl(ClockStatus status);
        public:
            USARTHandle() = default;
            USARTHandle(USARTRegDef* usartRegDef, const USARTConfig& usartConfig): m_pUSARTx(usartRegDef), m_usartConfig(usartConfig) {};

            void init();    
            // void deInit();  
            
            void sendData(uint8_t* pTxBuffer, uint32_t txLength);
            void receiveData(uint8_t* pRxBuffer, uint32_t rxLength);

            // Other peripheral control APIs    
            uint8_t getFlagStatus(uint8_t statusFlagBit);
            void clearFlag(uint8_t statusFlagBit); 
            void peripheralControl(bool enable);   
            void setBaudRate();
        
    };

}