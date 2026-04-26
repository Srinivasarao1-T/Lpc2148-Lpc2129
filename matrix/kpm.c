#include<lpc21xx.h>
#include "types.h"
#include "delay.h"	
#include "lcd.h"
#include "lcd_define.h"
#include "kpm.h"
#include<strlib.h>
//const u8 kpmLUT[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
//const u8 kpmLUT[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'e','0','=','+'}};
const u8 kpmLUT[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'p','0','=','D'}};
void initKPM()
{
      IODIR1|=(15<<ROW0);
	IOCLR1=15<<ROW0;
}
u32 colSCAN()
{ 
return ((((IOPIN1>>COL0)&15)<15)?0:1);
}
u32 rowCHECK(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		IOPIN1=(IOPIN1&~(15<<ROW0))|(~(1<<r)<<ROW0);
		if(colSCAN()==0)
		{
			break;
		}
	}
	IOCLR1=15<<ROW0;
	return r;
}
u32 colCHECK()
{
		 u32 c;
		 for(c=0;c<=3;c++)
		 {
		     if(((IOPIN1>>(COL0+c))&1)==0)
			 {
			   break;
			   }
		 }
		 return c;
}
u32 keySCAN()
{
 u32 r,c;
 static s32 flag ;
 if(flag==0)
 {
    initKPM();
	flag=1;
 }
 while(colSCAN());
 r=rowCHECK();
 c=colCHECK();
 while(!(colSCAN()));
  //delay_ms(50);
 return  kpmLUT[r][c];
  
}
void readNUM(u32 *sum,u8 *key)
{
u8 flag=0,cnt=0;
if(key==2)
{
 flag=1;
}
cmdLCD(GOTO_LINE2_POS0);
while(1)
{
    *key=keySCAN();
	//delay_ms(200);
	if((*key>='0')&&(*key<='9'))
	{
	charLCD(*key);
	if(flag==1)
	{
	delay_ms(50);
	cmdLCD(GOTO_LINE2_POS0+cnt);
	charLCD('*');
	cnt++;
	}
	*sum=(*sum*10)+(*key-48);
	//while(colSCAN()==0);
	}
	else{
	//while(colSCAN()==0);
	break;
	}
}
void readSTR(char *p)
{
  u8 key,i;
  i=0;
  cmdLCD(GOTO_LINE2_POS0);
  while(1){
  key=keySCAN(); 
  if((key>='0'&&key<='9')||(key<='A'&&key>='D'))
  {
     charLCD(key);
	p[i++]=key;
  }
  else{
   p[i]='\0';
       break;
     } 
  }
}
}
