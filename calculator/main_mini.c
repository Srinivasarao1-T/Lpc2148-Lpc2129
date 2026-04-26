#include<lpc21xx.h>
#include "delay.h"
#include "lcd_define.h"
#include "lcd.h"
#include "types.h"
#include "kpm.h"
main()
{
u32 sum,res=0,flag=0;
u8 key;
initLCD();
while(1)
{  sum=key=0;
    //u32LCD(555);
	//delay_s(5);
   readNUM(&sum,&key);
   if(key=='e')
   {
      break;
   }
   charLCD(key);
   if((key=='+'||key=='-')&&flag==0)
   {
   flag=1;
   res=0;
   }
   if((key=='*'||key=='/')&&flag==0)
   {
   flag=1;
   res=1;
   }   
   delay_ms(500);
   switch(key)
   {  
        case '+':res+=sum;
		         break;
	    case '-':res-=sum;
		         break;
		case '/':res/=sum;
		         break;
		case '*':res*=sum;
		         break;
		case '=':res=res;
		         break;
   }
   cmdLCD(0x01);
   cmdLCD(0x80);
   strLCD("RESULT");
   cmdLCD(GOTO_LINE2_POS0); 
   u32LCD(res);
   delay_s(2);
}
cmdLCD(0);
while(1); 		 
}
