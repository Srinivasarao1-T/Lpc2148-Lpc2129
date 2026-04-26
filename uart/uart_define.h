#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR  (PCLK/(16*BAUD))
//define for uxLCR
#define _8_BITS 3
#define WORD_LEN_SEL _8_BITS
#define DLAB_BIT 7
#define U0_TX_INT_EN 1
#define U0_RX_INT_EN 1
#define DR_BIT 0
#define TEMP_BIT 6
#define TXD0_PIN 1
#define RXD0_PIN 1
//URAT UXIER
#define EN_RDA_INT_BIT 0
#define EN_THRE_INT_BIT 1
//DEFINE FOR UCIIR
#define RDA_STATUS 2
#define THRE_STATUS 1
#define VIC_UART0_CHNO 6
#define U0_TX_INT_STATUS_PIN 16
#define U0_RX_INT_STATUS_PIN 17

