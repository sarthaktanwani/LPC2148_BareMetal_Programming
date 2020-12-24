#include<lpc214x.h>
#include "define.h"
#include "delay.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
/* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
    // reverse(s);
 }

void LCD_Data(unsigned char b)
{
	IO0PIN=(b<<0);
	IO0PIN|=(1<<10);	//RS=1
	IO0PIN|=(1<<8);		//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<8);	//EN=0
}
void LCD_Data1(unsigned int b)
{
IO0PIN=(b<<0);
	IO0PIN|=(1<<10);	//RS=1
	IO0PIN|=(1<<8);		//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<8);	//EN=0
}

void LCD_Cmd(unsigned char a)
{
	IO0PIN=(a<<0);
	IO0PIN&=~(1<<10);		//RS=0
	IO0PIN|=(1<<8);			//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<8);		//EN=0
}
void LCD_init()
{
	//PINSEL0=0;
	LCD_Cmd(0x38);
	LCD_Cmd(0x0e);
	LCD_Cmd(0x06);
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
}
void LCD_str(unsigned char *a)
{ 
	while(*a!='\0')
	{	
		LCD_Data(*a);
		a++;
	}
}
 /*****************ADC Functions***************/
void ADC0_Init(void)
{
	/*************Initialize ADC AD0.0*************/
	AD0CR = 1<<21;								//A/D is Operational
	AD0CR = 0<<21;								//A/D is in Power Down Mode
	PCONP = (PCONP &0x001817BE) | (1UL<<12);
	PINSEL0 = 0x00;
	PINSEL1 = 0x00400000;					//P0.27 is Configured as Analog to Digital Converter Pin AD0.0
	
	AD0CR = 0x00200401;						//CLKDIV=4,Channel-0.0 Selected,A/D is Operational
	/*
	A/D Clock = PCLK /(CLKDIV+1);
	*/
	/**********************************************/
}
unsigned int ADC0_Read(void)
{
	unsigned long adc_data;
	
	AD0CR |= 1UL<<24;							//Start Conversion
	do
	{
		adc_data = AD0GDR;
	}while(!(adc_data & 0x80000000));
	//Wait untill the DONE bits Sets
	AD0CR &= ~0x01000000;					//Stops the A/D Conversion   
	
	adc_data = adc_data >> 6;
	adc_data = adc_data & 0x3FF;    //Clearing all other Bits

return (adc_data);
}
/*********************************************/

main()
{
	unsigned int adc_value;
	
	PINSEL0=0;
	ADC0_Init();
	adc_value=ADC0_Read();
	/*while(1)
	{
		PINSEL1 = 0x00400000;
		AD1CR=0x00200D02;
		AD1CR|=0x01000000;
		do
		{
			i=AD1GDR;
		}while((i&0x80000000)==0);
		adc_value=(i>>6)&0x3FF;
	}*/
	
	while(1)
	{
		char buffer[10];
		unsigned int a=adc_value;
		IO0DIR|=0x7FF;	
		//itoa(a,buffer);
		sprintf(buffer, "%d",a);
		LCD_init();
		//LCD_str("hi");
		LCD_str(buffer);
		_delay_ms(20);
	}
}
