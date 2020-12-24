#include<lpc213x.h>
//#include "define.h"
#include  "delay.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define RS	10
#define EN	8

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
	IO0PIN|=(1<<RS);	//RS=1
	IO0PIN|=(1<<EN);		//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<EN);	//EN=0
}
void LCD_Data1(unsigned int b)
{
	IO0PIN=(b<<0);
	IO0PIN|=(1<<RS);	//RS=1
	IO0PIN|=(1<<EN);		//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<EN);	//EN=0
}

void LCD_Cmd(unsigned char a)
{
	IO0PIN=(a<<0);
	IO0PIN&=~(1<<RS);		//RS=0
	IO0PIN|=(1<<EN);			//EN=1
	_delay_ms(2);
	IO0PIN&=~(1<<EN);		//EN=0
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
	while(*a != '\0')
		LCD_Data(*a++);
}
main()
{
	PINSEL0=0x00;
	IO0DIR=0x7FF;
	while(1)
	{
		char buffer[10];
		int len,i,a=21;
		//itoa(a,buffer);
		sprintf(buffer, "%d", a);
		LCD_init();
		LCD_str("Sarthak1");
		LCD_str(buffer);
		_delay_ms(20);
	}
}

