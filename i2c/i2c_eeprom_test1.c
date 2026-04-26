#include <lpc21xx.h>

#include "i2c_defines.h"
#include "i2c_eeprom.h"
#include "i2c.h"
#include "delay.h"
u8 rbyte,rbytes[8];
main()
{
	IODIR1|=1<<16;
	init_i2c();
	i2c_eeprom_bytewrite(I2C_EEPROM_SA,0X7F,'A');
	rbyte=i2c_eeprom_randomread(I2C_EEPROM_SA,0X7F);
	if(rbyte=='A'){ IOPIN1^=1<<16;
	}
	delay_ms(1000);
IOPIN1^=1<<16;
	i2c_eeprom_pagewrite(I2C_EEPROM_SA,0X00,"123456",6);
	i2c_eeprom_seqread(I2C_EEPROM_SA,0X00,rbytes,6);
	while(1);
}
