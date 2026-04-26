#include <LPC21xx.H>
 const unsigned int  arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int ten=0,one=0;
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
int a;
    IODIR0|=(255<<6)|(1<<5)|(1<<4);

	while(1)
	{
        for(ten=0;ten<=9;ten++)
		{
		    for(one=0;one<=9;one++)
			{
			           for(a=250;a>0;a--){
			           IOPIN0=(IOPIN0&~(255<<6))|(arr[ten]<<6);
			    	   IOSET0=1<<5;
					   delay_ms(1);
					   IOCLR0=1<<5;
					   IOPIN0=(IOPIN0&~(255<<6))|(arr[one]<<6);
					   IOSET0=1<<4;
					   delay_ms(1);
					   IOCLR0=1<<4;	
					   }
			}
		}	     
	}
}
