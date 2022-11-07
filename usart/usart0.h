/*
 * usart0.h
 *
 * Created: 22.10.2019 11:19:39
 *  Author: AST-PC
 */ 


#ifndef USART0_H_
#define USART0_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

void usart0Init(void);
void usart0SetSerialBaudrate(uint32_t usart0Baudrate);
uint8_t usart0PutChar(uint8_t c);
void usart0PutString_P(const char *progmem_s);
void usart0PutString(char * ram_s);




#endif /* USART0_H_ */