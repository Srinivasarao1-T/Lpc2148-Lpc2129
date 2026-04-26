#include<lpc21xx.h>
#include "delay.h"
#include "adc.h"
#include "lcd_define.h"
#include "lcd.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "types.h"
#include "kpm.h"
#include<string.h>
#define REDLED 2
#define GREENLED 3
#define ADMIN_SW 1
#define USER_SW 0
typedef struct 
{ 
   char name[6];
   char userid[6];
   int num;
   int inhr;
   int inmin;
   int outhr;
   int outmin;   	   
}obj;
void timechange(s32 *h,s32 *m,s32 *s)
{
	 u32 sum;
	 u8 key;	  
	   strLCD("enter time");
 hrs:sum=key=0;
       readNUM(&sum,&key);
        if(!(sum>=0&&sum<=23)==0)
		{
		cmdLCD(0xc0);
		strLCD("wrong input");
		goto hrs; 
		}
	    HOUR=sum;
		*h=sum;
 min:  sum=key=0;
       readNUM(&sum,&key);
        if(!(sum>=0&&sum<=59)==0)
		{
		cmdLCD(0xc0);
		strLCD("wrong input");
		goto min; 
		}
	    MIN=sum;
		*m=sum;
sec:sum=key=0;
       readNUM(&sum,&key);
        if(!(sum>=0&&sum<=59)==0)
		{
		cmdLCD(0xc0);
		strLCD("wrong input");
		goto sec; 
		}
	     SEC=sum;
		 *s=sum;
}
int checkleap(u32 n)
{
    if(n%4==0)
	{
	    if(n%400==0)
		{
		 return 1;
		}
		if(n%100==0)
		{
		   return 0;
		}
		  return 1;
	}
	return 0;
}
void changedate(u32 *day,u32 *mon,u32 *yr)
{
	u32 sum;
	 u8 key;
	 u32 flag=0,flag2;
	 cmdLCD(0x80);	  
	   strLCD("enter the year");
       sum=key=0;
       readNUM(&sum,&key);
        if(checkleap(sum))
		{
		 flag=1;
		}
	    YEAR=sum;
		*yr=sum;
m:		 cmdLCD(0x80);	  
	   strLCD("enter the month");
        sum=key=0;
        readNUM(&sum,&key);
		if(!(sum>=1&&sum<=12)==0)
		{
		       cmdLCD(0xc0);
		       strLCD("wrong input");
			   delay_ms(500);
		       goto m;
		}
		MONTH=sum;
		*mon=sum;if((*mon==1)||(*mon==3)||(*mon==5)||(*mon==7)||(*mon==8)||(*mon==10)||(*mon==12)) 
	   {
	       flag2=31;
	   }
	    if((*mon==4)||(*mon==6)||(*mon==9)||(*mon==11)) 
	   {
	        flag2=30;
	   }
	   if((*mon==2)&&flag==1)
	   {
	        flag2=29;
	   }
	  else{
	  flag2=28;
	  }
d: 	   cmdLCD(0x80);	  
	   strLCD("enter the month");
        sum=key=0;
        readNUM(&sum,&key);
	        if(!(sum>=1&&sum<=flag2)==0)
			{
			  	   cmdLCD(0xc0);
		       strLCD("wrong input");
			   delay_ms(500);
			   goto d;
			}
			DOW=sum;
			*day=sum;
}
void  changebund(int a,obj *arr){ 
            u32 sum;
			u8 key,flag=0;
            cmdLCD(CLEAR_LCD);
            cmdLCD(GOTO_LINE1_POS0);
		    strLCD("enter the inhr ");
	one:	sum=key=0;
			readNUM(&sum,&key);
			if(sum>=0&&sum<=23)
			arr[a].inhr=sum;
			else {cmdLCD(0xc0);strLCD("invalidoption");goto one;};
			delay_ms(500);
			cmdLCD(0x80);
			strLCD("enter the inmin");
	two:		sum=key=0;
			readNUM(&sum,&key);
			if(sum>=0&&sum<=59)
			arr[a].inmin=sum;
			else {cmdLCD(0xc0);strLCD("invalidoption");goto two;};
			delay_ms(500);
			cmdLCD(0x80);
			strLCD("enter the outhr ");
   three:	sum=key=0;
			readNUM(&sum,&key);
		    if((sum>=arr[a].inhr)&&sum<=23)
			arr[a].outhr=sum;
			else {cmdLCD(0xc0);strLCD("invalidoption");goto three;};
			if(sum==arr[a].inhr) flag=1;
			delay_ms(500);
			strLCD("enter the outmin");
   four:	sum=key=0;
            if(flag==1){
				 if((sum>=arr[a].inmin)&&(sum<=59))
				 {
				     		arr[a].outmin=sum;
				 }
				 else {cmdLCD(0xc0);strLCD("invalidoption");goto four;};
			}
			else{ 
			if(sum>=0&&sum<=59)
			arr[a].outmin=sum;
			else {cmdLCD(0xc0);strLCD("invalidoption");goto four;};
			}
			delay_ms(500);			
			}   
