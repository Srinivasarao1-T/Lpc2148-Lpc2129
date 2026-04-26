#include <LPC21xx.Hs>
const unsigned int  arr[4]={0x89,0x86,0xc7,0x8c};
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
        for(ten=0;ten<6;ten++)
		{
		    for(one=0;one<=9;one++)
			{
			           for(a=250;a>0;a--){
			           IOPIN0=(IOPIN0&~(255<<6))|(arr[0]<<6);
			    	   IOSET0=1<<5;
					   delay_ms(1);
					   IOCLR0=1<<5;
					   IOPIN0=(IOPIN0&~(255<<6))|(arr[1]<<6);
					   IOSET0=1<<4;
					   delay_ms(1);
					   IOCLR0=1<<4;	
					   }
					   for(a=250;a>0;a--){
			           IOPIN0=(IOPIN0&~(255<<6))|(arr[2]<<6);
			    	   IOSET0=1<<5;
					   delay_ms(1);
					   IOCLR0=1<<5;
					   IOPIN0=(IOPIN0&~(255<<6))|(arr[3]<<6);
					   IOSET0=1<<4;
					   delay_ms(1);
					   IOCLR0=1<<4;	
					   }
			}
		}	     
	}
}
