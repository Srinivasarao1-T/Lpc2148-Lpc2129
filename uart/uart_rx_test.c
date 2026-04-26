#include<lpc21xx.h>
#include "uart.h"
#include "delay.h"
main()
{
	init_UART0();
	IODIR0|=1<<4;
	while(1)
	{
		if(u0_rxbyte()=='A')
		{
			IOPIN0^=1<<4;
		}
	}
}
