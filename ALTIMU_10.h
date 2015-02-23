/* 
 * File:   ALTIMU_10.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 16, 2015, 6:19 PM
 */

#ifndef ALTIMU_10_H
#define	ALTIMU_10_H
//#include <avr/io.h>//TODO fix this!

#ifdef	__cplusplus
extern "C" {
#endif



//7-bit slave addresses for the three sensors
#define GYRO_SLAVE_ADDRESS  0x6B
#define ACC_MAG_SLAVE_ADDRESS   0x1D
#define BAR_SLAVE_ADDRESS   0x5D
typedef unsigned char byte;

uint8_t read_from_reg(byte address_slave, byte reg_slave);
uint8_t write_to_reg(byte address_slave, byte reg_slave, uint8_t data);




#ifdef	__cplusplus
}
#endif


#endif	/* ALTIMU_10_H */

