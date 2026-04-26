#include<lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "lcd_define.h"
#include "delay.h"
#include "kpm.h"
main()
{
 u32 num=0;
 u8 key=0;
 initLCD();
 strLCD(" KPMTEST ");
 while(1)
 {
  readNUM(&num,&key);
  cmdLCD(GOTO_LINE2_POS0);
  u32LCD(num);
  delay_s(1);
 }
}
