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
#include "uart.h"
#include <avr/io.h>

void uart_init(void) {
    // Set baud rate
    UBRR0H = (uint8_t) (UBRR_VALUE >> 8);
    UBRR0L = (uint8_t) UBRR_VALUE;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    //enable transmission and reception
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

int uart_send_byte(char data, FILE *stream) {
    if (data == '\n') {
        uart_send_byte('\r', 0);
    }
    //wait while previous byte is completed
    while (!(UCSR0A & (1 << UDRE0)));
    // Transmit data
    UDR0 = data;
    return 0;
}

/*Not needed cause the receive part will be interrupt driven
 *but included for debug purpose.
 */
int uart_receive_byte(FILE *stream) {
    uint8_t data;
    // Wait for byte to be received
    while (!(UCSR0A & (1 << RXC0)));
    data = UDR0;
    //echo input data
//    uart_send_byte(data, stream);
    // Return received data
    return (int)data;
}
