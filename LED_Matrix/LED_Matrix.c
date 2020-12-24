//use array (the way taught earlier) for lessening the flickering 

#include<lpc21xx.h>
#include "define.h"
#include "delay.h"
main()
{
	int i=11;
p0=p1=p2=0;
	
	ddra|=0xFFF;
	while(1)
	{
		pina=0x0C1;
		_delay_ms(25);
		pina=0x6C2;
		_delay_ms(25);
		pina=0x6C4;
		_delay_ms(25);
		pina=0x6C8;
		_delay_ms(25);
		pina=0x610;
		_delay_ms(25);
	}
}
