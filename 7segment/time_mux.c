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
void segment7time(void);
int main()
{
    IODIR0|=(255<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2);

	while(1)
	{
        segment7time();
	}
}
 void segment7time()
 {		    
    int a[4]={0};
	int min=0,d,i,sec=0,str;
     for(;sec<60;)
	 {
	   a[0]=min/10;
	   a[1]=min%10;
	   a[2]=sec/10;
	   a[3]=sec%10;
	   for(i=0;i<4;i++)
	   {
	     if (i==1)
		 {
		     str=0x7f;
		 }
		 else
		 { 
		  str=0xff;
		 }
		 for(d=50;d>0;d--){
		 IOPIN0=(IOPIN0&~(255<<6))|((arr[a[i]]&str)<<6);
		 IOSET0=1<<5-i;
		 delay_ms(1);
		 IOCLR0=1<<5-i;
		 }
		 sec++;
		 if(sec==60)
		 {   
		   	 sec=0;
			 min++;
			 if(min==60)
			 {
			 min=0;
			 }
		 }
	   }
	 }	       
 }
