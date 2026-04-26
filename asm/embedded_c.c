//#include <reg51.h>
sfr P0=0x80;
 int i;
 sbit portpin=P0^0;
main()
{
  
   while(1)
   {
    portpin=0;
	for (i=0;i<120;i++) ;
    portpin=1;
	for (i=0;i<120;i++) ;
   }
}
