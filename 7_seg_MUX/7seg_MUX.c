#include<lpc21xx.h>
#include "define.h"
#include "delay.h"
unsigned char arr[]={0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
main()
{
	int i,j;
p0=p1=p2=0;
ddra|=0x0000FFFF;
while(1)
{
	for(i=0;i<10;i++)
	{
		//porta=arr[i];
		pina|=arr[i];		
		for(j=0;j<10;j++)
		{
			//porta=(arr[j]<<8);
			pina|=(arr[j]<<8);
			_delay_ms(10);
			pina&=~(arr[j]<<8);
			//clra=(arr[j]<<4);
		}
		pina&=~arr[i];
		//clra=arr[i];
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
