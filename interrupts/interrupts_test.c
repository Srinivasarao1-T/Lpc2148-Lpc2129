#include <lpc21xx.h>
#include "delay.h"
#define  PIN_FUNC1 0;
#define	 PIN_FUNC4 3;
#define  GPIO_0_1 PINFUN1
#define  EINT0_PIN_0_1 PIN_FUNC4
#define  EINT0_VIC_CHNO 14
#define  EINT0_STATUS_LED 16
#define  EINT1_PIN_0_3 PIN_FUNC4
#define  EINT1_VIC_CHNO 15
#define  EINT1_STATUS_LED 17
#define  EINT2_PIN_0_7 PIN_FUNC4
#define  EINT2_VIC_CHNO 16
#define  EINT2_STATUS_LED 18
void eint0_fiq_isr(void) __irq;
void eint1_virq_isr(void) __irq;
void eint2_nvirq_isr(void) __irq;
unsigned int var;
main()
{
	//cfg port pin po.1 p0.3 p0.7 as ent0,ent1,ent2
		//	else if(pin<=31&&pin>=16)
		   PINSEL0= ((PINSEL0 & (~(3<<(1*2))))|(3<<(1*2)));
	   PINSEL0= ((PINSEL0 & (~(3<<(3*2))))|(3<<(3*2)));
		      PINSEL0= ((PINSEL0 & (~(3<<(7*2))))|(3<<(7*2)));
    //  PINSEL0=(PINSEL0&(~3<<(1*2))|(pinfun<<(*2)));
     //PINSEL0=(PINSEL0&(~3<<(3*2)))|(EINT1_PIN_0_3<<(3*2));
	//PINSEL0=(PINSEL0&~(3<<(7*2)))|(EINT2_PIN_0_7<<(7*2));
	//cfg VIC peripheral
	//cfg ENT0 as fiq ENT1 as virq ENT2 as nvirq types
	VICIntSelect=1<<EINT0_VIC_CHNO ;
	//enable EINT0,ENT1 vi VIC
	VICIntEnable=1<<EINT0_VIC_CHNO |1<<EINT1_VIC_CHNO |1<<EINT2_VIC_CHNO;

	//cfg startup for ent0 ist to handle as fiq
	//as follows
	//FIQ handler  B FIQ_Handler
	// IMPORT eint0_fiq_isr
	// FIQ_HANDLER B ent0_fiq_isr
	//cfg EINNT1 with highest priorty('0')
	//as v.irq
	VICVectCntl0=(1<<5)|EINT1_VIC_CHNO;
	//load eint1_virq_isr_address
	VICVectAddr0=(u32)eint1_virq_isr;
        //cfg eint2 as nv.irq
	//load eint2.virq_isr address
	VICDefVectAddr=(u32)eint2_nvirq_isr;
	//cfg external interrupt peripheral
	//enable EINT0,EINT1,EINT2
	//EXTINT=0
	//cfg EINT0,EINT1,EINT2 for edge Triggering
	EXTMODE=1<<2|1<<1|1<<0;
	//cfg EINT0,EINT1 and EINT2 as edge triggering
	//EXTPOLAR=0
	//CFG P1.16,P1.17 and p1.18 as gpio out pins
	IODIR1=1<<EINT0_STATUS_LED|1<<EINT1_STATUS_LED|1<<EINT2_STATUS_LED;
	while(1)
		var++;
}
void eint0_fiq_isr(void) __irq
{
	IOPIN1^=1<<EINT0_STATUS_LED;
        delay_ms(100);
	//clear EINT0 flag in external interrupt
	EXTINT=1<<0;
	//clear EINT0 flag in VIC BLOCK
	VICVectAddr=0;
}
void eint1_virq_isr(void) __irq
{
	IOPIN1^=1<<EINT1_STATUS_LED;
        delay_ms(100);
	var=0;
	//clear EINT0 flag in external interrupt
	EXTINT=1<<1;
	//clear EINT0 flag in VIC BLOCK
	VICVectAddr=0;
}
void eint2_nvirq_isr(void) __irq
{
	IOPIN1^=1<<EINT2_STATUS_LED;
        delay_ms(100);
	//clear EINT0 flag in external interrupt
	EXTINT=1<<2;
	//clear EINT0 flag in VIC BLOCK
	VICVectAddr=0;
}
