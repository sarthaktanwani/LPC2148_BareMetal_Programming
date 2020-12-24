#include<lpc21Xx.h>
main()
{
	IO0DIR |= (1<<10);
	while(1)
	{
		IO0SET |= (1<<10);
		//_delay_ms(200);
		IO0CLR |= (1<<10);
		//_delay_ms(200);
	}
}