/* 
 * File:   twi_master.h
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
 * Created on February 16, 2015, 6:23 PM
 */

#ifndef TWI_MASTER_H
#define	TWI_MASTER_H
#define ACK 1
#define NAK 0
#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 
void TWIInit(void);
extern uint8_t i2c_readNak(void);
extern uint8_t i2c_readAck(void);
extern uint8_t i2c_write( unsigned char data );
extern void i2c_stop(void);
extern uint8_t i2c_rep_start(unsigned char address);
extern void i2c_start_wait(unsigned char address);
extern uint8_t i2c_start(unsigned char address);
#endif	/* TWI_MASTER_H */

