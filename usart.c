/* 
 * File:   usart.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 * Public Key: https://pgp.mit.edu/pks/lookup?op=get&search=0x3DD59D8AB91E4765
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on February 16, 2015, 5:30 PM
 */
#include "usart.h"
#include <avr/io.h>

void USART0Init(void) {
    // Set baud rate
    UBRR0H = (uint8_t) (UBRR_VALUE >> 8);
    UBRR0L = (uint8_t) UBRR_VALUE;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    //enable transmission and reception
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

int USART0SendByte(char u8Data, FILE *stream) {
    if (u8Data == '\n') {
        USART0SendByte('\r', 0);
    }
    //wait while previous byte is completed
    while (!(UCSR0A & (1 << UDRE0))) {
    };
    // Transmit data
    UDR0 = u8Data;
    return 0;
}
int USART0ReceiveByte(FILE *stream) {
    uint8_t u8Data;
    // Wait for byte to be received
    while (!(UCSR0A & (1 << RXC0))) {
    };
    u8Data = UDR0;
    //echo input data
    USART0SendByte(u8Data, stream);
    // Return received data
    return u8Data;
}