void timebund(obj *arr)
{
   u32 sum=0;u8 key;
   cmdLCD(CLEAR_LCD);
   cmdLCD(GOTO_LINE1_POS0);
   strLCD("1.u1 2.u2 3.u3");
   readNUM(&sum,&key);
   switch(sum)
   {
     case 1:changebund(0,arr);break;
	 case 2:changebund(1,arr);break;           
	 case 3:changebund(2,arr);break;
	 default:strLCD("invalid option");
   }
}
main()
{
int i;
s32  hour,min,sec;
u32 day,mon;
u32 yr;
u16 dval;
u32 sum;
u8 key;
f32 ear;
char p[10];
obj arr[4]={{"User1","1111",1234,9,0,11,0},{"User2","2222",2345,12,0,14,0},{"User3","3333",3456,15,0,17,0},{"Admin","AAAA",5555,0,0,0,0}};
initLCD();
Init_ADC();
RTC_Init();
IODIR0|=1<<ADMIN_SW|1<<USER_SW|1<<REDLED|1<<GREENLED;
//SetRTCTimeInfo(14,56,0);
//SetRTCDateInfo(6,5,2025);
//SetRTCDay(4);
office:HOUR=hour;MIN=min;SEC=sec; 
READ_ADC(1,&dval,&ear);
cmdLCD(GOTO_LINE1_POS0);
//strLCD("temp: ");
f32LCD(ear,3);
DisplayRTCTime(hour,min,sec);
DOW=day;MONTH=mon;YEAR=yr;
cmdLCD(GOTO_LINE2_POS0);
DisplayRTCDate(day,mon,yr);
delay_ms(1);
while(1){
		 if(((IOPIN0>>ADMIN_SW)&1)==0)
		 { 
		    while(((IOPIN0>>ADMIN_SW)&1)==0);
		    goto label;
		 }
		 if(((IOPIN0>>USER_SW)&1)==0)
		 {
		    while(((IOPIN0>>USER_SW)&1)==0);
		    goto label1; 
		 }
}	                                                
label1:		 while(1){ 
		     readSTR(p);
			 readNUM(&sum,&key);
			 for(i=0;i<3;i++)
			 {
			      if(strcmp(arr[i].userid,p)==0)
				  {
				   if(sum==arr[i].num)
				   { 
				      if(((HOUR>=arr[i].inhr)&&(HOUR<=arr[i].outhr))&&((MIN>=arr[i].inmin)&&(MIN<=arr[i].outmin))){
				       cmdLCD(GOTO_LINE2_POS0);
				       strLCD(" login is sucess ");
					   IOSET0=1<<GREENLED;
					   delay_s(1);
					   IOCLR0=1<<GREENLED;
					   goto office;
					   }
					   else{
				       cmdLCD(GOTO_LINE1_POS0);
				       strLCD(" time_bounded ");
				         break;
					   }
				   }
				  }
			 }
			 IOSET0	=1<<REDLED;
			 cmdLCD(GOTO_LINE2_POS0);
			 if(i==3) strLCD("LOGIN FAIL");
			 delay_s(1);
			 IOCLR0=1<<REDLED;
			 goto office;                                             
         }
label:	     sum=0;key=2;
             readSTR(p);
			 readNUM(&sum,&key);
			 for(i=0;i<3;i++)
			 {		    
			      if(strcmp(arr[i].userid,p)==0)
				  {
				   if(sum==arr[i].num)
				   { 
				       cmdLCD(GOTO_LINE2_POS0);
				       strLCD(" login is sucess ");
					   IOSET0=1<<GREENLED;
					   delay_s(1);
                       IOCLR0=1<<GREENLED;   
					    goto time;
				   }
				  }
			 }
			 IOSET0	=1<<REDLED;
			 if(i==3) strLCD("LOGIN FAIL");
			 delay_s(1);
			 IOCLR0=1<<REDLED;
			 goto office;
time:  cmdLCD(CLEAR_LCD);
       cmdLCD(GOTO_LINE1_POS0);
       strLCD("1.time");
	   cmdLCD(GOTO_LINE2_POS0);
       strLCD("2.time_boundries");
	   delay_ms(500);
	   key=sum=0;
	   readNUM(&sum,&key);       
       switch(sum)
	   {  case 1:timechange(&hour,&min,&sec);
	             changedate(&day,&mon,&yr); 
				 goto office;
	      case 2:timebund(arr);
		         goto office;
		  default:cmdLCD(CLEAR_LCD);
                  cmdLCD(GOTO_LINE1_POS0);
		          strLCD("wrong option");
				  goto time;
	   }
}
