#include<lpc21xx.h>
#include "delay.h"
#define ST_CP (1<<2)
#define SH_CP	(1<<0)
#define DS		(1<<1)
main()
{
	int i=0;
	int a=0x38;
	//int a= data;
	PINSEL0=0;
	IO0DIR=0x3f;
	while(1)
	{
		//pina|=(1<<3);
		for(i=0;i<8;i++)
		{
			IO0PIN=(i*8);
			if(a&0x80 == 1)
			{
					IO0PIN|=DS;
			}
			else
			{
				IO0PIN &=~DS;
			}
			IO0PIN|=SH_CP;
			_delay_ms(40);
			IO0PIN&=~SH_CP;
			_delay_ms(40);
			a=a<<1;
		}
		IO0PIN|=ST_CP;
		_delay_ms(40);
		IO0PIN&=~ST_CP;
		_delay_ms(40);
	}
}
