/* 
 * File:   twi_master.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
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

