#include<lpc21xx.h>
const unsigned int  arr[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int aa[2];
int i,a;
unsigned int dp2;
void delay_ms(unsigned int dyms)
{
     for(dyms*=12000;dyms>0;dyms--);
 }
main()
{
  float f=0;
  IODIR0|=(255<<6)|(1<<5)|(1<<4);
 
  while(1)
  {
  	 if(f==9.9)
	 {
	    f=0.0;

	 }
   aa[0]=((int)(f*10)/10);
	  aa[1]=((int)(f*10)%10);
  f=f+0.1;
        for(a=250;a>0;a--){
		for(i=0;i<=1;i++)
		{
		if(i==0)
		{
		dp2=0x7f;
		}
		else{
		dp2=0xff;
		}
	    IOPIN0=(IOPIN0&~(255<<6))|((arr[aa[i]]&dp2)<<6);
	    IOSET0=1<<4+i;
		delay_ms(1);
	    IOCLR0=1<<4+i;
	  }	
	 }
	 
	 }
}
