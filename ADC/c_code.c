/*(C) Umang Gajera - www.ocfreaks.com
More Embedded tutorials @ www.ocfreaks.com/cat/embedded/
LPC2148 ADC Example 1 Source Code.
@ http://www.ocfreaks.com/lpc2148-adc-programming-tutorial/
License : GPL.*/

#include <lpc213x.h>
//#include "ocfreaks_sh.h" //OCFreaks LPC214x Tutorial Support Header
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "delay.h"

#define AD06 ((1<<9)|(1<<8)) //Select AD0.6 function for P0.4
#define SEL_AD06 (1<<6)

#define CLKDIV (15-1) // 4Mhz ADC clock (ADC_CLOCK=PCLK/CLKDIV) where "CLKDIV-1" is actually used , in our case PCLK=60mhz  
#define BURST_MODE_OFF (0<<16) // 1 for on and 0 for off
#define PowerUP (1<<21)
#define START_NOW ((0<<26)|(0<<25)|(1<<24)) //001 for starting the conversion immediately
#define ADC_DONE (1<<31)

#define VREF 3.3 //Reference Voltage at VREF pin

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
int main(void)
{
	//initClocks(); //CCLK and PCLK @ 60Mhz - defined in ocfreaks_sh.h
	//initUART0(); //Initialize UART0 for printf - defined in ocfreaks_sh.h

	int result=0;
	float voltage = 0;
	unsigned long AD0CR_setup = (CLKDIV<<8) | BURST_MODE_OFF | PowerUP;
	PINSEL0 |= AD06 ; //select AD0.6 for P0.4
	//printf("OCFreaks.com ADC Tutorial Example 1.\nSoftware Controlled Mode ADC on AD06 Channel.\n");
	PINSEL0=0;
	while(1)
	{
		char buffer[10];
		int len,i,a=21;
		IO0DIR=0x7FF;
		AD0CR =  AD0CR_setup | SEL_AD06; 
		AD0CR |= START_NOW; //Start new Conversion

		while( (AD0DR6 & ADC_DONE) == 0 );
		
		result = (AD0DR6>>6) & 0x3ff;
		
		voltage = ((float)result*VREF)/1024; //Convert result to volts
		sprintf(buffer, "%f", voltage);
		LCD_init();
		LCD_str("Sarthak1");
		LCD_str(buffer);
		_delay_ms(20);

		//printf("AD06 = %dmV\n" , (int)( voltage*1000 )); //Display millivolts
		_delay_ms(250); //Slowing down Updates to 4 Updates per second
	}
	
	//return 0; //This won't execute normally
}

