/* 
 * File:   usart.h
 * Author: krille0x7c2
 *
 * Created on February 16, 2015, 5:58 PM
 */

#ifndef USART_H
#define	USART_H
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART0Init(void);
int USART0SendByte(char u8Data, FILE *stream);
int USART0ReceiveByte(FILE *stream);


#endif	/* USART_H */

