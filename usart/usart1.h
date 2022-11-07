/*
 * usart1.h
 *
 * Created: 22.10.2019 11:19:56
 *  Author: AST-PC
 */ 


#ifndef USART1_H_
#define USART1_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#define Uart_EnableTransmitIT()		UCSR1B |= (1 << UDRIE1)
#define Uart_DisableTransmitIT()	UCSR1B &= ~(1 << UDRIE1)

void usart1Init(void);
void usart1SetSerialBaudrate(uint32_t usart1Baudrate);
void usart1PutChar(uint8_t c);
void usart1PutString_P(const char *progmem_s);
void usart1PutString(char * ram_s);



#endif /* USART1_H_ */