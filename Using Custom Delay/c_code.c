#include<lpc214x.h>
void PLL_Init()
{
	PLL0CFG=0X25;
	PLL0CON=0X01;
	PLL0FEED=0XAA;
	PLL0FEED=0X55;
	while(PLL0STAT&(1<<10)==0);
	PLL0CON=0X0B;
	PLL0FEED=0XAA;
	PLL0FEED=0X55;
}
void timer_Init()
{
	T0PR=59999;
}
void _delay_ms(unsigned int ms)
{
	T0TCR=0X01;
	while(T0TC<=ms);
	T0TC=T0PC=0;
}
main()
{
	PINSEL0=0;
	IO0DIR|=0X01;
	PLL_Init();
	timer_Init();
	while(1)
	{
		IO0SET=0X01;
		_delay_ms(1000);
		IO0CLR=0X01;
		_delay_ms(1000);
	}
}