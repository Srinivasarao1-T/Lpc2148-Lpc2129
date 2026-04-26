#include<lpc21xx.h>			   0
#include "types.h"
#include "delay.h"
#include "uart.h"
extern int flag;
extern u8 buff;
u8 p[10]="finish";
int pt;
int cnt=0;
void  u0_str(u8 *p)
{
      while(*p)
	    u0_txbyte(*p++);
}
main()
{
	init_UART0();
	while(1)
	{
	//	buff='\0';
	while(flag==0);
	flag=0;
	//delay_ms(100);
	/*if(buff=='\n')
	{
	break;
	} */
	if(cnt==5)
	{							     
	       u0_txbyte('\n');
	       u0_str(p);
	       break;
	}
	U0THR=buff;
	cnt++;

	//U0THR=0;

	}
	while(1)
	{
	  	while(flag==0);
	flag=0;
	//delay_ms(100);
	if(buff=='\r')
	{
	break;
	}            
	if(buff=='\n')
	{								  
	break;
	}

	U0THR=buff;	
	}
	while(1);
}
			  			                                          
											