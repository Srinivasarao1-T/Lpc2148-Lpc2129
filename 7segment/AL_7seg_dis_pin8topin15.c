#include<lpc21xx.h>
const unsigned int  arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int i;
 void delay_ms(unsigned int delayms)
 {
       delayms*=12000;                   //1ms
           while(delayms--);
 }
main()
{
     IODIR0|=~(255<<8);
	 for(i=0;i<10;i++){
	   IOPIN0=(IOPIN0&(~(255<<8)))|(arr[i]<<8);
	   delay_ms(100);
	 }
	 while(1);
}
