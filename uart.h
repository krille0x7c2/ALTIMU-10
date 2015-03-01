/* 
 * File:   usart.h
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
 * Created on February 16, 2015, 5:58 PM
 */

#ifndef UART_H
#define	UART_H
#include <stdio.h>
/*//Defined in makefile. uncomment if needed
 *#define F_CPU 16000000UL
 */
#define BAUD 9600

extern void uart_init(void);
extern int uart_send_byte(char u8Data, FILE *stream);
extern int uart_receive_byte(FILE *stream);


#endif	/* UART_H */

