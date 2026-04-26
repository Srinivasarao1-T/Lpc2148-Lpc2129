#include <LPC21xx.H>
#include<stdlib.h>
const unsigned int  arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void delay_ms(unsigned int delayms)
{
   delayms*=12000;
   while(delayms--);
}
void delay_s(unsigned int delays)
{
   delays*=12000000;
   while(delays--);
}
int main()
{
int seed,res,a;
    IODIR0|=(255<<6)|(1<<5)|(1<<4);

	while(1)
	{
      				   if(((IOPIN0>>0)&1)==0)
					   {
					    srand(seed++);
						res=(rand()%6)+1;
			           for(a=250;a>0;a--){
			           IOPIN0=(IOPIN0&~(255<<6))|(arr[0]<<6);
			    	   IOSET0=1<<5;
					   delay_ms(1);
					   IOCLR0=1<<5;
					   IOPIN0=(IOPIN0&~(255<<6))|(arr[res]<<6);
					   IOSET0=1<<4;
					   delay_ms(1);
					   IOCLR0=1<<4;
					   }
					   }	
					   	     
	}
}
