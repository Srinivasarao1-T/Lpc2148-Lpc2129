#include "types.h"
void init_UART0(void);
void u0_txbyte(u8);
u8  u0_rxbyte(void);
void u0_isr(void) __irq;
