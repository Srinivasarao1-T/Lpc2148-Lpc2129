#include<lpc21xx.h>
const unsigned int  arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int aa[2],i,a;
unsigned int dp2;
void delay_ms(unsigned int dyms)
{
     for(dyms*=12000;dyms>0;dyms--);
 }
 float f=0.0;
main()
{
  
  IODIR0|=(255<<6)|(1<<5)|(1<<4);
 
  while(1)
  {
  	 if(f>=9.9)
	 {
	    f=0.0;
	 }
   
	 
	 }
}
