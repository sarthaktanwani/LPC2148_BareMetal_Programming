#include <LPC214x.H>                     /* LPC21xx definitions               */
#define CR     0x0D
//#define FOSC 60000000UL
void init_serial(void)  {               /* Initialize Serial Interface       */
  PINSEL0 = 0x00050000;                  /* Enable RxD1 and TxD1              */
  U1LCR = 0x83;                          /* 8 bits, no Parity, 1 Stop bit     */
  U1DLL = 0x62;                            /* 9600 Baud Rate @ 15MHz VPB Clock  */
  U1LCR = 0x03;                          /* DLAB = 0                          */
}


/* implementation of putchar (also used by printf function to output data)    */
void sendchar (unsigned char ch)  {                 /* Write character to Serial Port    */
  	U1THR=ch;
		while(!(U1LSR&0X20));
}


int getkey (void){                     /* Read character from Serial Port   */
	
  while (!(U1LSR & 0x01));
  return (U1RBR);
}
void TRANSMIT_UART1(unsigned char *P)
{		
		/*	int i=0;
		 while(P[i]!='\0')
		 {
			sendchar(P[i]);
			 i++;
		}*/
		 /* Write string to Serial Port    */
	while(*P){
		//U1THR=*P;
		sendchar(*P);
		while(!(U1LSR&0X20));
		P++;} 
	
}
void Delay()
{
	unsigned int X=1000000;
	while(X--);
}
int main()
{
	//PINSEL0=0x00;
	//char g = 'g';
	
	init_serial();
	Delay();
	Delay();
	IO0DIR|=0xf;
 //sendchar('f');
	//sendchar(g);
	while(1)
	{ //sendchar('g');
		char ch=getkey();
	
		TRANSMIT_UART1("\r Enter a char :");
		sendchar(ch);		
		
		if(ch=='a')
			IO0PIN=0x01;
		else if(ch=='b')
			IO0PIN=0x02;
		else if(ch=='c')
			IO0PIN=0x04;
		else if(ch=='d')
			IO0PIN=0x08;
		else
			IO0PIN=0x00;
	}
}
