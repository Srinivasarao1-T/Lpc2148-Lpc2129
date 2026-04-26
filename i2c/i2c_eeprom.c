#include "types.h"
#include "i2c.h"
#include "i2c_defines.h"
#include "delay.h"
void i2c_eeprom_bytewrite(u8 slaveaddr,u16 wbuffaddr,u8 wbyte)
{
	i2c_start();
	i2c_write(slaveaddr<<1);//sa+w;
	i2c_write(wbuffaddr>>8);
	i2c_write(wbuffaddr);
	i2c_write(wbyte);
	i2c_stop();
	delay_ms(10);
}
u8 i2c_eeprom_randomread(u8 slaveaddr,u16 rbuffaddr)
{
	u8 rbyte;
	i2c_start();
	i2c_write(slaveaddr<<1);//sa+w;
	i2c_write(rbuffaddr>>8);
	i2c_write(rbuffaddr);
	i2c_reset();
	i2c_write((slaveaddr<<1)|1);//sa+r;
	rbyte=i2c_nack();
	i2c_stop();
	return rbyte;
}
void i2c_eeprom_pagewrite(u8 slaveaddr,u16 wbuffaddr,u8 *pbyte,u8 nbyte)
{ 
	u32 i;
	i2c_start();
	i2c_write(slaveaddr<<1);//sa+w;
	i2c_write(wbuffaddr>>8);
	i2c_write(wbuffaddr);
	for(i=0;i<nbyte;i++){
	i2c_write(pbyte[i]);
	}
	i2c_stop();
	delay_ms(10);
}
void i2c_eeprom_seqread(u8 slaveaddr,u16 rbuffaddr,u8 *pbyte,u8 nbyte)
{ 
	u32 i;
	i2c_start();
	i2c_write(slaveaddr<<1);//sa+w;
	i2c_write(rbuffaddr>>8);
	i2c_write(rbuffaddr);
	i2c_reset();
	i2c_write((slaveaddr<<1)|1);
	for(i=0;i<(nbyte-1);i++){
	pbyte[i]=i2c_mack();
	}
	pbyte[i]=i2c_nack();
	i2c_stop();
	delay_ms(10);
}


