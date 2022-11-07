/*
 * usart1.c
 *
 * Created: 22.10.2019 11:20:11
 *  Author: AST-PC
 */ 

#include "usart1.h"

void usart1Init(void)
{
	UCSR1A = 0x00;	//U2X: Double the USART Transmission Speed Disabled
	UCSR1B = 0X18;	//RX Complete Interrupt Enabled,Transmitter Enabled
	UCSR1C = 0x06;	//URSEL Enabled, Asynchronous Operation, Parity Disabled, 8bit Enabled
	UCSR1C = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);	//enable global interrupts
}

void usart1SetSerialBaudrate(uint32_t usart1Baudrate)
{
	static uint16_t lastUBRR1;

	UCSR1A = 0x00;	//U2X: Double the USART Transmission Speed Disabled
	UCSR1B = 0x18;	//RX Complete Interrupt Enabled,Transmitter Enabled
	UCSR1C = 0x06;	//URSEL Enabled, Asynchronous Operation, Parity Disabled, 8bit Enabled
	UCSR1B = (1<<TXEN1);//enable global interrupts
	
	
// 	#if (F_CPU != 7372800)
// 	#error F_CPU does not equal 7372800!!
// 	#endif
	UBRR1 = ((F_CPU / (usart1Baudrate * 16UL))) - 1;// PRESCALER HESAPLA
	
	if(lastUBRR1 != UBRR1)
	{
		UBRR1H = UBRR1 >> 8;
		UBRR1L = UBRR1;
		lastUBRR1 = UBRR1;
	}
	
}

void usart1PutChar(uint8_t c)
{
	loop_until_bit_is_set(UCSR1A, UDRE1);
	UDR1 = c;
}

void usart1PutString_P(const char *progmem_s)
{
	char c;
	while ((c = pgm_read_byte(progmem_s++)))
	{
		usart1PutChar(c);
	}
}
void usart1PutString(char * ram_s)
{
	char c;
	while ((c = *ram_s++))
	{
		usart1PutChar(c);
	}
}