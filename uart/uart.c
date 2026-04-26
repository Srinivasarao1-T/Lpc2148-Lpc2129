#include<lpc21xx.h>
#include "types.h"
#include "uart_define.h"
#include "uart.h"
int flag;
u8 buff;
void init_UART0()
{
	PINSEL0=(PINSEL0&~(3<<(0*2))|(TXD0_PIN<<0*2));
	PINSEL0=(PINSEL0&~(3<<(1*2))|(RXD0_PIN<<1*2));
	U0LCR=((1<<DLAB_BIT)|WORD_LEN_SEL);
	U0DLL=DIVISOR;
	U0DLM=DIVISOR>>8;
	U0LCR&=~(1<<DLAB_BIT);
#if U0_TX_INT_EN > 0
	U0IER|=1<<EN_THRE_INT_BIT;
#endif
#if U0_RX_INT_EN > 0
	U0IER|=1<<EN_RDA_INT_BIT;
#endif
#if (U0_TX_INT_EN > 0) ||(U0_RX_INT_EN > 0)
	VICIntEnable=1<<VIC_UART0_CHNO;
	VICVectCntl0=1<<5|VIC_UART0_CHNO;
	VICVectAddr0=(u32) u0_isr;
	IODIR0|=(1<<U0_TX_INT_STATUS_PIN);
#endif


}
void u0_txbyte(u8 SBYTE)
{
    U0THR=SBYTE;
    while(((U0LSR>>TEMP_BIT)&1)==0);
}
u8 u0_rxbyte()
{
	while(((U0LSR>>DR_BIT)&1)==0);
        return U0RBR;
	
}
void u0_isr() __irq
{
	u8 stat,d;
	//stat=U0IIR;
	stat=((U0IIR>>1)&7);
/*	if(stat==THRE_STATUS)
	{ 
	IOPIN1 ^=1<<U0_TX_INT_STATUS_PIN;
	flag=1;
	}*/
	if(stat==RDA_STATUS)
	{ IOPIN1 ^=1<<U0_RX_INT_STATUS_PIN;
	buff=U0RBR;
	flag=1;
	}
	else
	d=U0IIR;
	VICVectAddr=0;
}
