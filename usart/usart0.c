/*
 * usart0.c
 *
 * Created: 22.10.2019 11:20:29
 *  Author: AST-PC
 */ 

#include "usart0.h"

void usart0Init(void)
{
	UCSR0A = 0x00;	//U2X: Double the USART Transmission Speed Disabled
	UCSR0B = 0X18;	//RX Complete Interrupt Enabled,Transmitter Enabled
	UCSR0C = 0x06;	//URSEL Enabled, Asynchronous Operation, Parity Disabled, 8bit Enabled
	UCSR0B = (1<<RXEN0)|(1<<RXCIE0);	//enable global interrupts
	UBRR0 = 95; //4800bps
}

void usart0SetSerialBaudrate(uint32_t usart0Baudrate)
{
	static uint16_t lastUBRR0;

	UCSR0A = 0x00;	//U2X: Double the USART Transmission Speed Disabled
	UCSR0B = 0x18;	//RX Complete Interrupt Enabled,Transmitter Enabled
	UCSR0C = 0x06;	//URSEL Enabled, Asynchronous Operation, Parity Disabled, 8bit Enabled
	UCSR0B = (1<<RXEN0)|(1<<RXCIE0);//enable global interrupts
	
	
	
// 	#if (F_CPU != 7372800)
// 	#error F_CPU does not equal 7372800!!
// 	#endif
	UBRR0 = ((F_CPU / (usart0Baudrate * 16UL))) - 1;// PRESCALER HESAPLA
	
	if(lastUBRR0 != UBRR0)
	{
		UBRR0H		= UBRR0 >> 8;
		UBRR0L		= UBRR0;
		lastUBRR0	= UBRR0;
	}
	
}

uint8_t usart0PutChar(uint8_t c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

void usart0PutString_P(const char *progmem_s)
{
	char c;
	while ((c = pgm_read_byte(progmem_s++)))
	{
		usart0PutChar(c);
	}
}

void usart0PutString(char * ram_s)
{
	char c;
	while ((c = *ram_s++))
	{
		usart0PutChar(c);
	}
}

