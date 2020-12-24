#include<lpc21xx.h>
#include "define.h"
#include "delay.h"
unsigned char arr[]={0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
main()
{
	int i;
p0=p1=p2=0;
ddra|=0x000000FF;
while(1)
{
	for(i=0;i<10;i++)
	{
		pina=arr[i];
		_delay_ms(25);
	}
}
}
	
	
	/*while(1)
{	
porta|=(1<<1);
_delay_ms(100);	
clra|=(1<<1);
_delay_ms(60000);
}*/
