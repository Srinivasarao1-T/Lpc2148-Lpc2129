#include<lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_define.h"
#include "kpm.h"
main()
{
 initLCD();
 strLCD(" KPMTEST ");
 while(1)
 {
 cmdLCD(GOTO_LINE2_POS0);
 u32LCD(keySCAN());
 delay_ms(100);
 while(colSCAN()==0);
 cmdLCD(GOTO_LINE2_POS0);
 strLCD(" ");
 }
}
